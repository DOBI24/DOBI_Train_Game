// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseField.h"
#include "../GameMode/TrainGamePlayerController.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseField::ABaseField() : StaticMeshColor(ETrack_Color::DEFAULT_VALUE)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;

	Parent = nullptr;
	CubeComponent = nullptr;
}

// Called when the game starts or when spawned
void ABaseField::BeginPlay()
{
	Super::BeginPlay();

	CubeComponent = FindComponentByClass<UStaticMeshComponent>();

	SetOwner(GetWorld()->GetFirstPlayerController());

	if (HasAuthority()) {
		InitializeParent();
		StaticMeshColor = Parent->TrackColor;
		OnRep_ColorUpdate();
	}
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
	DOREPLIFETIME(ABaseField, StaticMeshColor);
}

void ABaseField::InitializeParent()
{
	Parent->AddFieldToFields(this);
}

void ABaseField::HighlightOnClick()
{
	CubeComponent->SetRenderCustomDepth(!CubeComponent->bRenderCustomDepth);
}

void ABaseField::OnRep_ColorUpdate()
{
	if (!CubeComponent) return;

	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(CubeComponent->GetMaterial(0), this);
	DynMaterial->SetVectorParameterValue("Color", Parent->GetTrackColorInVector());
	CubeComponent->SetMaterial(0, DynMaterial);
}
