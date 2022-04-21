#include "CFileActor.h"
#include "Global.h"

ACFileActor::ACFileActor()
{
	CHelpers::CreateActorComponent<UInputComponent>(this, &InputComponent, "InputComponent");
}

void ACFileActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	CheckNull(controller);
	EnableInput(controller);
	
	//TODO
}


