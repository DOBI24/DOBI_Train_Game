// @Copyright Marton Pal SZTE


#include "LobbyGameMode.h"
#include "LobbyPlayerState.h"

ALobbyGameMode::ALobbyGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Lobby/PC_LobbyPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ALobbyPlayerState> PlayerStateBPClass(TEXT("/Game/Lobby/PS_LobbyPlayerState"));
	if (PlayerStateBPClass.Class != nullptr)
	{
		PlayerStateClass = PlayerStateBPClass.Class;
	}
}
