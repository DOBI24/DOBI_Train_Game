// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API ATrainGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	static const int32 MAX_TRAIN_COUNT = 45;
	static const int32 MAX_STATION_COUNT = 3;

	ATrainGameMode();
};
