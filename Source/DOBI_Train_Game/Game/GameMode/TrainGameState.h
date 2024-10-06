// @Copyright Marton Pal SZTE

#pragma once

#include "../City/City.h"
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

	FRouteCard(){}

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

	UPROPERTY(BlueprintReadWrite, Replicated)
	TArray<FRouteCard> RouteCards;

	UPROPERTY(BlueprintReadWrite, Replicated)
	TArray<FRouteCard> LongRouteCards;

	UFUNCTION()
	void CreateRouteCards();
};
