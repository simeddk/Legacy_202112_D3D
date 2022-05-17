#include "CLobbyGameMode.h"

void ACLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NumberOfPlayers++;

	if (NumberOfPlayers >= 3)
	{
		UE_LOG(LogTemp, Error, TEXT("Reached 3 Players!!"));

		//TODO
	}
}

void ACLobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	NumberOfPlayers--;
}