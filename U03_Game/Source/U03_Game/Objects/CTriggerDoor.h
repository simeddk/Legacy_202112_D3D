#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTriggerDoor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FTriggerDoorOpen, class ACPlayer*);
DECLARE_MULTICAST_DELEGATE(FTriggerDoorClose);

UCLASS()
class U03_GAME_API ACTriggerDoor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Speed = 2.0f;

	UPROPERTY(EditAnywhere)
		float MaxDegree = 90.0f;

	UPROPERTY(EditAnywhere)
		bool bHiddenInGame;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Door;

public:
	FTriggerDoorOpen OnTriggerDoorOpen;
	FTriggerDoorClose OnTriggerDoorClose;
	
public:	
	ACTriggerDoor();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void Open(class ACPlayer* InPlayer);

	UFUNCTION()
		void Close();

public:	
	virtual void Tick(float DeltaTime) override;

private:
	bool bOpen = false;
	float Rotation;
};
