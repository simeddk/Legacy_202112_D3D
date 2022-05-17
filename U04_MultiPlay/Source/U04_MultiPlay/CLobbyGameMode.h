#pragma once

#include "CoreMinimal.h"
#include "U04_MultiPlayGameMode.h"
#include "CLobbyGameMode.generated.h"

UCLASS()
class U04_MULTIPLAY_API ACLobbyGameMode : public AU04_MultiPlayGameMode
{
	GENERATED_BODY()
	
public:
	void PostLogin(APlayerController* NewPlayer) override;
	void Logout(AController* Exiting) override;

private:
	uint32 NumberOfPlayers = 0;
	
};
