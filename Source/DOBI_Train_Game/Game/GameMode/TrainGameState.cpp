// @Copyright Marton Pal SZTE


#include "TrainGameState.h"
#include "Net/UnrealNetwork.h"
#include "TrainGamePlayerState.h"
#include "TrainGameplayerController.h"

ATrainGameState::ATrainGameState() : ReadyPlayerCount(0)
{
	bReplicates = true;
	bAlwaysRelevant = true;

	
	if (HasAuthority()) {
		CreateRouteCards();
		CreateWagonCards();
	}
}

void ATrainGameState::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		CurrentGameState = EGameState::WAITING_PLAYERS;
		OnRep_CurrentGameStateUpdate();
	}
}

void ATrainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATrainGameState, CurrentGameState);
	DOREPLIFETIME(ATrainGameState, RouteCards);
	DOREPLIFETIME(ATrainGameState, LongRouteCards);
	DOREPLIFETIME(ATrainGameState, WagonCards);
	DOREPLIFETIME(ATrainGameState, DiscardWagonCards);
}

void ATrainGameState::CreateRouteCards()
{
	RouteCards = {
		FRouteCard(ECity::FRANKFURT, ECity::KOBENHAVN, 5),
		FRouteCard(ECity::MADRID, ECity::DIEPPE, 8),
		FRouteCard(ECity::KYIV, ECity::PETROGRAD, 6),
		FRouteCard(ECity::FRANKFURT, ECity::SMOLENSK, 13),
		FRouteCard(ECity::LONDON, ECity::BERLIN, 7),
		FRouteCard(ECity::VENEZIA, ECity::CONSTANTINOPLE, 10),
		FRouteCard(ECity::KYIV, ECity::SOCHI, 8),
		FRouteCard(ECity::BERLIN, ECity::MOSKVA, 12),
		FRouteCard(ECity::AMSTERDAM, ECity::WILNO, 12),
		FRouteCard(ECity::AMSTERDAM, ECity::PAMPLONA, 7),
		FRouteCard(ECity::BARCELONA, ECity::MUNCHEN, 8),
		FRouteCard(ECity::PALERMO, ECity::CONSTANTINOPLE, 8),
		FRouteCard(ECity::PARIS, ECity::WIEN, 8),
		FRouteCard(ECity::BREST, ECity::MARSEILLE, 7),
		FRouteCard(ECity::EDINBURGH, ECity::PARIS, 7),
		FRouteCard(ECity::ATHINA, ECity::ANGORA, 5),
		FRouteCard(ECity::ZAGRAB, ECity::BRINDISI, 6),
		FRouteCard(ECity::ERZURUM, ECity::ROSTOV, 5),
		FRouteCard(ECity::SMOLENSK, ECity::ROSTOV, 8),
		FRouteCard(ECity::SOFIA, ECity::SMYRNA, 5),
		FRouteCard(ECity::BREST, ECity::VENEZIA, 8),
		FRouteCard(ECity::ANGORA, ECity::KHARKOV, 10),
		FRouteCard(ECity::LONDON, ECity::WIEN, 10),
		FRouteCard(ECity::SARAJEVO, ECity::SEVASTOPOL, 8),
		FRouteCard(ECity::MARSEILLE, ECity::ESSEN, 8),
		FRouteCard(ECity::MADRID, ECity::ZURICH, 8),
		FRouteCard(ECity::BUDAPEST, ECity::SOFIA, 5),
		FRouteCard(ECity::ZURICH, ECity::BRINDISI, 6),
		FRouteCard(ECity::ROMA, ECity::SMYRNA, 8),
		FRouteCard(ECity::ZURICH, ECity::BUDAPEST, 6),
		FRouteCard(ECity::BERLIN, ECity::ROMA, 9),
		FRouteCard(ECity::STOCKHOLM, ECity::WIEN, 11),
		FRouteCard(ECity::ATHINA, ECity::WILNO, 11),
		FRouteCard(ECity::PARIS, ECity::ZAGRAB, 7),
		FRouteCard(ECity::RIGA, ECity::BUCURESTI, 10),
		FRouteCard(ECity::ESSEN, ECity::KYIV, 10),
		FRouteCard(ECity::BRUXELLES, ECity::DANZIG, 9),
		FRouteCard(ECity::BERLIN, ECity::BUCURESTI, 8),
		FRouteCard(ECity::WARSZAWA, ECity::SMOLENSK, 6),
		FRouteCard(ECity::BARCELONA, ECity::BRUXELLES, 8)
	};
	LongRouteCards = {
		FRouteCard(ECity::PALERMO, ECity::MOSKVA, 20),
		FRouteCard(ECity::BREST, ECity::PETROGRAD, 20 ),
		FRouteCard(ECity::LISBOA, ECity::DANZIG, 20),
		FRouteCard(ECity::KOBENHAVN, ECity::ERZURUM, 21),
		FRouteCard(ECity::CADIZ, ECity::STOCKHOLM, 21),
		FRouteCard(ECity::EDINBURGH, ECity::ATHINA, 21)
	};
}

void ATrainGameState::CreateWagonCards()
{
	WagonCards.Emplace(FWagonCard(ECard_Color::LOCOMOTIVE));
	WagonCards.Emplace(FWagonCard(ECard_Color::LOCOMOTIVE));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			WagonCards.Emplace(FWagonCard(ECard_Color(i)));
		}
	}
	OnRep_WagonCardsUpdate();
}

void ATrainGameState::PlayerReadyToNextState(ATrainGamePlayerState* PlayerState)
{
	if (PlayerArray.Contains(PlayerState)) {
		ReadyPlayerCount++;
		UE_LOG(LogTemp, Warning, TEXT("Erte %d"), ReadyPlayerCount);
		if (ReadyPlayerCount == PlayerArray.Num())
		{
			ReadyPlayerCount = 0;
			CurrentGameState = EGameState((int)CurrentGameState + 1);
			//CurrentGameState = EGameState::DRAW_ROUTE_CARDS;
			OnRep_CurrentGameStateUpdate();
		}
	}
}

void ATrainGameState::DrawStartRouteCards_Implementation(ATrainGamePlayerState* PlayerState)
{
	//Draw 1 Long route card
	PlayerState->OwnedRouteCards.Emplace(LongRouteCards.Last());
	LongRouteCards.RemoveAt(LongRouteCards.Num() - 1);

	//Draw 3 route cards
	for (int i = 0; i < 3; i++)
	{
		PlayerState->OwnedRouteCards.Emplace(RouteCards.Last());
		RouteCards.RemoveAt(RouteCards.Num() - 1);
	}
}

void ATrainGameState::DrawStartWagonCards_Implementation(ATrainGamePlayerState* PlayerState, ATrainGamePlayerController* Controller)
{
	//Draw 4 wagon cards
	for (int i = 0; i < 4; i++)
	{
		PlayerState->AddWagonCard(WagonCards.Last(), Controller);
		WagonCards.RemoveAt(WagonCards.Num()-1);
	}
	OnRep_WagonCardsUpdate();
}

/* OnRep functions */

void ATrainGameState::OnRep_WagonCardsUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT("update"));
}

void ATrainGameState::OnRep_DiscardWagonCardsUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT("update"));
}

void ATrainGameState::OnRep_CurrentGameStateUpdate()
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetWorld()->GetFirstPlayerController());
	
	if (Controller)
	{
		Controller->CheckCurrentGameState();
	}
}