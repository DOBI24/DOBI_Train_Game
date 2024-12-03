// @Copyright Marton Pal SZTE


#include "TrainGameState.h"
#include "Net/UnrealNetwork.h"
#include "TrainGamePlayerState.h"
#include "TrainGameplayerController.h"
#include "TrainGameMode.h"

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
		SR_SetGameState(EGameState::WAITING_PLAYERS);
	}
}

void ATrainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATrainGameState, CurrentGameState);
	DOREPLIFETIME(ATrainGameState, RouteCards);
	DOREPLIFETIME(ATrainGameState, LongRouteCards);
	DOREPLIFETIME(ATrainGameState, WagonCards);
	DOREPLIFETIME(ATrainGameState, ShopWagonCards);
	DOREPLIFETIME(ATrainGameState, DiscardWagonCards);
	DOREPLIFETIME(ATrainGameState, CurrentPlayer);
	DOREPLIFETIME(ATrainGameState, CurrentPlayerIndex);
}

// Game state controller
void ATrainGameState::SR_SetGameState_Implementation(EGameState NewGameState)
{
	ATrainGamePlayerController* Controller = nullptr;

	GetWorldTimerManager().ClearTimer(TimerHandle);
	ReadyQueue.Empty();

	switch (NewGameState)
	{
	case EGameState::WAITING_PLAYERS:
		break;
	case EGameState::DRAW_ROUTE_CARDS:
		StartTimerTick(ATrainGameMode::DRAW_ROUTE_TIME);
		ReadyQueue = PlayerArray;
		break;
	case EGameState::DRAW_WAGON_CARDS:
		//SR_FillShopWagonCards();
		CurrentPlayerIndex = -1;
		StartTimerTick(3);
		break;
	case EGameState::GAME:
		CurrentPlayerIndex++;
		if (CurrentPlayerIndex == PlayerArray.Num()) {
			CurrentPlayerIndex = 0;
		}

		CurrentPlayer = Cast<ATrainGamePlayerState>(PlayerArray[CurrentPlayerIndex]);
		Controller = Cast<ATrainGamePlayerController>(CurrentPlayer->GetPlayerController());
		Controller->SetInputModeByServer(true);

		StartTimerTick(ATrainGameMode::GAME_TIME);
		ReadyQueue.Emplace(CurrentPlayer);

		break;
	case EGameState::NEXT_PLAYER:
		Controller = Cast<ATrainGamePlayerController>(CurrentPlayer->GetPlayerController());
		Controller->SetInputModeByServer(false);
		StartTimerTick(3);

		BP_CheckWagonCardCount();

		break;
	}

	CurrentGameState = NewGameState;
	OnRep_CurrentGameStateUpdate();
}

/* TIMER */
void ATrainGameState::StartTimerTick(int32 Time)
{
	CurrentTime = Time;
	SR_UpdateServerTimer();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrainGameState::SR_UpdateServerTimer, 1.0f, true);
}

void ATrainGameState::SR_UpdateServerTimer_Implementation()
{
	MC_UpdateClientTimer(CurrentTime);

	if (CurrentTime == 0) {
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SR_PlayerReadyToNextState();
	}

	CurrentTime--;
}

void ATrainGameState::MC_UpdateClientTimer_Implementation(int32 Time)
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangeTimeWidget(Time);
}

/* DRAW CARDS */
void ATrainGameState::SR_DrawRouteCards_Implementation(ATrainGamePlayerState* PlayerState)
{
	int32 Amount = 0;

	if (CurrentGameState == EGameState::DRAW_ROUTE_CARDS) {
		//Draw 1 Long route card
		PlayerState->SR_AddRouteCard(LongRouteCards.Last());
		LongRouteCards.RemoveAt(LongRouteCards.Num() - 1);
	}

	while (Amount < 3 && RouteCards.Num() != 0) {
		PlayerState->SR_AddRouteCard(RouteCards.Last());
		RouteCards.RemoveAt(RouteCards.Num() - 1);
		Amount++;
	}
}

void ATrainGameState::SR_DrawStartWagonCards_Implementation(ATrainGamePlayerState* PlayerState)
{
	//Draw 4 wagon cards
	for (int i = 0; i < 4; i++)
	{
		PlayerState->SR_AddWagonCard(WagonCards.Last());
		WagonCards.RemoveAt(WagonCards.Num() - 1);
		
		//--------- DEBUG ---------
		PlayerState->SR_AddWagonCard(FWagonCard(ECard_Color::LOCOMOTIVE));
		//--------- DEBUG ---------
	}
	OnRep_WagonCardsUpdate();
}

void ATrainGameState::SR_DrawWagonCard_Implementation(int32 Amount, ATrainGamePlayerState* PlayerState)
{
	for (int32 i = 0; i < Amount; i++)
	{
		PlayerState->SR_AddWagonCard(WagonCards.Last());
		WagonCards.RemoveAt(WagonCards.Num() - 1);
	}
	OnRep_WagonCardsUpdate();
}

/* PLAYER READY */
void ATrainGameState::SR_PlayerReadyToNextState_Implementation(ATrainGamePlayerState* PlayerState = nullptr)
{
	if (!PlayerState) {
		if (CurrentGameState == EGameState::NEXT_PLAYER) {
			SR_SetGameState(EGameState::GAME);
		}
		else {
			SR_SetGameState(EGameState((int)CurrentGameState + 1));
		}
		return;
	}

	if (ReadyQueue.Contains(PlayerState)) {
		ReadyPlayerCount++;
		if (ReadyPlayerCount == ReadyQueue.Num())
		{
			ReadyPlayerCount = 0;
			if (CurrentGameState == EGameState::NEXT_PLAYER) {
				SR_SetGameState(EGameState::GAME);
			}
			else {
				SR_SetGameState(EGameState((int)CurrentGameState + 1));
			}
		}
	}
}

void ATrainGameState::SR_PlayerReadyToStart_Implementation(ATrainGamePlayerState* PlayerState)
{
	if (PlayerArray.Contains(PlayerState)) {
		ReadyPlayerCount++;
		if (ReadyPlayerCount == PlayerArray.Num())
		{
			ReadyPlayerCount = 0;
			SR_SetGameState(EGameState::DRAW_ROUTE_CARDS);
		}
	}
}

/* CREATE CARDS */
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

/* SHOP WAGON CARDS */
void ATrainGameState::SR_FillShopWagonCards_Implementation()
{
	while(ShopWagonCards.Num() != 5) {
		ShopWagonCards.Emplace(WagonCards.Last());
		MC_FillShopWagonCards(WagonCards.Last());
		WagonCards.RemoveAt(WagonCards.Num() - 1);
	}
}

void ATrainGameState::MC_FillShopWagonCards_Implementation(FWagonCard InputCard)
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetWorld()->GetFirstPlayerController());

	if (Controller)
	{
		Controller->BP_TriggerShopWidget_AddWagonCard(InputCard.Color);
	}
}

/* OnRep functions */
void ATrainGameState::OnRep_WagonCardsUpdate()
{
}

void ATrainGameState::OnRep_DiscardWagonCardsUpdate()
{
}

void ATrainGameState::OnRep_CurrentGameStateUpdate()
{
	ATrainGamePlayerController* Controller = Cast<ATrainGamePlayerController>(GetWorld()->GetFirstPlayerController());
	
	if (Controller)
	{
		Controller->CheckCurrentGameState(CurrentPlayer);
	}
}

void ATrainGameState::OnRep_ShopWagonCardsUpdate()
{

}