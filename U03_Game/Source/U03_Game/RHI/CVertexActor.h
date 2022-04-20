#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertexActor.generated.h"

UCLASS()
class U03_GAME_API ACVertexActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* Mesh;
	
public:	
	ACVertexActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void AddFace(uint32 InStart);

private:
	TArray<FVector> Vertices;
	TArray<uint32> Indices;

};
