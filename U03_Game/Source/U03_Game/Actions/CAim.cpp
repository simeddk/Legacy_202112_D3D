#include "CAim.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

UCAim::UCAim()
{

}

void UCAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
}

void UCAim::Tick(float DeltaTime)
{

}

void UCAim::On()
{
	CheckFalse(IsAvaliable());
	CheckTrue(bInZoom);

	bInZoom = true;

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	SpringArm->bEnableCameraLag = false;

	Camera->FieldOfView = 45.f;
}

void UCAim::Off()
{
	CheckFalse(IsAvaliable());
	CheckFalse(bInZoom);

	bInZoom = false;

	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true;

	Camera->FieldOfView = 90.f;
}