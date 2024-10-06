// @Copyright Marton Pal SZTE


#include "TrainGameMode.h"
#include "TrainGameState.h"

ATrainGameMode::ATrainGameMode()
{
	static ConstructorHelpers::FClassFinder<ATrainGameState> GameStateBPClass(TEXT("/Game/Game/BP_TrainGameState"));
	if (GameStateBPClass.Class != nullptr)
	{
		GameStateClass = GameStateBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Game/Character/BP_GameCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Game/BP_TrainGamePlayerController"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
