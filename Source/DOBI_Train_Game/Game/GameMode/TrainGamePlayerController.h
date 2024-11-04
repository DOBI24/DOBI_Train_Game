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

private:
	void TriggerReadyPlayer();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void LocalBeginPlay();

	UFUNCTION()
	void CheckLocalBegin();

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

	UFUNCTION()
	void SetPlayerName();

	UFUNCTION(Server, Reliable)
	void SR_SetPlayerName(ATrainGamePlayerState* PlayerStateParam, const FString& Name);

	UFUNCTION(Server, Reliable)
	void SR_PlayerReady(ATrainGamePlayerState* PlayerStateParam);

	/* UI functions */
	UFUNCTION(BlueprintImplementableEvent)
	void CreateWaitingPlayerUI();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateDrawRouteCardUI();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateGameUI();

	UFUNCTION()
	void CheckCurrentGameState();
};
