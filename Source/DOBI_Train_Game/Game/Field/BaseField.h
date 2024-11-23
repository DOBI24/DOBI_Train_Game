// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Track/Track.h"
#include "../Track/BaseTrack.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseField.generated.h"

UCLASS()
class DOBI_TRAIN_GAME_API ABaseField : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseField();
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	ABaseTrack* Parent;

	UPROPERTY()
	UStaticMeshComponent* FieldComponent;

	UFUNCTION()
	void InitializeParent();

	UPROPERTY(ReplicatedUsing = OnRep_ColorUpdate)
	ETrack_Color StaticMeshColor;

	UFUNCTION(BlueprintCallable)
	void HighlightOnClick();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void MC_ChangeFieldComponentStaticMeshToRail(UStaticMesh* NewStaticMesh);

	UFUNCTION()
	void OnRep_ColorUpdate();
};
