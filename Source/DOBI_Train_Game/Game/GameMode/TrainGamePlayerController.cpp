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
		ATrainGamePlayerState* TrainPlayerState = GetPlayerState<ATrainGamePlayerState>();
		if (TrainPlayerState) {
			TrainPlayerState->SetPN(Cast<UCustomGameInstance>(GetGameInstance())->InputName);
		}
		CallDrawStartCards();
	}
}

void ATrainGamePlayerController::CallDrawStartCards()
{
	if (!GetPlayerState<ATrainGamePlayerState>())
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &ATrainGamePlayerController::CallDrawStartCards);
		return;
	}
	SR_CallDrawStartCards(GetPlayerState<ATrainGamePlayerState>(), this);
}

void ATrainGamePlayerController::CL_TriggerHUDWidget_WagonCards_Implementation(ECard_Color CardColor)
{
	this->TriggerHUDWidget_WagonCards(CardColor);
}

void ATrainGamePlayerController::SR_CallDrawStartCards_Implementation(ATrainGamePlayerState* PlayerStateParam, ATrainGamePlayerController* ControllerParam)
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	if (GameState) {
		GameState->DrawStartCards(PlayerStateParam, ControllerParam);
	}
}