// @Copyright Marton Pal SZTE


#include "TrainGameMode.h"
#include "TrainGameState.h"


void ATrainGameMode::BeginPlay()
{
	Super::BeginPlay();
	CreateTrackByEnum();
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

void ATrainGameMode::CreateTrackByEnum()
{
	TArray<FArray2D> DataArray = ATrainGameMode::ImportTrackData();
	for (auto& Data : DataArray)
	{
		UTrack* NewTrack = NewObject<UTrack>();
		NewTrack->TrackColor = ETrack_Color(Data.Array[0]);
		NewTrack->TrackType = ETrack_Type(Data.Array[1]);
		AllTrack.Emplace(NewTrack);
	}
}

TArray<FArray2D> ATrainGameMode::ImportTrackData()
{
	//Temp array initialization
	TArray<FArray2D> DataArray = { FArray2D({5,0}), FArray2D({6,0}), FArray2D({0,2,2}), FArray2D({0,2,2}), FArray2D({0,2,2}), FArray2D({5,0}), FArray2D({1,0}), FArray2D({6,0}), FArray2D({1,0}), FArray2D({8,0}), FArray2D({6,1}), FArray2D({2,1}), FArray2D({0,1}), FArray2D({7,0}), FArray2D({3,0}), FArray2D({8,0}), FArray2D({1,0}), FArray2D({5,0}), FArray2D({4,0}), FArray2D({0,0}), FArray2D({3,0}), FArray2D({4,0}), FArray2D({7,0}), FArray2D({0,1}), FArray2D({0,0}), FArray2D({2,0}), FArray2D({5,0}), FArray2D({6,0}), FArray2D({3,0}), FArray2D({2,0}), FArray2D({4,0}), FArray2D({1,1}), FArray2D({0,1}), FArray2D({4,1}), FArray2D({8,1}), FArray2D({8,0}), FArray2D({6,0}), FArray2D({7,0}), FArray2D({1,0}), FArray2D({0,2,1}), FArray2D({0,2,1}), FArray2D({3,0}), FArray2D({3,1}), FArray2D({5,1}), FArray2D({6,0}), FArray2D({0,0}), FArray2D({2,0}), FArray2D({0,2,1}), FArray2D({0,2,1}), FArray2D({0,2,2}), FArray2D({0,2,1}), FArray2D({0,0}), FArray2D({7,0}), FArray2D({2,0}), FArray2D({8,0}), FArray2D({3,0}), FArray2D({5,0}), FArray2D({1,0}), FArray2D({0,1}), FArray2D({0,1}), FArray2D({7,0}), FArray2D({1,0}), FArray2D({4,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({7,0}), FArray2D({6,0}), FArray2D({8,0}), FArray2D({0,0}), FArray2D({3,0}), FArray2D({4,0}), FArray2D({0,0}), FArray2D({0,1}), FArray2D({2,0}), FArray2D({4,0}), FArray2D({2,0}), FArray2D({5,0}), FArray2D({7,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({8,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({2,0}), FArray2D({0,2,1}), FArray2D({0,2,2}), FArray2D({0,2,2}), FArray2D({7,1}), FArray2D({0,1}), FArray2D({0,1}), FArray2D({3,0}), FArray2D({4,0}), FArray2D({6,0}), FArray2D({5,1}), FArray2D({0,1}), FArray2D({0,1}), FArray2D({1,0}), FArray2D({0,2,1}), FArray2D({8,0}) };
	return DataArray;
}

void ATrainGameMode::CreateCards()
{

}
