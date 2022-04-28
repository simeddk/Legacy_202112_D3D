#include "CPlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "CMovingPlatform.h"

ACPlatformTrigger::ACPlatformTrigger()
{
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	if (Box == nullptr) return;

	RootComponent = Box;
}

void ACPlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACPlatformTrigger::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACPlatformTrigger::OnEndOveralp);
	
}

void ACPlatformTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (ACMovingPlatform* platform : PlatformToTrigger)
		platform->AddActiveTrigger();
}

void ACPlatformTrigger::OnEndOveralp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (ACMovingPlatform* platform : PlatformToTrigger)
		platform->RemoveActiveTrigger();
}
