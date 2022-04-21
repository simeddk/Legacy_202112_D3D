#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertexPaintActor.generated.h"

UCLASS()
class U03_GAME_API ACVertexPaintActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	
public:	
	ACVertexPaintActor();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ChangeVertexColor();
};
