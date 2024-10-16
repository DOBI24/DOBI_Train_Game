// @Copyright Marton Pal SZTE


#include "LobbyPlayerState.h"

ALobbyPlayerState::ALobbyPlayerState()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ALobbyPlayerState::SetPN(FString Name)
{
	SetPlayerName(Name);
}
