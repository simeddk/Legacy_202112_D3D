#include "CMovingPlatform.h"

ACMovingPlatform::ACMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	if (mesh.Succeeded())
		GetStaticMeshComponent()->SetStaticMesh(mesh.Object);

	ConstructorHelpers::FObjectFinder<UMaterial> material(TEXT("/Game/Materials/MAT_Platform"));
	if (material.Succeeded())
		GetStaticMeshComponent()->SetMaterial(0, material.Object);
}

void ACMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

}

void ACMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector location = GetActorLocation();

		float totalDistance = (GlobalTargetLocation - GlobalStartLocation).Size();
		float currentDistance = (location - GlobalStartLocation).Size();

		if (currentDistance >= totalDistance)
		{
			FVector temp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = temp;
		}
		
		FVector direction = (GlobalTargetLocation - location).GetSafeNormal();

		location += Speed * direction * DeltaTime;
		SetActorLocation(location);
	}
}