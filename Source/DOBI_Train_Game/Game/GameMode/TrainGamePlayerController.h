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
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_CallDrawCards(const FString& CardType);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_CallDrawWagonCards();

	UFUNCTION(Server, Reliable)
	void SR_SetPlayerName(ATrainGamePlayerState* PlayerStateParam, const FString& Name);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_PlayerReady();

/* CLIENT FUNCTIONS */
	UFUNCTION(Client, Reliable)
	void CL_SetPlayerName();

	UFUNCTION(Client, Reliable)
	void CL_TriggerHUDWidget_WagonCards(ECard_Color CardColor);

	UFUNCTION(Client, Reliable)
	void CL_TriggerRouteWidgets_AddRouteCards(FRouteCard Card);

	UFUNCTION(Client, Reliable)
	void SetInputModeByServer(bool GameAndUI);

	UFUNCTION(BlueprintPure)
	bool CanInteract();

	UFUNCTION(Client, Reliable)
	void CL_OutlineCompletedRouteCard(int32 Index);

/* BLUEPRINT FUNCTIONS */
	UFUNCTION(BlueprintImplementableEvent)
	void BP_TriggerHUDWidget_WagonCards(ECard_Color CardColor);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_TriggerRouteWidgets_AddRouteCards(FRouteCard Card);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_UpdatePlayerStatsWidget(APlayerState* PlayerStateParam);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OutlineCurrentPlayer(APlayerState* PlayerStateParam);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_DeselectTrack();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OutlineCompletedRouteCard(int32 Index);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ChangeWinnerName(const FString& Name);

/* UI FUNCTIONS */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchScene(TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleGameMenu(TSubclassOf<UUserWidget> WidgetClass);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleDrawButtonEnable(bool InIsEnabled);

/* GAMEMODE GETTERS */
	UFUNCTION(BlueprintPure)
	TMap<int32, int32> GetPOINT_FROM_LENGTH();

/* FUNCTIONS */
	UFUNCTION()
	void CheckCurrentGameState(ATrainGamePlayerState* CurrentPlayer = nullptr);
};
