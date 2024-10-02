// @Copyright Marton Pal SZTE


#include "TrainGamePlayerController.h"
#include "Engine/Engine.h"

ATrainGamePlayerController::ATrainGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATrainGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
}
