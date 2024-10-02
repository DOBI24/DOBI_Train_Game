// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "../Card/Card.h"
#include "../Track/Track.h"
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

protected:
	virtual void BeginPlay() override;

public:
	ATrainGameMode();

	UPROPERTY(BlueprintReadWrite)
	TArray<UTrack*> AllTrack;

	UFUNCTION()
	void CreateTrackByEnum();

	UFUNCTION()
	TArray<FArray2D> ImportTrackData();

	UFUNCTION()
	void CreateCards();
};