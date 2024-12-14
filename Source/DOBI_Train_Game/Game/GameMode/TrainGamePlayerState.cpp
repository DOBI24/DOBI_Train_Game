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
	DOREPLIFETIME(ATrainGamePlayerState, TrainCount);
	DOREPLIFETIME(ATrainGamePlayerState, StationCount);
	DOREPLIFETIME(ATrainGamePlayerState, Point);
	DOREPLIFETIME(ATrainGamePlayerState, Paths);
}


void ATrainGamePlayerState::SR_SetPlayerName_Implementation(const FString& Name)
{
	SetPlayerName(Name);
}

void ATrainGamePlayerState::SR_AddWagonCard_Implementation(FWagonCard Card)
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetOwningController());
	
	OwnedWagonCards[(int32)Card.Color].Amount++;
	OnRep_PlayerStatUpdate();

	if (OwnedWagonCards[(int32)Card.Color].Amount == 1) {
		Controller->CL_TriggerHUDWidget_WagonCards(Card.Color);
	}
}

void ATrainGamePlayerState::SR_RemoveWagonCard_Implementation(FWagonCard Card)
{
	OwnedWagonCards[(int32)Card.Color].Amount--;
	OnRep_PlayerStatUpdate();
}

void ATrainGamePlayerState::SR_AddRouteCard_Implementation(FRouteCard Card)
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetOwningController());

	OwnedRouteCards.Emplace(Card);
	Controller->CL_TriggerRouteWidgets_AddRouteCards(Card);
}

void ATrainGamePlayerState::SR_AddPoint_Implementation(int32 Amount)
{
	Point += Amount;
	OnRep_PlayerStatUpdate();
}

void ATrainGamePlayerState::SR_DecreaseTrainCount_Implementation(int32 Amount)
{
	TrainCount -= Amount;
	OnRep_PlayerStatUpdate();
}

void ATrainGamePlayerState::SR_AddTrack_Implementation(ABaseTrack* Track)
{
	OwnedTracks.Emplace(Track);

	AddNewPath(Track->LeftCity, Track->RightCity);
}

void ATrainGamePlayerState::AddNewPath(ECity LeftCity, ECity RightCity)
{
	int32 AddedIndex = -1;
	for (int32 i = 0; i < Paths.Num(); i++)
	{
		//Find existing track with same cities
		if ((AddedIndex == -1) && (Paths[i].CityList.Contains(LeftCity) || Paths[i].CityList.Contains(RightCity))) {
			Paths[i].CityList.AddUnique(LeftCity);
			Paths[i].CityList.AddUnique(RightCity);
			AddedIndex = i;
			continue;
		}

		//Find if another path contains one of the cities
		if (Paths[i].CityList.Contains(LeftCity) || Paths[i].CityList.Contains(RightCity)) {
			for (ECity City : Paths[i].CityList) {
				Paths[AddedIndex].CityList.AddUnique(City);
			}
			Paths.RemoveAt(i);
			return;
		}
	}
	if (AddedIndex == -1) Paths.Emplace(FPath(LeftCity, RightCity));
}

void ATrainGamePlayerState::SR_CheckCompletedRoutes_Implementation()
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetOwningController());

	for (int32 i = 0; i < OwnedRouteCards.Num(); i++) {
		if (OwnedRouteCards[i].Completed) continue;
		for (FPath Path : Paths) {
			if (Path.CityList.Contains(OwnedRouteCards[i].From) && Path.CityList.Contains(OwnedRouteCards[i].To)) {
				OwnedRouteCards[i].Completed = true;
				Controller->CL_OutlineCompletedRouteCard(i);
			}
		}
	}
}

void ATrainGamePlayerState::SR_AddCompletedRoutesPoints_Implementation()
{
	for(FRouteCard Card : OwnedRouteCards) {
		SR_AddPoint(Card.Completed ? Card.Point : Card.Point * -1);
	}
}

void ATrainGamePlayerState::OnRep_PlayerStatUpdate()
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->BP_UpdatePlayerStatsWidget(this);
}