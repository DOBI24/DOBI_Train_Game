// @Copyright Marton Pal SZTE


#include "TrainGamePlayerController.h"
#include "Engine/Engine.h"
#include "TrainGamePlayerState.h"
#include "../../CustomGameInstance.h"
#include "TrainGameMode.h"

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
	if (!GetPlayerState<ATrainGamePlayerState>() ||
		!GetWorld()->GetGameState())
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
			GameState->SR_DrawStartRouteCards(PlayerStateParam, ControllerParam);
		}
	}
}

void ATrainGamePlayerController::SR_SetPlayerName_Implementation(ATrainGamePlayerState* PlayerStateParam, const FString& Name)
{
	if (PlayerStateParam) {
		PlayerStateParam->SR_SetPlayerName(Name);
	}
}

void ATrainGamePlayerController::SR_PlayerReady_Implementation(ATrainGamePlayerState* PlayerStateParam)
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());
	if (GameState->CurrentGameState == EGameState::WAITING_PLAYERS) {
		GameState->SR_PlayerReadyToStart(PlayerStateParam);
		return;
	}

	GameState->SR_PlayerReadyToNextState(PlayerStateParam);
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

void ATrainGamePlayerController::CL_TriggerHUDWidget_WagonCards_Implementation(ECard_Color CardColor)
{
	BP_TriggerHUDWidget_WagonCards(CardColor);
}

void ATrainGamePlayerController::CL_TriggerRouteWidgets_AddRouteCards_Implementation(FRouteCard Card)
{
	BP_TriggerRouteWidgets_AddRouteCards(Card);
}

void ATrainGamePlayerController::SetInputModeByServer_Implementation(bool GameAndUI)
{
	UE_LOG(LogTemp, Warning, TEXT("Mode: %s"), GameAndUI ? TEXT("GameAndUI") : TEXT("UIOnly"));
	if (GameAndUI) {
		SetInputMode(FInputModeGameAndUI());
		return;
	}
	
	SetInputMode(FInputModeUIOnly());
}

/* FUNCTIONS */

TMap<int32, int32> ATrainGamePlayerController::GetPOINT_FROM_LENGTH()
{
	return ATrainGameMode::POINT_FROM_LENGTH;
}

void ATrainGamePlayerController::CheckCurrentGameState(ATrainGamePlayerState* CurrentPlayer)
{
	ATrainGameState* TrainGameState = Cast<ATrainGameState>(GetWorld()->GetGameState());
	ATrainGamePlayerState* LocalPlayerState = Cast<ATrainGamePlayerState>(PlayerState);

	switch (TrainGameState->CurrentGameState)
	{
	case EGameState::WAITING_PLAYERS:
		break;
	case EGameState::DRAW_ROUTE_CARDS:
		SwitchScene(WidgetReferences["DrawRoute"]);
		CL_CallDrawStartCards("Route");
		break;
	case EGameState::DRAW_WAGON_CARDS:
		SwitchScene(WidgetReferences["Game"]);
		CL_CallDrawStartCards("Wagon");
		break;
	case EGameState::GAME:
		BP_OutlineCurrentPlayer(CurrentPlayer);
		if (CurrentPlayer && (CurrentPlayer == GetPlayerState<ATrainGamePlayerState>())) {
			
		}
		break;
	case EGameState::NEXT_PLAYER:
		BP_OutlineCurrentPlayer(CurrentPlayer);
		BP_DeselectTrack();
		break;
	}
}

bool ATrainGamePlayerController::CanInteract()
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	if (GameState && (GameState->CurrentGameState == EGameState::GAME) && (PlayerState == GameState->CurrentPlayer)) {
		return true;
	}

	return false;
}
