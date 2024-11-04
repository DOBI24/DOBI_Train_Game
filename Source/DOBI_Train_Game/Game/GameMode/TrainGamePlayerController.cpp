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
	SetPlayerName();
	CheckCurrentGameState();

	//TODO: Delete if loading screen is created
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrainGamePlayerController::TriggerReadyPlayer, 3.0f, false);
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

void ATrainGamePlayerController::CallDrawStartCards()
{
	SR_CallDrawStartCards(GetPlayerState<ATrainGamePlayerState>(), this);
}

void ATrainGamePlayerController::SR_CallDrawStartCards_Implementation(ATrainGamePlayerState* PlayerStateParam, ATrainGamePlayerController* ControllerParam)
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	if (GameState) {
		GameState->DrawStartCards(PlayerStateParam, ControllerParam);
	}
}

void ATrainGamePlayerController::CL_TriggerHUDWidget_WagonCards_Implementation(ECard_Color CardColor)
{
	this->TriggerHUDWidget_WagonCards(CardColor);
}

void ATrainGamePlayerController::SetPlayerName()
{
	if (!GetPlayerState<ATrainGamePlayerState>())
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &ATrainGamePlayerController::SetPlayerName);
		return;
	}
	SR_SetPlayerName(GetPlayerState<ATrainGamePlayerState>(), Cast<UCustomGameInstance>(GetGameInstance())->InputName);
}

void ATrainGamePlayerController::SR_PlayerReady_Implementation(ATrainGamePlayerState* PlayerStateParam)
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());
	GameState->PlayerReadyToStart(PlayerStateParam);
}

void ATrainGamePlayerController::SR_SetPlayerName_Implementation(ATrainGamePlayerState* PlayerStateParam, const FString& Name)
{
	if (PlayerStateParam) {
		PlayerStateParam->SetPN(Name);
	}
}

void ATrainGamePlayerController::TriggerReadyPlayer()
{
	SR_PlayerReady(GetPlayerState<ATrainGamePlayerState>());
}

void ATrainGamePlayerController::CheckCurrentGameState()
{
	ATrainGameState* TrainGameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	switch (TrainGameState->CurrentGameState)
	{
	case EGameState::WAITING_PLAYERS:
		CreateWaitingPlayerUI();
		break;
	case EGameState::DRAW_ROUTE_CARDS:
		CreateGameUI();
		CallDrawStartCards();
		break;
	case EGameState::DRAW_WAGON_CARDS:
		break;
	case EGameState::NEXT_PLAYER:
		break;
	case EGameState::GAME:
		break;
	}
}