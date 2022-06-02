#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.h"
#include "GoKartReplicateComponent.generated.h"

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

struct FHermiteCubeSpline
{
	FVector StartLocation, StartDerivative, TargetLocation, TargetDerivative;

	FVector InterpolateLocation(float LerpRatio) const
	{
		return FMath::CubicInterp(StartLocation, StartDerivative, TargetLocation, TargetDerivative, LerpRatio);
	}

	FVector InterpolateDerivative(float LerpRatio) const
	{
		return FMath::CubicInterpDerivative(StartLocation, StartDerivative, TargetLocation, TargetDerivative, LerpRatio);
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class U05_SYNCHRONIZATION_API UGoKartReplicateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGoKartReplicateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void ClearAcknowledgeMoves(FGoKartMove LastMove);
	void UpdateServerState(const FGoKartMove& Move);
	
	void ClientTick(float DeltaTime);
	FHermiteCubeSpline CreateSpline();
	void InterpolateLocation(const FHermiteCubeSpline& Spline, float LerpRatio);
	void InterpolateVelocity(const FHermiteCubeSpline& Spline, float LerpRatio);
	void InterpolateRotation(float LerpRatio);
	float VelocityToDerivative();
		
	UFUNCTION(Reliable, Server, WithValidation)
		void Server_SendMove(FGoKartMove Move);

	UPROPERTY(ReplicatedUsing = "OnRep_ServerState")
		FGoKartState ServerState;

	UFUNCTION()
		void OnRep_ServerState();
	void AutonomousProxy_OnRep_ServerState();
	void Simulate_OnRep_ServerState();

	TArray<FGoKartMove> UnacknowledgedMoves;

	float ClientTimeSinceUpdate;
	float ClientTimeBetweenLastUpdate;
	FTransform ClientStartTransform;
	FVector ClientStartVelocity;

	UPROPERTY()
		UGoKartMovementComponent* MovementComponent;
};
