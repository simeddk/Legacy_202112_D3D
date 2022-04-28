#include "CGameInstance.h"
#include "Engine/Engine.h"

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance::Constructor"));
}

void UCGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance::Init"));
}

void UCGameInstance::Host()
{
	UEngine* engine = GetEngine();
	if (engine == nullptr) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Host"));
}

void UCGameInstance::Join(const FString& InAddress)
{
	UEngine* engine = GetEngine();
	if (engine == nullptr) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join to %s"), *InAddress));
}