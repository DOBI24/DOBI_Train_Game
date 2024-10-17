// @Copyright Marton Pal SZTE


#include "BaseTrack.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "../GameMode/TrainGamePlayerController.h"

// Sets default values
ABaseTrack::ABaseTrack() : FieldCount(0), FerryCount(0), HasTrackOwner(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ABaseTrack::BeginPlay()
{
	Super::BeginPlay();
	SetOwner(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void ABaseTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTrack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseTrack, HasTrackOwner);
	DOREPLIFETIME(ABaseTrack, TrackColor);
	DOREPLIFETIME(ABaseTrack, TrackType);
	DOREPLIFETIME(ABaseTrack, FieldCount);
	DOREPLIFETIME(ABaseTrack, Fields);
	DOREPLIFETIME(ABaseTrack, FerryCount);
	DOREPLIFETIME(ABaseTrack, LeftCity);
	DOREPLIFETIME(ABaseTrack, RightCity);
}

void ABaseTrack::AddFieldToFields(ABaseField* field)
{
	Fields.Emplace(field);
	FieldCount++;
}

FVector ABaseTrack::GetTrackColorInVector()
{
	FVector TrackColorRGB(0, 0, 0);
	switch (TrackColor)
	{
	case ETrack_Color::NO_COLOR:
		TrackColorRGB = { 144.0f, 150.0f, 150.0f };
		break;
	case ETrack_Color::PINK:
		 TrackColorRGB = { 189.0f, 135.0f, 174.0f};
		break;
	case ETrack_Color::WHITE:
		 TrackColorRGB = { 246.0f, 247.0f, 250.0f};
		break;
	case ETrack_Color::BLUE:
		 TrackColorRGB = { 56.0f, 156.0f, 213.0f};
		break;
	case ETrack_Color::YELLOW:
		 TrackColorRGB = { 230.0f, 228.0f, 60.0f};
		break;
	case ETrack_Color::ORANGE:
		 TrackColorRGB = { 214.0f, 135.0f, 44.0f};
		break;
	case ETrack_Color::BLACK:
		 TrackColorRGB = { 56.0f, 69.0f, 82.0f};
		break;
	case ETrack_Color::RED:
		 TrackColorRGB = { 185.0f, 31.0f, 39.0f};
		break;
	case ETrack_Color::GREEN:
		 TrackColorRGB = { 113.0f, 186.0f, 50.0f};
		break;
	}
	TrackColorRGB = TrackColorRGB / 255.0f;
	return TrackColorRGB;
}

void ABaseTrack::SR_SetTrackStaticMeshColor_Implementation(UStaticMeshComponent* Mesh)
{
	MC_SetTrackStaticMeshColor(Mesh);
}

void ABaseTrack::MC_SetTrackStaticMeshColor_Implementation(UStaticMeshComponent* Mesh)
{
	UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
	DynMaterial->SetVectorParameterValue("Color", GetTrackColorInVector());
	Mesh->SetMaterial(0, DynMaterial);
}

void ABaseTrack::SR_ChangeOwner_Implementation()
{
	MC_ChangeOwner();
}

void ABaseTrack::MC_ChangeOwner_Implementation()
{
	HasTrackOwner = true;
}

