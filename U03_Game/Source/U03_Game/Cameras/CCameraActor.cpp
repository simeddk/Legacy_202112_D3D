#include "CCameraActor.h"
#include "Global.h"
#include "CCameraSpline.h"
#include "Components/SplineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

ACCameraActor::ACCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Camera, "Camera");
}



void ACCameraActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACCameraSpline::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);

	for (AActor* actor : actors)
	{
		if (actor->IsA<ACCameraSpline>() && actor->GetName().Contains("BP_CCameraSpline"))
			Spline = Cast<ACCameraSpline>(actor);
	}
}

void ACCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Timeline.IsPlaying())
		Timeline.TickTimeline(DeltaTime);
}

void ACCameraActor::StartTimeline()
{
	CheckTrue(Timeline.IsPlaying());

	FOnTimelineFloat progress;
	progress.BindUFunction(this, "OnProgress");

	FOnTimelineEvent finish;
	finish.BindUFunction(this, "OnFinishProgress");

	Timeline = FTimeline();
	Timeline.AddInterpFloat(Spline->GetCurve(), progress);
	Timeline.SetTimelineFinishedFunc(finish);
	Timeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	Timeline.SetPlayRate(0.25f);
	Timeline.PlayFromStart();

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	controller->SetViewTarget(this);
}

void ACCameraActor::OnProgress(float Output)
{
	USplineComponent* spline = Spline->GetSpline();
	float length = spline->GetSplineLength();

	FVector location = spline->GetLocationAtDistanceAlongSpline(Output * length, ESplineCoordinateSpace::World);
	FRotator rotation = spline->GetRotationAtDistanceAlongSpline(Output * length, ESplineCoordinateSpace::World);

	SetActorLocation(location);
	SetActorRotation(rotation);
}

void ACCameraActor::OnFinishProgress()
{
	Timeline.Stop();

	APlayerController* controller =	UGameplayStatics::GetPlayerController(GetWorld(), 0); 
	CheckNull(controller);

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	CheckNull(player);
	controller->SetViewTarget(Cast<AActor>(player));
}