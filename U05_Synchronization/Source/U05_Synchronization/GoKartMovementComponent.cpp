#include "GoKartMovementComponent.h"
#include "GameFramework/GameState.h"

UGoKartMovementComponent::UGoKartMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UGoKartMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UGoKartMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGoKartMovementComponent::SimulateMove(const FGoKartMove& Move)
{
	FVector force = GetOwner()->GetActorForwardVector() * MaxDrivingForce * Move.Throttle;
	force += GetAirResistance();
	force += GetRollingResistance();

	FVector acceleration = force / Mass;
	Velocity = Velocity + acceleration * Move.DeltaTime;

	ApplyRotation(Move.DeltaTime, Move.SteeringThrow);
	UpdateLocationFromVelocity(Move.DeltaTime);
}

FGoKartMove UGoKartMovementComponent::CreateMove(float DeltaTime)
{
	FGoKartMove move;
	move.DeltaTime = DeltaTime;
	move.SteeringThrow = SteeringThrow;
	move.Throttle = Throttle;
	move.Time = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();

	return move;
}

FVector UGoKartMovementComponent::GetAirResistance()
{
	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

FVector UGoKartMovementComponent::GetRollingResistance()
{
	float acceleartionDueToGravity = -GetWorld()->GetGravityZ() / 100;
	float normalForce = acceleartionDueToGravity * Mass;
	return -Velocity.GetSafeNormal() * RollingCoefficient * normalForce;
}

void UGoKartMovementComponent::ApplyRotation(float DeltaTime, float Steering)
{
	float deltaLocation = (GetOwner()->GetActorForwardVector() | Velocity) * DeltaTime;

	float rotationAngle = deltaLocation / MinTurningRadius * Steering;
	FQuat rotationDelta(GetOwner()->GetActorUpVector(), rotationAngle);

	Velocity = rotationDelta.RotateVector(Velocity);

	GetOwner()->AddActorWorldRotation(rotationDelta);
}

void UGoKartMovementComponent::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector translation = Velocity * 100 * DeltaTime;

	FHitResult hit;

	GetOwner()->AddActorWorldOffset(translation, true, &hit);

	if (hit.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}


