#include "CDoAction_Warp.h"
#include "Global.h"
#include "CAttachment.h"
#include "Characters/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CBehaviorComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "AIController.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Warp"))
		{
			Decal = CHelpers::GetComponent<UDecalComponent>(actor);
			break;
		}
	}

	
}

void ACDoAction_Warp::DoAction()
{
	Super::DoAction();

	CheckFalse(*bEquipped);
	CheckFalse(State->IsIdleMode());

	if (UseCursorLocation())
	{
		FRotator rotation;
		CheckFalse(GetCursorLocationAndRotation(Location, rotation));
	}
	else
	{
		AAIController* controller = OwnerCharacter->GetController<AAIController>();
		UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

		Location = behavior->GetWaprLocation();
		Decal->SetVisibility(false);
	}
	
	State->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Warp::Begin_DoAction()
{
	Super::Begin_DoAction();

	FTransform transform = Datas[0].EffectTransform;
	UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, OwnerCharacter->GetMesh(), "", transform.GetLocation(), FRotator(transform.GetRotation()), transform.GetScale3D());;
}

void ACDoAction_Warp::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->SetActorLocation(Location);
	Location = FVector::ZeroVector;

	State->SetIdelMode();
	Status->SetMove();
}

void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(*bEquipped);

	if (UseCursorLocation() == nullptr)
	{
		Decal->SetVisibility(false);
		return;
	}

	FVector location;
	FRotator rotation;
	if (GetCursorLocationAndRotation(location, rotation) == true)
	{
		Decal->SetVisibility(true);
		Decal->SetWorldLocation(location);
		Decal->SetWorldRotation(rotation);
	}
	else
		Decal->SetVisibility(false);
}

ACPlayer* ACDoAction_Warp::UseCursorLocation()
{
	return Cast<ACPlayer>(OwnerCharacter);
}

bool ACDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation)
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery1);

	FHitResult hitResult;
	if (controller->GetHitResultUnderCursorForObjects(objects, true, hitResult))
	{
		OutLocation = hitResult.ImpactPoint;
		OutRotation = hitResult.ImpactNormal.Rotation();

		return true;
	}

	return false;
}
