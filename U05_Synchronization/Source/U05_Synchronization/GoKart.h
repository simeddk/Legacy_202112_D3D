#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

	UFUNCTION(Reliable, Server, WithValidation)
		void Server_MoveForward(float Value);
	
	UFUNCTION(Reliable, Server, WithValidation)
		void Server_MoveRight(float Value);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector GetAirResistance();
	FVector GetRollingResistance();
	void UpdateLocationFromVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime);

private:
	UPROPERTY(EditAnywhere)
		float Mass = 1000;

	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;

	UPROPERTY(EditAnywhere)
		float MinTurningRadius = 10;

	UPROPERTY(EditAnywhere)
		float MaxDegreePerSecond = 90;

	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16;
	
	UPROPERTY(EditAnywhere)
		float RollingCoefficient = 0.015f;

private:
	UPROPERTY(Replicated)
		FVector Velocity;

	UPROPERTY(ReplicatedUsing = "OnRep_ReplicatedTransform")
		FTransform ReplicatedTransform;
	
	UFUNCTION()
		void OnRep_ReplicatedTransform();

	UPROPERTY(Replicated)
		float Throttle;

	UPROPERTY(Replicated)
		float SteeringThrow;
};
