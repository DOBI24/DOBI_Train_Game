// @Copyright Marton Pal SZTE


#include "TrainGamePlayerState.h"
#include "Net/UnrealNetwork.h"

ATrainGamePlayerState::ATrainGamePlayerState()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ATrainGamePlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ATrainGamePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATrainGamePlayerState, OwnedRouteCards);
	DOREPLIFETIME(ATrainGamePlayerState, OwnedWagonCards);
	DOREPLIFETIME(ATrainGamePlayerState, OwnedTracks);
	DOREPLIFETIME(ATrainGamePlayerState, PlayerColor);
}


void ATrainGamePlayerState::SetPN(FString Name)
{
	SetPlayerName(Name);
}
