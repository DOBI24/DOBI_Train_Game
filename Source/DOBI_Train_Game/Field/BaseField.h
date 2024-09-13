// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DOBI_Train_Game/Track/Track.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseField.generated.h"

UCLASS()
class DOBI_TRAIN_GAME_API ABaseField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UTrack* parent;

	UPROPERTY(EditAnywhere)
	ETrack_Route TrackRouteEnum;
};
