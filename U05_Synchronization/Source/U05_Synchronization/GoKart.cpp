#include "GoKart.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AGoKart::AGoKart()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	MovementComponent = CreateDefaultSubobject<UGoKartMovementComponent>(TEXT("MovementComponent"));
	//ReplicateComponent = CreateDefaultSubobject<UGoKartReplicateComponent>(TEXT("ReplicateComponent"));
}

void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
		NetUpdateFrequency = 1;
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

	DrawDebugString(GetWorld(), FVector(0, 0, 140), "Local : " + GetEnumText(GetLocalRole()), this, FColor::Black, DeltaTime, false, 1.2f);
	DrawDebugString(GetWorld(), FVector(0, 0, 100), "Remote : " + GetEnumText(GetRemoteRole()), this, FColor::Blue, DeltaTime);
}

void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);
}

void AGoKart::MoveForward(float Value)
{
	if (MovementComponent == nullptr) return;

	MovementComponent->SetThrottle(Value);
}

void AGoKart::MoveRight(float Value)
{
	if (MovementComponent == nullptr) return;

	MovementComponent->SetSteeringThrow(Value);
}
