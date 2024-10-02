// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TrainGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API ATrainGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATrainGamePlayerController();

protected:
	virtual void BeginPlay() override;
};
