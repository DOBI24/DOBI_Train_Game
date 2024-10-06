// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseField.h"
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

	Parent = nullptr;
}

// Called when the game starts or when spawned
void ABaseField::BeginPlay()
{
	Super::BeginPlay();
	if (!Parent) {
		UE_LOG(LogTemp, Warning, TEXT("Field has no parent"));
	}
	SetOwner(GetWorld()->GetFirstPlayerController());
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
	Parent->AddFieldToFields(this);
}
