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
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrainGamePlayerController::SR_PlayerReady, 3.0f, false);

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
void ATrainGamePlayerController::SR_CallDrawCards_Implementation(const FString& CardType)
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());
	ATrainGamePlayerState* LocalPlayerState = Cast<ATrainGamePlayerState>(PlayerState);

	if (GameState) {
		if (CardType == "Wagon") {
			GameState->SR_DrawWagonCard(4, LocalPlayerState);
		}
		else if (CardType == "Route") {
			GameState->SR_DrawRouteCards(LocalPlayerState);
		}
	}
}

void ATrainGamePlayerController::SR_CallDrawWagonCards_Implementation()
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	GameState->SR_DrawWagonCard(2, Cast<ATrainGamePlayerState>(PlayerState));
}

void ATrainGamePlayerController::SR_SetPlayerName_Implementation(ATrainGamePlayerState* PlayerStateParam, const FString& Name)
{
	if (PlayerStateParam) {
		PlayerStateParam->SR_SetPlayerName(Name);
	}
}

void ATrainGamePlayerController::SR_PlayerReady_Implementation()
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());
	ATrainGamePlayerState* LocalPlayerState = Cast<ATrainGamePlayerState>(PlayerState);

	if (GameState->CurrentGameState == EGameState::WAITING_PLAYERS) {
		GameState->SR_PlayerReadyToStart(LocalPlayerState);
		return;
	}

	GameState->SR_PlayerReadyToNextState(LocalPlayerState);
}

/* CLIENT FUNCTIONS */
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
	if (GameAndUI) {
		SetInputMode(FInputModeGameAndUI());
		return;
	}
	
	SetInputMode(FInputModeUIOnly());
}

bool ATrainGamePlayerController::CanInteract()
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	if (GameState && (GameState->CurrentGameState == EGameState::GAME) && (PlayerState == GameState->CurrentPlayer)) {
		return true;
	}

	return false;
}

void ATrainGamePlayerController::CL_OutlineCompletedRouteCard_Implementation(int32 Index)
{
	BP_OutlineCompletedRouteCard(Index);
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
		SR_CallDrawCards("Route");
		break;
	case EGameState::DRAW_WAGON_CARDS:
		SwitchScene(WidgetReferences["Game"]);
		SR_CallDrawCards("Wagon");
		break;
	case EGameState::GAME:
		BP_OutlineCurrentPlayer(CurrentPlayer);
		if (CurrentPlayer && (CurrentPlayer == GetPlayerState<ATrainGamePlayerState>())) {
			ToggleDrawButtonEnable(true);
		}
		break;
	case EGameState::NEXT_PLAYER:
		SwitchScene(WidgetReferences["Game"]);
		BP_OutlineCurrentPlayer(CurrentPlayer);
		BP_DeselectTrack();
		ToggleDrawButtonEnable(false);
		break;
	case EGameState::END:
		SwitchScene(WidgetReferences["EndGame"]);
		break;
	}
}
