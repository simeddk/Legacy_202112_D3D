#include "CpatrolPath.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"

ACpatrolPath::ACpatrolPath()
{
	CHelpers::CreateComponent(this, &Scene, "Scene");
	CHelpers::CreateComponent(this, &Spline, "Spline", Scene);
	CHelpers::CreateComponent(this, &Text, "Text", Scene);

	Spline->SetRelativeLocation(FVector(0, 0, 30));

	Text->SetRelativeLocation(FVector(0, 0, 120));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->TextRenderColor = FColor::Black;
}

void ACpatrolPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Text->SetText(FText::FromString(GetActorLabel()));

	Spline->SetClosedLoop(bLoop);
}

void ACpatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
	Text->SetVisibility(false);
}

