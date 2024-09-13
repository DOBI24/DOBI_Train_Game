// @Copyright Marton Pal SZTE


#include "TrainGameMode.h"
#include "Misc/FileHelper.h"

ATrainGameMode::ATrainGameMode()
{
	CreateTrackByEnum();
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
	UE_LOG(LogTemp, Warning, TEXT("%d"), AllTrack.Num());
}

TArray<FArray2D> ATrainGameMode::ImportTrackData()
{
	//Temp array initialization
	TArray<FArray2D> DataArray = { FArray2D({5,0}), FArray2D({6,0}), FArray2D({0,2,2}), FArray2D({0,2,2}), FArray2D({0,2,2}), FArray2D({5,0}), FArray2D({1,0}), FArray2D({6,0}), FArray2D({1,0}), FArray2D({8,0}), FArray2D({6,1}), FArray2D({2,1}), FArray2D({0,1}), FArray2D({7,0}), FArray2D({3,0}), FArray2D({8,0}), FArray2D({1,0}), FArray2D({5,0}), FArray2D({4,0}), FArray2D({0,0}), FArray2D({3,0}), FArray2D({4,0}), FArray2D({7,0}), FArray2D({0,1}), FArray2D({0,0}), FArray2D({2,0}), FArray2D({5,0}), FArray2D({6,0}), FArray2D({3,0}), FArray2D({2,0}), FArray2D({4,0}), FArray2D({1,1}), FArray2D({0,1}), FArray2D({4,1}), FArray2D({8,1}), FArray2D({8,0}), FArray2D({6,0}), FArray2D({7,0}), FArray2D({1,0}), FArray2D({0,2,1}), FArray2D({0,2,1}), FArray2D({3,0}), FArray2D({3,1}), FArray2D({5,1}), FArray2D({6,0}), FArray2D({0,0}), FArray2D({2,0}), FArray2D({0,2,1}), FArray2D({0,2,1}), FArray2D({0,2,2}), FArray2D({0,2,1}), FArray2D({0,0}), FArray2D({7,0}), FArray2D({2,0}), FArray2D({8,0}), FArray2D({3,0}), FArray2D({5,0}), FArray2D({1,0}), FArray2D({0,1}), FArray2D({0,1}), FArray2D({7,0}), FArray2D({1,0}), FArray2D({4,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({7,0}), FArray2D({6,0}), FArray2D({8,0}), FArray2D({0,0}), FArray2D({3,0}), FArray2D({4,0}), FArray2D({0,0}), FArray2D({0,1}), FArray2D({2,0}), FArray2D({4,0}), FArray2D({2,0}), FArray2D({5,0}), FArray2D({7,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({8,0}), FArray2D({0,0}), FArray2D({0,0}), FArray2D({2,0}), FArray2D({0,2,1}), FArray2D({0,2,2}), FArray2D({0,2,2}), FArray2D({7,1}), FArray2D({0,1}), FArray2D({0,1}), FArray2D({3,0}), FArray2D({4,0}), FArray2D({6,0}), FArray2D({5,1}), FArray2D({0,1}), FArray2D({0,1}), FArray2D({1,0}), FArray2D({0,2,1}), FArray2D({8,0}) };
	return DataArray;
}
