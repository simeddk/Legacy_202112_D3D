#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"


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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U05_SYNCHRONIZATION_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGoKartMovementComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);
	FGoKartMove CreateMove(float DeltaTime);

public:
	FORCEINLINE FVector GetVelocity() { return Velocity; }
	FORCEINLINE void SetVelocity(FVector Val) { Velocity = Val; }

	FORCEINLINE void SetSteeringThrow(float Val) { SteeringThrow = Val; }
	FORCEINLINE void SetThrottle(float Val) { Throttle = Val; }

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
		float DragCoefficient = 16;

	UPROPERTY(EditAnywhere)
		float RollingCoefficient = 0.015f;

	
	FVector Velocity;

	float Throttle;
	float SteeringThrow;
};
