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

	UFUNCTION(BlueprintCallable)
	void CallDrawStartCards();

	UFUNCTION(Server, Reliable)
	void SR_CallDrawStartCards(ATrainGamePlayerState* PlayerStateParam, ATrainGamePlayerController* ControllerParam);

	UFUNCTION(BlueprintImplementableEvent)
	void TriggerHUDWidget_WagonCards(ECard_Color CardColor);

	UFUNCTION(Client, Reliable)
	void CL_TriggerHUDWidget_WagonCards(ECard_Color CardColor);
};
