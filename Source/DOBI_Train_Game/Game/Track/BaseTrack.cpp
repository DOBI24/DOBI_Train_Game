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
	UE_LOG(LogAudio, Warning, TEXT("Adding successfully %d"), Fields.Num());
}

void ABaseTrack::SR_ChangeOwner_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Benne"));
	MC_ChangeOwner();
}

void ABaseTrack::MC_ChangeOwner_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Multicast Change Owner"));
	HasTrackOwner = true;
}

