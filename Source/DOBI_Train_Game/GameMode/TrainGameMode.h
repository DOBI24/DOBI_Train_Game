// @Copyright Marton Pal SZTE

#pragma once

#include "../Track/Track.h"
#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "GameFramework/GameModeBase.h"
#include "TrainGameMode.generated.h"

USTRUCT(BlueprintType)
struct FArray2D
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<uint16> Array;
	FArray2D(){}
	FArray2D(const TArray<uint16>& InArray) : Array(InArray) {}
};

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API ATrainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATrainGameMode();

	UPROPERTY()
	TArray<UTrack*> AllTrack;

	UFUNCTION()
	void CreateTrackByEnum();

	UFUNCTION()
	TArray<FArray2D> ImportTrackData();
};