// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Track.h"
#include "../City/City.h"
#include "GameFramework/Actor.h"
#include "BaseTrack.generated.h"

UCLASS()
class DOBI_TRAIN_GAME_API ABaseTrack : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseTrack();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	bool HasTrackOwner;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	ETrack_Color TrackColor;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	ETrack_Type TrackType;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "TrackType == ETrack_Type::Ferry"))
	int32 FerryCount;

	UPROPERTY(Replicated, EditAnywhere)
	ECity LeftCity;

	UPROPERTY(Replicated, EditAnywhere)
	ECity RightCity;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 FieldCount;

	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<ABaseField*> Fields;

	UFUNCTION()
	void AddFieldToFields(ABaseField* field);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_SetTrackOwner(bool HasOwner);

	UFUNCTION(BlueprintPure)
	FVector GetTrackColorInVector();
};
