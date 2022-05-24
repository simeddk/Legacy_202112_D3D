#include "GoKart.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AGoKart::AGoKart()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
}

FString GetEnumText(ENetRole Role)
{
	switch (Role)
	{
		case ROLE_None:					return "None";
		case ROLE_SimulatedProxy:		return "SimulatedProxy";
		case ROLE_AutonomousProxy:		return "AutonomousProxy";
		case ROLE_Authority:			return "Authority";
		default:						return "Error";
	}

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

	DrawDebugString(GetWorld(), FVector(0, 0, 100), GetEnumText(GetLocalRole()), this, FColor::Green, DeltaTime);
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

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::Server_MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::Server_MoveRight);
	
}

void AGoKart::Server_MoveForward_Implementation(float Value)
{
	Throttle = Value;
}

bool AGoKart::Server_MoveForward_Validate(float Value)
{
	return FMath::Abs(Value) <= 1;
}

void AGoKart::Server_MoveRight_Implementation(float Value)
{
	SteeringThrow = Value;
}

bool AGoKart::Server_MoveRight_Validate(float Value)
{
	return FMath::Abs(Value) <= 1;
}
