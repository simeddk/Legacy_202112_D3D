#include "GoKartReplicateComponent.h"
#include "Net/UnrealNetwork.h"

UGoKartReplicateComponent::UGoKartReplicateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicated(true);
}

void UGoKartReplicateComponent::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent = GetOwner()->FindComponentByClass<UGoKartMovementComponent>();
}

void UGoKartReplicateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MovementComponent == nullptr) return;

	FGoKartMove lastMove = MovementComponent->GetLastMove();

	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		UnacknowledgedMoves.Add(lastMove);
		Server_SendMove(lastMove);
	}

	if (GetOwner()->GetRemoteRole() == ROLE_SimulatedProxy)
	{
		UpdateServerState(lastMove);
	}

	if (GetOwnerRole() == ROLE_SimulatedProxy)
	{
		ClientTick(DeltaTime);
	}
}

void UGoKartReplicateComponent::ClientTick(float DeltaTime)
{
	ClientTimeSinceUpdate += DeltaTime;

	if (ClientTimeBetweenLastUpdate < KINDA_SMALL_NUMBER) return;
	if (MovementComponent == nullptr) return;

	float lerpRatio = ClientTimeSinceUpdate / ClientTimeBetweenLastUpdate;
	
	FHermiteCubeSpline spline = CreateSpline();
	InterpolateLocation(spline, lerpRatio);
	InterpolateVelocity(spline, lerpRatio);
	InterpolateRotation(lerpRatio);
}

FHermiteCubeSpline UGoKartReplicateComponent::CreateSpline()
{
	FHermiteCubeSpline spline;

	spline.StartLocation = ClientStartTransform.GetLocation();
	spline.TargetLocation = ServerState.Transform.GetLocation();

	spline.StartDerivative = ClientStartVelocity * VelocityToDerivative();
	spline.TargetDerivative = ServerState.Velocity * VelocityToDerivative();

	return spline;
}

void UGoKartReplicateComponent::InterpolateLocation(const FHermiteCubeSpline& Spline, float LerpRatio)
{
	FVector newLocation = Spline.InterpolateLocation(LerpRatio);
	GetOwner()->SetActorLocation(newLocation);
}

void UGoKartReplicateComponent::InterpolateVelocity(const FHermiteCubeSpline& Spline, float LerpRatio)
{
	FVector newDerivative = Spline.InterpolateDerivative(LerpRatio);
	FVector newVelocity = newDerivative / VelocityToDerivative();
	MovementComponent->SetVelocity(newVelocity);
}

void UGoKartReplicateComponent::InterpolateRotation(float LerpRatio)
{
	FQuat startRotation = ClientStartTransform.GetRotation();
	FQuat targetRotation = ServerState.Transform.GetRotation();
	FQuat newRotation = FQuat::Slerp(startRotation, targetRotation, LerpRatio);
	GetOwner()->SetActorRotation(newRotation);
}

float UGoKartReplicateComponent::VelocityToDerivative()
{
	return ClientTimeBetweenLastUpdate * 100;
}

void UGoKartReplicateComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UGoKartReplicateComponent, ServerState);
}

void UGoKartReplicateComponent::OnRep_ServerState()
{
	switch (GetOwnerRole())
	{
		case ROLE_AutonomousProxy:	AutonomousProxy_OnRep_ServerState(); break;
		case ROLE_SimulatedProxy:	Simulate_OnRep_ServerState();		 break;
	}
}

void UGoKartReplicateComponent::AutonomousProxy_OnRep_ServerState()
{
	if (MovementComponent == nullptr) return;

	GetOwner()->SetActorTransform(ServerState.Transform);
	MovementComponent->SetVelocity(ServerState.Velocity);

	ClearAcknowledgeMoves(ServerState.LastMove);

	for (const FGoKartMove& move : UnacknowledgedMoves)
	{
		MovementComponent->SimulateMove(move);
	}
}

void UGoKartReplicateComponent::Simulate_OnRep_ServerState()
{
	if (MovementComponent == nullptr) return;

	ClientTimeBetweenLastUpdate = ClientTimeSinceUpdate;
	ClientTimeSinceUpdate = 0;

	ClientStartTransform = GetOwner()->GetActorTransform();
	ClientStartVelocity = MovementComponent->GetVelocity();
}

void UGoKartReplicateComponent::ClearAcknowledgeMoves(FGoKartMove LastMove)
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

void UGoKartReplicateComponent::UpdateServerState(const FGoKartMove& Move)
{
	ServerState.LastMove = Move;
	ServerState.Transform = GetOwner()->GetActorTransform();
	ServerState.Velocity = MovementComponent->GetVelocity();
}

void UGoKartReplicateComponent::Server_SendMove_Implementation(FGoKartMove Move)
{
	if (MovementComponent == nullptr) return;

	MovementComponent->SimulateMove(Move);
	UpdateServerState(Move);
}

bool UGoKartReplicateComponent::Server_SendMove_Validate(FGoKartMove Move)
{
	return true;
}