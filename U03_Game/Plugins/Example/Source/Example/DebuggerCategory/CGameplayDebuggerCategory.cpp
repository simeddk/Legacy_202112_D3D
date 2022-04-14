#include "CGameplayDebuggerCategory.h"
//#include "GameplayDebuggerTypes.h"

CGameplayDebuggerCategory::CGameplayDebuggerCategory()
{
	UE_LOG(LogTemp, Error, L"CGameplayDebuggerCategory Started");
}

CGameplayDebuggerCategory::~CGameplayDebuggerCategory()
{
	UE_LOG(LogTemp, Error, L"CGameplayDebuggerCategory Ended");
}

TSharedRef<FGameplayDebuggerCategory> CGameplayDebuggerCategory::MakeInstance()
{
	return MakeShareable(new CGameplayDebuggerCategory());
}

void CGameplayDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	Data.Actor = DebugActor;

	if (!!Data.Actor)
	{
		Data.Location = Data.Actor->GetActorLocation();
		Data.Distance = OwnerPC->GetPawn()->GetDistanceTo(Data.Actor);
	}

}

void CGameplayDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	if (!!Data.Actor)
	{
		CanvasContext.Printf(FColor::Red, L"Name : %s", *Data.Actor->GetName());
		CanvasContext.Printf(FColor::Green, L"Location : %s", *Data.Location.ToString());
		CanvasContext.Printf(FColor::Blue, L"Distance : %f", Data.Distance);
	}
}
