#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float Throttle;

	UPROPERTY()
		float SteeringThrow;

	UPROPERTY()
		float DeltaTime;

	UPROPERTY()
		float Time;
};

USTRUCT()
struct FGoKartState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		FTransform Transform;

	UPROPERTY()
		FVector Velocity;

	UPROPERTY()
		FGoKartMove LastMove;
};

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
		void Server_SendMove(FGoKartMove Move);

	void SimulateMove(const FGoKartMove& Move);
	FGoKartMove CreateMove(float DeltaTime);
	void ClearAcknowledgeMoves(FGoKartMove LastMove);
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector GetAirResistance();
	FVector GetRollingResistance();
	void UpdateLocationFromVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime, float Steering);

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
	UPROPERTY(ReplicatedUsing = "OnRep_ServerState")
		FGoKartState ServerState;

	FVector Velocity;

	UFUNCTION()
		void OnRep_ServerState();

	float Throttle;
	float SteeringThrow;

	TArray<FGoKartMove> UnacknowledgedMoves;
};
