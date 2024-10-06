// @Copyright Marton Pal SZTE


#include "TrainGameMode.h"
#include "TrainGameState.h"


void ATrainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

ATrainGameMode::ATrainGameMode()
{
	GameStateClass = ATrainGameState::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Game/Character/BP_GameCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Game/BP_TrainGamePlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void ATrainGameMode::CreateCards()
{

}
