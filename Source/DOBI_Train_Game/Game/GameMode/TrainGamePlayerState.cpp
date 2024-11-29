// @Copyright Marton Pal SZTE


#include "TrainGamePlayerState.h"
#include "Net/UnrealNetwork.h"
#include "TrainGamePlayerController.h"
#include "TrainGameMode.h"

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

	TrainCount = ATrainGameMode::MAX_TRAIN_COUNT;
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
	DOREPLIFETIME(ATrainGamePlayerState, TrainCount);
	DOREPLIFETIME(ATrainGamePlayerState, StationCount);
	DOREPLIFETIME(ATrainGamePlayerState, Point);
}


void ATrainGamePlayerState::SR_SetPlayerName_Implementation(const FString& Name)
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

void ATrainGamePlayerState::AddRouteCard(FRouteCard Card, ATrainGamePlayerController* Controller)
{
	OwnedRouteCards.Emplace(Card);
	Controller->CL_TriggerRouteWidgets_AddRouteCards(Card);
}

void ATrainGamePlayerState::SR_AddPoint_Implementation(int32 Amount)
{
	Point += Amount;
	OnRep_PlayerStatUpdate();
}

void ATrainGamePlayerState::OnRep_PlayerStatUpdate()
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->BP_UpdatePlayerStatsWidget(this);
}