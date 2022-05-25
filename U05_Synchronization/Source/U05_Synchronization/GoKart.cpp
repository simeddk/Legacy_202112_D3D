#include "GoKart.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"

AGoKart::AGoKart()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
		NetUpdateFrequency = 1;
}

void AGoKart::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGoKart, ReplicatedTransform);
	DOREPLIFETIME(AGoKart, Velocity);
	DOREPLIFETIME(AGoKart, Throttle);
	DOREPLIFETIME(AGoKart, SteeringThrow);
}

FString GetEnumText(ENetRole Role)
{
	switch (Role)
	{
		case ROLE_None:					return "None";
		case ROLE_SimulatedProxy:		return "Simulated";
		case ROLE_AutonomousProxy:		return "Autonomous";
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

	if (HasAuthority())
	{
		ReplicatedTransform = GetActorTransform();
	}

	DrawDebugString(GetWorld(), FVector(0, 0, 140), "Local : " + GetEnumText(GetLocalRole()), this, FColor::Black, DeltaTime, false, 1.2f);
	DrawDebugString(GetWorld(), FVector(0, 0, 100), "Remote : " + GetEnumText(GetRemoteRole()), this, FColor::Blue, DeltaTime);
}

void AGoKart::OnRep_ReplicatedTransform()
{
	SetActorTransform(ReplicatedTransform);
}

void AGoKart::ApplyRotation(float DeltaTime)
{
	float deltaLocation = (GetActorForwardVector() | Velocity) * DeltaTime;

	float rotationAngle = deltaLocation  / MinTurningRadius * SteeringThrow;
	FQuat rotationDelta(GetActorUpVector(), rotationAngle);

	Velocity = rotationDelta.RotateVector(Velocity);

	AddActorWorldRotation(rotationDelta);
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

void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);
}


void AGoKart::MoveForward(float Value)
{
	Throttle = Value;
	Server_MoveForward(Value);
}

void AGoKart::MoveRight(float Value)
{
	SteeringThrow = Value;
	Server_MoveRight(Value);
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
