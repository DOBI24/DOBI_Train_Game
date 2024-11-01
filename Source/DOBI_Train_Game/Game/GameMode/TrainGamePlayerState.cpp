// @Copyright Marton Pal SZTE


#include "TrainGamePlayerState.h"
#include "Net/UnrealNetwork.h"
#include "TrainGamePlayerController.h"

ATrainGamePlayerState::ATrainGamePlayerState()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	OwnedWagonCards = {
		FWagonCard(ECard_Color::LOCOMOTIVE),
		FWagonCard(ECard_Color::PINK),
		FWagonCard(ECard_Color::WHITE),
		FWagonCard(ECard_Color::BLUE),
		FWagonCard(ECard_Color::YELLOW),
		FWagonCard(ECard_Color::ORANGE),
		FWagonCard(ECard_Color::BLACK),
		FWagonCard(ECard_Color::RED),
		FWagonCard(ECard_Color::GREEN)
	};
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

void ATrainGamePlayerState::AddWagonCard(FWagonCard Card, ATrainGamePlayerController* Controller)
{
	OwnedWagonCards[(int32)Card.Color].Amount++;
	if (OwnedWagonCards[(int32)Card.Color].Amount == 1) {
		Controller->CL_TriggerHUDWidget_WagonCards(Card.Color);
	}
}
