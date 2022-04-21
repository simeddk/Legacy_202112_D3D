#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFileActor.generated.h"

UCLASS()
class U03_GAME_API ACFileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFileActor();

protected:
	virtual void BeginPlay() override;


};
