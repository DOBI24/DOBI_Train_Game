// @Copyright Marton Pal SZTE


#include "TrainGamePlayerController.h"
#include "Engine/Engine.h"
#include "TrainGamePlayerState.h"
#include "../../CustomGameInstance.h"

ATrainGamePlayerController::ATrainGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATrainGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController()) {
		CheckLocalBegin();
	}
}

// Called when every player component has been synchronized
void ATrainGamePlayerController::LocalBeginPlay()
{
	CL_SetPlayerName();
	CheckCurrentGameState();

	//TODO: Delete if loading screen is created
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrainGamePlayerController::CL_TriggerReadyPlayer, 3.0f, false);

	//TriggerReadyPlayer();
}

void ATrainGamePlayerController::CheckLocalBegin()
{
	if (!GetPlayerState<ATrainGamePlayerState>() || !GetWorld()->GetGameState())
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &ATrainGamePlayerController::CheckLocalBegin);
		return;
	}
	LocalBeginPlay();
}

/* TIMER FUNCTIONS */


/* SERVER FUNCTIONS */
void ATrainGamePlayerController::SR_CallDrawStartCards_Implementation(const FString& CardType, ATrainGamePlayerState* PlayerStateParam, ATrainGamePlayerController* ControllerParam)
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	if (GameState) {
		if (CardType == "Wagon") {
			GameState->SR_DrawStartWagonCards(PlayerStateParam, ControllerParam);
		}
		else if (CardType == "Route") {
			GameState->SR_DrawStartRouteCards(PlayerStateParam);
		}
	}
}

void ATrainGamePlayerController::SR_SetPlayerName_Implementation(ATrainGamePlayerState* PlayerStateParam, const FString& Name)
{
	if (PlayerStateParam) {
		PlayerStateParam->SetPN(Name);
	}
}

void ATrainGamePlayerController::SR_PlayerReady_Implementation(ATrainGamePlayerState* PlayerStateParam)
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());
	GameState->PlayerReadyToNextState(PlayerStateParam);
}

/* CLIENT FUNCTIONS */
void ATrainGamePlayerController::CL_CallDrawStartCards_Implementation(const FString& CardType)
{
	SR_CallDrawStartCards(CardType, GetPlayerState<ATrainGamePlayerState>(), this);
}

void ATrainGamePlayerController::CL_TriggerReadyPlayer_Implementation()
{
	SR_PlayerReady(GetPlayerState<ATrainGamePlayerState>());
}

void ATrainGamePlayerController::CL_SetPlayerName_Implementation()
{
	if (!GetPlayerState<ATrainGamePlayerState>())
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &ATrainGamePlayerController::CL_SetPlayerName);
		return;
	}
	SR_SetPlayerName(GetPlayerState<ATrainGamePlayerState>(), Cast<UCustomGameInstance>(GetGameInstance())->InputName);
}

/* UI FUNCTIONS */
void ATrainGamePlayerController::TriggerHUDWidget_WagonCards(ECard_Color CardColor)
{
	BP_TriggerHUDWidget_WagonCards(CardColor);
}

void ATrainGamePlayerController::CheckCurrentGameState()
{
	ATrainGameState* TrainGameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	switch (TrainGameState->CurrentGameState)
	{
	case EGameState::WAITING_PLAYERS:
		CreatePlayerUI(WidgetReferences["WaitingPlayer"]);
		CL_CallDrawStartCards("Route");
		break;
	case EGameState::DRAW_ROUTE_CARDS:
		CreatePlayerUI(WidgetReferences["DrawRoute"]);
		break;
	case EGameState::DRAW_WAGON_CARDS:
		CreatePlayerUI(WidgetReferences["Game"]);
		CL_CallDrawStartCards("Wagon");
		break;
	case EGameState::NEXT_PLAYER:
		break;
	case EGameState::GAME:
		break;
	}
}