#include "CTriggerDoor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/CPlayer.h"

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

	OnTriggerDoorOpen.AddUFunction(this, "Open");
	OnTriggerDoorClose.AddUFunction(this, "Close");
}

void ACTriggerDoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);
	CheckNull(OtherComp);
	CheckTrue(OtherActor == this);
	CheckFalse(OtherActor->GetClass()->IsChildOf(ACPlayer::StaticClass()));

	if (OnTriggerDoorOpen.IsBound())
		OnTriggerDoorOpen.Broadcast(Cast<ACPlayer>(OtherActor));
}

void ACTriggerDoor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckNull(OtherActor);
	CheckNull(OtherComp);
	CheckTrue(OtherActor == this);
	CheckFalse(OtherActor->GetClass()->IsChildOf(ACPlayer::StaticClass()));

	if (OnTriggerDoorClose.IsBound())
		OnTriggerDoorClose.Broadcast();
}

void ACTriggerDoor::Open(ACPlayer* InPlayer)
{
	FVector doorForward = GetActorForwardVector();
	FVector playerForward = InPlayer->GetActorForwardVector();

	float direction = FMath::Sign(doorForward | playerForward);
	Rotation = direction * MaxDegree;

	bOpen = true;
}

void ACTriggerDoor::Close()
{
	bOpen = false;
}

void ACTriggerDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = Door->GetRelativeRotation();

	if (bOpen)
		Door->SetRelativeRotation(FMath::Lerp(rotation, FRotator(0, Rotation, 0), Speed));
	else
		Door->SetRelativeRotation(FMath::Lerp(rotation, FRotator(0, 0, 0), Speed));

}

