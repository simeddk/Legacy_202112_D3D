#include "GoKart.h"

AGoKart::AGoKart()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector force = GetActorForwardVector() * MaxDrivingForce * Throttle;
	force += GetAirResistance();
	force += GetRollingResistance();

	FVector acceleration = force / Mass;
	Velocity = Velocity + acceleration* DeltaTime;

	ApplyRotation(DeltaTime);
	UpdateLocationFromVelocity(DeltaTime);

}

void AGoKart::ApplyRotation(float DeltaTime)
{
	float deltaLocation = (GetActorForwardVector() | Velocity) * DeltaTime;

	float rotationAngle = deltaLocation  / MinTurningRadius * SteeringThrow;
	FQuat rotationDelta(GetActorUpVector(), rotationAngle);

	Velocity = rotationDelta.RotateVector(Velocity);

	AddActorWorldRotation(rotationDelta);
}

FVector AGoKart::GetAirResistance()
{
	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

FVector AGoKart::GetRollingResistance()
{
	float acceleartionDueToGravity = -GetWorld()->GetGravityZ() / 100;
	float normalForce = acceleartionDueToGravity * Mass;
	return -Velocity.GetSafeNormal() * RollingCoefficient * normalForce;
}

void AGoKart::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector translation = Velocity * 100 * DeltaTime;

	FHitResult hit;
	AddActorWorldOffset(translation, true, &hit);
	if (hit.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}

void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);
	
}

void AGoKart::MoveForward(float Value)
{
	Throttle = Value;
}

void AGoKart::MoveRight(float Value)
{
	SteeringThrow = Value;
}
