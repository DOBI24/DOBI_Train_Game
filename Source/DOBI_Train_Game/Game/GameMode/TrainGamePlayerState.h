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

/**
 * 
 */
UCLASS()
class DOBI_TRAIN_GAME_API ATrainGamePlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	ATrainGamePlayerState();
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	EPlayer_Color PlayerColor;

	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<FWagonCard> OwnedWagonCards;

	UPROPERTY(Replicated)
	TArray<FRouteCard> OwnedRouteCards;

	UPROPERTY(Replicated)
	TArray<ABaseTrack*> OwnedTracks;

	UFUNCTION(BlueprintCallable)
	void SetPN(FString Name);
};
