#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKartMovementComponent.h"
#include "GoKartReplicateComponent.h"
#include "GoKart.generated.h"

UCLASS()
class U05_SYNCHRONIZATION_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	AGoKart();

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		UGoKartMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		UGoKartReplicateComponent* ReplicateComponent;
};
