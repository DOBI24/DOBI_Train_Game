// @Copyright Marton Pal SZTE


#include "TrainGameState.h"
#include "Net/UnrealNetwork.h"

ATrainGameState::ATrainGameState()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	if (HasAuthority()) {
		CreateRouteCards();
	}

}

void ATrainGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ATrainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATrainGameState, RouteCards);
	DOREPLIFETIME(ATrainGameState, LongRouteCards);
}

void ATrainGameState::CreateRouteCards()
{
	RouteCards = {
		{ ECity::FRANKFURT, ECity::KOBENHAVN, 5},
		{ ECity::MADRID, ECity::DIEPPE, 8},
		{ ECity::KYIV, ECity::PETROGRAD, 6},
		{ ECity::FRANKFURT, ECity::SMOLENSK, 13},
		{ ECity::LONDON, ECity::BERLIN, 7},
		{ ECity::VENEZIA, ECity::CONSTANTINOPLE, 10},
		{ ECity::KYIV, ECity::SOCHI, 8},
		{ ECity::BERLIN, ECity::MOSKVA, 12},
		{ ECity::AMSTERDAM, ECity::WILNO, 12},
		{ ECity::AMSTERDAM, ECity::PAMPLONA, 7},
		{ ECity::BARCELONA, ECity::MUNCHEN, 8},
		{ ECity::PALERMO, ECity::CONSTANTINOPLE, 8},
		{ ECity::PARIS, ECity::WIEN, 8},
		{ ECity::BREST, ECity::MARSEILLE, 7},
		{ ECity::EDINBURGH, ECity::PARIS, 7},
		{ ECity::ATHINA, ECity::ANGORA, 5},
		{ ECity::ZAGRAB, ECity::BRINDISI, 6},
		{ ECity::ERZURUM, ECity::ROSTOV, 5},
		{ ECity::SMOLENSK, ECity::ROSTOV, 8},
		{ ECity::SOFIA, ECity::SMYRNA, 5},
		{ ECity::BREST, ECity::VENEZIA, 8},
		{ ECity::ANGORA, ECity::KHARKOV, 10},
		{ ECity::LONDON, ECity::WIEN, 10},
		{ ECity::SARAJEVO, ECity::SEVASTOPOL, 8},
		{ ECity::MARSEILLE, ECity::ESSEN, 8},
		{ ECity::MADRID, ECity::ZURICH, 8},
		{ ECity::BUDAPEST, ECity::SOFIA, 5},
		{ ECity::ZURICH, ECity::BRINDISI, 6},
		{ ECity::ROMA, ECity::SMYRNA, 8},
		{ ECity::ZURICH, ECity::BUDAPEST, 6},
		{ ECity::BERLIN, ECity::ROMA, 9},
		{ ECity::STOCKHOLM, ECity::WIEN, 11},
		{ ECity::ATHINA, ECity::WILNO, 11},
		{ ECity::PARIS, ECity::ZAGRAB, 7},
		{ ECity::RIGA, ECity::BUCURESTI, 10},
		{ ECity::ESSEN, ECity::KYIV, 10},
		{ ECity::BRUXELLES, ECity::DANZIG, 9},
		{ ECity::BERLIN, ECity::BUCURESTI, 8},
		{ ECity::WARSZAWA, ECity::SMOLENSK, 6},
		{ ECity::BARCELONA, ECity::BRUXELLES, 8}
	};
	LongRouteCards = {
		{ ECity::PALERMO, ECity::MOSKVA, 20},
		{ ECity::BREST, ECity::PETROGRAD, 20 },
		{ ECity::LISBOA, ECity::DANZIG, 20},
		{ ECity::KOBENHAVN, ECity::ERZURUM, 21},
		{ ECity::CADIZ, ECity::STOCKHOLM, 21},
		{ ECity::EDINBURGH, ECity::ATHINA, 21}
	};
}
