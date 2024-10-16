// @Copyright Marton Pal SZTE

#pragma once

#include "CoreMinimal.h"
#include "Track.h"
#include "../City/City.h"
#include "GameFramework/Actor.h"
#include "BaseTrack.generated.h"

UCLASS()
class DOBI_TRAIN_GAME_API ABaseTrack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	bool HasTrackOwner;

	UPROPERTY(Replicated, EditAnywhere)
	ETrack_Color TrackColor;

	UPROPERTY(Replicated, EditAnywhere)
	ETrack_Type TrackType;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 FieldCount;

	UPROPERTY(Replicated, BlueprintReadOnly)
	TArray<ABaseField*> Fields;

	UPROPERTY(Replicated, EditAnywhere, meta = (EditCondition = "TrackType == ETrack_Type::Ferry"))
	int32 FerryCount;

	UPROPERTY(Replicated, EditAnywhere)
	ECity LeftCity;

	UPROPERTY(Replicated, EditAnywhere)
	ECity RightCity;

	UFUNCTION()
	void AddFieldToFields(ABaseField* field);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SR_ChangeOwner();

	UFUNCTION(NetMulticast, Reliable)
	void MC_ChangeOwner();
};
