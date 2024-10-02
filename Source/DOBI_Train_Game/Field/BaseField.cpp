// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseField.h"
#include "../GameMode/TrainGameMode.h"
#include "../GameMode/TrainGameState.h"
#include "../GameMode/TrainGamePlayerController.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseField::ABaseField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ABaseField::BeginPlay()
{
	Super::BeginPlay();
	SetOwner(GetWorld()->GetFirstPlayerController());

	// InitializeParent will be called on the server;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseField::InitializeParent, 1.0f, false);
}

// Called every frame
void ABaseField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseField::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseField, Parent);
}

void ABaseField::InitializeParent()
{
	if (GetLocalRole() == ROLE_Authority) {
		ATrainGameMode* GameMode = Cast<ATrainGameMode>(GetWorld()->GetAuthGameMode());
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("GameMode: %d"), GameMode->AllTrack.Num()));

		Parent = GameMode->AllTrack[(uint8)(TrackRouteEnum)];
		Parent->AddFieldToFields(this);
	}
}
