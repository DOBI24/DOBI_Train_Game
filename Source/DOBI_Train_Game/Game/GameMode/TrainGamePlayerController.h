// @Copyright Marton Pal SZTE

#pragma once

#include "Blueprint/UserWidget.h"

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

private:
	UPROPERTY(EditAnywhere)
	TMap<FString, TSubclassOf<UUserWidget>> WidgetReferences;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void LocalBeginPlay();

	UFUNCTION()
	void CheckLocalBegin();

public:
/* TIMER */
	UPROPERTY()
	int32 CurrentTime;

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeTimeWidget(int32 Time);

/* SERVER FUNCTIONS */
	UFUNCTION(Server, Reliable)
	void SR_CallDrawStartCards(const FString& CardType, ATrainGamePlayerState* PlayerStateParam, ATrainGamePlayerController* ControllerParam);

	UFUNCTION(Server, Reliable)
	void SR_SetPlayerName(ATrainGamePlayerState* PlayerStateParam, const FString& Name);

	UFUNCTION(Server, Reliable)
	void SR_PlayerReady(ATrainGamePlayerState* PlayerStateParam);

/* CLIENT FUNCTIONS */
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void CL_CallDrawStartCards(const FString& CardType);

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void CL_TriggerReadyPlayer();

	UFUNCTION(Client, Reliable)
	void CL_SetPlayerName();

	UFUNCTION(Client, Reliable)
	void CL_TriggerHUDWidget_WagonCards(ECard_Color CardColor);

/* BLUEPRINT FUNCTIONS */
	UFUNCTION(BlueprintImplementableEvent)
	void BP_TriggerHUDWidget_WagonCards(ECard_Color CardColor);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdatePlayerStatsWidget(ATrainGamePlayerState* PlayerStateParam);

/* UI FUNCTIONS */
	UFUNCTION(BlueprintImplementableEvent)
	void CreatePlayerUI(TSubclassOf<UUserWidget> WidgetClass);

/* FUNCTIONS */
	UFUNCTION()
	void CheckCurrentGameState(ATrainGamePlayerState* CurrentPlayer = nullptr);
};
