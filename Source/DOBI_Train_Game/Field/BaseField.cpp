// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseField.h"
#include "../GameMode/TrainGameMode.h"

// Sets default values
ABaseField::ABaseField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseField::BeginPlay()
{
	Super::BeginPlay();

	ATrainGameMode* GameMode= (ATrainGameMode*)(GetWorld()->GetAuthGameMode());
	parent = GameMode->AllTrack[(uint8)(TrackRouteEnum)];
	if (!parent){
		UE_LOG(LogTemp, Error, TEXT("Failed to find parent track for field %s"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Found parent track for field %d"), parent->TrackColor);
	parent->AddFieldToFields(this);

}

// Called every frame
void ABaseField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

