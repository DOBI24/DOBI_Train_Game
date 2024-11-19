// @Copyright Marton Pal SZTE

#pragma once

#include "../City/City.h"
#include "../Card/Card.h"
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TrainGameState.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	WAITING_PLAYERS,
	DRAW_ROUTE_CARDS,
	DRAW_WAGON_CARDS,
	GAME,
	NEXT_PLAYER
};

USTRUCT(BlueprintType)
struct FRouteCard {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ECity From;

	UPROPERTY(BlueprintReadOnly)
	ECity To;

	UPROPERTY(BlueprintReadOnly)
	int32 Point;

	FRouteCard() {}

	FRouteCard(ECity InFrom, ECity InTo, int32 InPoint) : From(InFrom), To(InTo), Point(InPoint) {}
};

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API ATrainGameState : public AGameState
{
	GENERATED_BODY()

public:
	ATrainGameState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY()
	int32 ReadyPlayerCount;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<FRouteCard> RouteCards;

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<FRouteCard> LongRouteCards;

	UPROPERTY(ReplicatedUsing = OnRep_WagonCardsUpdate, BlueprintReadOnly)
	TArray<FWagonCard> WagonCards;

	UPROPERTY(ReplicatedUsing = OnRep_DiscardWagonCardsUpdate, BlueprintReadOnly)
	TArray<FWagonCard> DiscardWagonCards;

/* GAMESTATE */
	UPROPERTY(ReplicatedUsing = OnRep_CurrentGameStateUpdate, BlueprintReadOnly)
	EGameState CurrentGameState;

	UPROPERTY(Replicated, BlueprintReadOnly)
	ATrainGamePlayerState* CurrentPlayer;

	UPROPERTY(Replicated)
	int32 CurrentPlayerIndex;

	UPROPERTY()
	TArray<TObjectPtr<APlayerState>> ReadyQueue;

	UFUNCTION(Server, Reliable)
	void SR_SetGameState(EGameState NewGameState);

/* TIMER */
	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	int32 CurrentTime;

	UFUNCTION()
	void StartTimerTick(int32 Time);

	UFUNCTION(Server, Reliable)
	void SR_UpdateServerTimer();

	UFUNCTION(NetMulticast, Reliable)
	void MC_UpdateClientTimer(int32 Time);

/* SERVER FUNCTIONS */
	UFUNCTION(Server, Reliable)
	void SR_DrawStartRouteCards(ATrainGamePlayerState* PlayerState);

	UFUNCTION(Server, Reliable)
	void SR_DrawStartWagonCards(ATrainGamePlayerState* PlayerState, ATrainGamePlayerController* Controller);

	UFUNCTION(Server, Reliable)
	void SR_DrawWagonCard(FWagonCard Card, ATrainGamePlayerState* PlayerState, ATrainGamePlayerController* Controller);

	UFUNCTION()
	void CreateRouteCards();

	UFUNCTION()
	void CreateWagonCards();

	UFUNCTION(Server, Reliable)
	void SR_PlayerReadyToNextState(ATrainGamePlayerState* PlayerState);

	UFUNCTION(Server, Reliable)
	void SR_PlayerReadyToStart(ATrainGamePlayerState* PlayerState);

/* ONREP FUNCTIONS */
	UFUNCTION()
	void OnRep_WagonCardsUpdate();

	UFUNCTION()
	void OnRep_DiscardWagonCardsUpdate();

	UFUNCTION()
	void OnRep_CurrentGameStateUpdate();
};
