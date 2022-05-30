#include "GoKart.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameState.h"

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
	DOREPLIFETIME(AGoKart, ServerState);
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

	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		FGoKartMove move = CreateMove(DeltaTime);

		SimulateMove(move);
		UnacknowledgedMoves.Add(move);

		Server_SendMove(move);
	}

	if (GetRemoteRole() == ROLE_SimulatedProxy)
	{
		FGoKartMove move = CreateMove(DeltaTime);
		SimulateMove(move);
		Server_SendMove(move);
	}

	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		SimulateMove(ServerState.LastMove);
	}

	DrawDebugString(GetWorld(), FVector(0, 0, 140), "Local : " + GetEnumText(GetLocalRole()), this, FColor::Black, DeltaTime, false, 1.2f);
	DrawDebugString(GetWorld(), FVector(0, 0, 100), "Remote : " + GetEnumText(GetRemoteRole()), this, FColor::Blue, DeltaTime);
}

void AGoKart::OnRep_ServerState()
{
	SetActorTransform(ServerState.Transform);
	Velocity = ServerState.Velocity;

	ClearAcknowledgeMoves(ServerState.LastMove);

	for (const FGoKartMove& move : UnacknowledgedMoves)
	{
		SimulateMove(move);
	}
}

void AGoKart::SimulateMove(const FGoKartMove& Move)
{
	FVector force = GetActorForwardVector() * MaxDrivingForce * Move.Throttle;
	force += GetAirResistance();
	force += GetRollingResistance();

	FVector acceleration = force / Mass;
	Velocity = Velocity + acceleration * Move.DeltaTime;

	ApplyRotation(Move.DeltaTime, Move.SteeringThrow);
	UpdateLocationFromVelocity(Move.DeltaTime);
}

FGoKartMove AGoKart::CreateMove(float DeltaTime)
{
	FGoKartMove move;
	move.DeltaTime = DeltaTime;
	move.SteeringThrow = SteeringThrow;
	move.Throttle = Throttle;
	move.Time = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();

	return move;
}

void AGoKart::ClearAcknowledgeMoves(FGoKartMove LastMove)
{
	TArray<FGoKartMove> nakMoves;

	for (const FGoKartMove& move : UnacknowledgedMoves)
	{
		if (move.Time > LastMove.Time)
		{
			nakMoves.Add(move);
		}
	}

	UnacknowledgedMoves = nakMoves;
}

void AGoKart::ApplyRotation(float DeltaTime, float Steering)
{
	float deltaLocation = (GetActorForwardVector() | Velocity) * DeltaTime;

	float rotationAngle = deltaLocation  / MinTurningRadius * Steering;
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
}

void AGoKart::MoveRight(float Value)
{
	SteeringThrow = Value;
}

void AGoKart::Server_SendMove_Implementation(FGoKartMove Move)
{
	SimulateMove(Move);
	ServerState.LastMove = Move;
	ServerState.Transform = GetActorTransform();
	ServerState.Velocity = Velocity;
}

bool AGoKart::Server_SendMove_Validate(FGoKartMove Move)
{
	return true;
}