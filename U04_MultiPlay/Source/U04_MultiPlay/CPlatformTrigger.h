#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPlatformTrigger.generated.h"

UCLASS()
class U04_MULTIPLAY_API ACPlatformTrigger : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		TArray<class ACMovingPlatform*> PlatformToTrigger;
	
public:	
	ACPlatformTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOveralp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
