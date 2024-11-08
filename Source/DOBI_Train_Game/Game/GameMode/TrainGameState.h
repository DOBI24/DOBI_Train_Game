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

private:
	UPROPERTY()
	int32 ReadyPlayerCount;

protected:
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:
	ATrainGameState();

	UPROPERTY(ReplicatedUsing = OnRep_CurrentGameStateUpdate, BlueprintReadOnly)
	EGameState CurrentGameState;
	
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<FRouteCard> RouteCards;

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<FRouteCard> LongRouteCards;

	UPROPERTY(ReplicatedUsing = OnRep_WagonCardsUpdate, BlueprintReadOnly)
	TArray<FWagonCard> WagonCards;

	UPROPERTY(ReplicatedUsing = OnRep_DiscardWagonCardsUpdate, BlueprintReadOnly)
	TArray<FWagonCard> DiscardWagonCards;

	UFUNCTION()
	void CreateRouteCards();

	UFUNCTION()
	void CreateWagonCards();

	UFUNCTION(Server, Reliable)
	void DrawStartRouteCards(ATrainGamePlayerState* PlayerState);

	UFUNCTION(Server, Reliable)
	void DrawStartWagonCards(ATrainGamePlayerState* PlayerState, ATrainGamePlayerController* Controller);

	UFUNCTION()
	void PlayerReadyToNextState(ATrainGamePlayerState* PlayerState);

	UFUNCTION()
	void OnRep_WagonCardsUpdate();

	UFUNCTION()
	void OnRep_DiscardWagonCardsUpdate();

	UFUNCTION()
	void OnRep_CurrentGameStateUpdate();
};
