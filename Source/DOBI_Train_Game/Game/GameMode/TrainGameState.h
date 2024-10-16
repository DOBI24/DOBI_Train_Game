// @Copyright Marton Pal SZTE

#pragma once

#include "../City/City.h"
#include "../Card/Card.h"
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TrainGameState.generated.h"

USTRUCT(BlueprintType)
struct FRouteCard {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ECity From;

	UPROPERTY()
	ECity To;

	UPROPERTY()
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

protected:
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:
	ATrainGameState();

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<FRouteCard> RouteCards;

	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<FRouteCard> LongRouteCards;

	UPROPERTY(ReplicatedUsing=OnRep_WagonCardsUpdate, BlueprintReadOnly)
	TArray<FWagonCard> WagonCards;

	UFUNCTION()
	void OnRep_WagonCardsUpdate();

	UFUNCTION()
	void CreateRouteCards();

	UFUNCTION()
	void CreateWagonCards();

	UFUNCTION(Server, Reliable)
	void DrawStartCards(ATrainGamePlayerState* PlayerState);
};
