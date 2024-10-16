// @Copyright Marton Pal SZTE


#include "TrainGamePlayerController.h"
#include "Engine/Engine.h"
#include "TrainGamePlayerState.h"

ATrainGamePlayerController::ATrainGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATrainGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalPlayerController()) {
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
	SR_CallDrawStartCards(GetPlayerState<ATrainGamePlayerState>());
}

void ATrainGamePlayerController::SR_CallDrawStartCards_Implementation(ATrainGamePlayerState* PlayerStateParam)
{
	ATrainGameState* GameState = Cast<ATrainGameState>(GetWorld()->GetGameState());

	if (GameState) {
		GameState->DrawStartCards(PlayerStateParam);
	}
}