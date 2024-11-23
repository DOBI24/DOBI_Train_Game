// @Copyright Marton Pal SZTE


#include "BaseTrack.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "../GameMode/TrainGamePlayerController.h"

// Sets default values
ABaseTrack::ABaseTrack() : HasTrackOwner(false), FieldCount(0), FerryCount(0)
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

void ABaseTrack::SR_SetTrackOwner_Implementation(bool HasOwner)
{
	HasTrackOwner = HasOwner;
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
		 TrackColorRGB = { 190.0f, 130.0f, 180.0f};
		break;
	case ETrack_Color::WHITE:
		 TrackColorRGB = { 250.0f, 250.0f, 250.0f};
		break;
	case ETrack_Color::BLUE:
		 TrackColorRGB = { 60.0f, 160.0f, 215.0f};
		break;
	case ETrack_Color::YELLOW:
		 TrackColorRGB = { 230.0f, 230.0f, 60.0f};
		break;
	case ETrack_Color::ORANGE:
		 TrackColorRGB = { 215.0f, 135.0f, 45.0f};
		break;
	case ETrack_Color::BLACK:
		 TrackColorRGB = { 60.0f, 60.0f, 60.0f};
		break;
	case ETrack_Color::RED:
		 TrackColorRGB = { 185.0f, 30.0f, 40.0f};
		break;
	case ETrack_Color::GREEN:
		 TrackColorRGB = { 115.0f, 190.0f, 50.0f};
		break;
	}
	TrackColorRGB = TrackColorRGB / 255.0f;
	return TrackColorRGB;
}