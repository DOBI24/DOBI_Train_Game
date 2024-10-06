// @Copyright Marton Pal SZTE


#include "Game/Track/BaseTrack.h"

// Sets default values
ABaseTrack::ABaseTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

