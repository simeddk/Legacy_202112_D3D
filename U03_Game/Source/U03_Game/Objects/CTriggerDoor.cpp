#include "CTriggerDoor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACTriggerDoor::ACTriggerDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Scene, "Scene");
	CHelpers::CreateComponent(this, &Box, "Box", Scene);
	CHelpers::CreateComponent(this, &DoorFrame, "DoorFrame", Scene);
	CHelpers::CreateComponent(this, &Door, "Door", DoorFrame);

	UStaticMesh* doorFrameMesh;
	CHelpers::GetAsset<UStaticMesh>(&doorFrameMesh, "StaticMesh'/Game/DoorMesh/Props/SM_DoorFrame.SM_DoorFrame'");
	DoorFrame->SetStaticMesh(doorFrameMesh);

	UStaticMesh* doorMesh;
	CHelpers::GetAsset<UStaticMesh>(&doorMesh, "StaticMesh'/Game/DoorMesh/Props/SM_Door.SM_Door'");
	Door->SetStaticMesh(doorMesh);

	Box->InitBoxExtent(FVector(150, 50, 100));
	Box->SetRelativeLocation(FVector(0, 0, 100));
	Box->SetCollisionProfileName("Trigger");

	Door->SetRelativeLocation(FVector(0, 45, 0));
}

void ACTriggerDoor::BeginPlay()
{
	Super::BeginPlay();

	Box->SetHiddenInGame(bHiddenInGame);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACTriggerDoor::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACTriggerDoor::OnEndOverlap);
}

void ACTriggerDoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ACTriggerDoor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ACTriggerDoor::Open(ACPlayer* InPlayer)
{
	//Todo30
}

void ACTriggerDoor::Close()
{
}

void ACTriggerDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

