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

protected:
	virtual void BeginPlay() override;

public:
	ATrainGamePlayerController();

	UFUNCTION()
	void CallDrawStartCards();

	UFUNCTION(Server, Reliable)
	void SR_CallDrawStartCards(ATrainGamePlayerState* PlayerStateParam);
};
