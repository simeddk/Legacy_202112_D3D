#include "CAim.h"
#include "Global.h"
#include "CHUD.h"
#include "Components/CStateComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

UCAim::UCAim()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Curves/Curve_Aim.Curve_Aim'");
}

void UCAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	TimelineFloat.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, TimelineFloat);
	Timeline.SetPlayRate(200);

	//Hud = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<ACHUD>();
	Hud = OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD<ACHUD>();
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCAim::On()
{
	CheckFalse(IsAvaliable());
	CheckTrue(bInZoom);

	bInZoom = true;

	Hud->OnDraw();

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	SpringArm->bEnableCameraLag = false;

	Timeline.PlayFromStart();
}

void UCAim::Off()
{
	CheckFalse(IsAvaliable());
	CheckFalse(bInZoom);

	bInZoom = false;

	Hud->OffDraw();

	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true;

	Timeline.ReverseFromEnd();
}

void UCAim::Zooming(float Output)
{
	Camera->FieldOfView = Output;
}
