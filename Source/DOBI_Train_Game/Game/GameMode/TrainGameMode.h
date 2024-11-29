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
	/* PLAYER CONSTANTS */
	inline static const int32 MAX_TRAIN_COUNT = 45;
	inline static const int32 MAX_STATION_COUNT = 3;

	/* TIMER CONSTANTS */
	inline static const int32 DRAW_ROUTE_TIME = 30;
	inline static const int32 GAME_TIME = 60;

	static TMap<int32, int32> POINT_FROM_LENGTH;

	ATrainGameMode();
};
