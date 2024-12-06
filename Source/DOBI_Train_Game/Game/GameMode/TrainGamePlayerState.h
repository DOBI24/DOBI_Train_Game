// @Copyright Marton Pal SZTE

#pragma once

#include "../Track/BaseTrack.h"
#include "../Card/Card.h"
#include "../Character/GameCharacter.h"
#include "TrainGameState.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TrainGamePlayerState.generated.h"

UENUM()
enum class EPlayer_Color : uint8
{
	BLUE,
	YELLOW,
	BLACK,
	RED,
	GREEN
};

USTRUCT(BlueprintType)
struct FPath {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<ECity> CityList;

	FPath(ECity LeftCity, ECity RightCity) {
		CityList.AddUnique(LeftCity);
		CityList.AddUnique(RightCity);
	}

	FPath() {}
};

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API ATrainGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATrainGamePlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(Replicated, BlueprintReadOnly)
	EPlayer_Color PlayerColor;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerStatUpdate, BlueprintReadWrite)
	int32 TrainCount;

	UPROPERTY(Replicated, BlueprintReadWrite)
	int32 StationCount;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerStatUpdate, BlueprintReadOnly)
	TArray<FWagonCard> OwnedWagonCards;

	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<FRouteCard> OwnedRouteCards;

	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<ABaseTrack*> OwnedTracks;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerStatUpdate, BlueprintReadOnly)
	int32 Point;

	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<FPath> Paths;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_SetPlayerName(const FString& Name);

	UFUNCTION(Server, Reliable)
	void SR_AddWagonCard(FWagonCard Card);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_RemoveWagonCard(FWagonCard Card);

	UFUNCTION(Server, Reliable)
	void SR_AddRouteCard(FRouteCard Card);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_AddPoint(int32 Amount);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_DecreaseTrainCount(int32 Amount);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_AddTrack(ABaseTrack* Track);

	UFUNCTION()
	void AddNewPath(ECity LeftCity, ECity RightCity);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_CheckCompletedRoutes();

	UFUNCTION(Server, Reliable)
	void SR_AddCompletedRoutesPoints();

	/* OnRep FUNCTION */
	UFUNCTION()
	void OnRep_PlayerStatUpdate();
};
