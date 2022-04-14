#include "Example.h"
#include "GameplayDebugger.h"
#include "DebuggerCategory/CGameplayDebuggerCategory.h"

#define LOCTEXT_NAMESPACE "FExampleModule"

void FExampleModule::StartupModule()
{
	UE_LOG(LogTemp, Error, L"Module Started");

	//GameplayDebuggerCategory
	{
		IGameplayDebugger& gamplayDebugger = IGameplayDebugger::Get();
		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&CGameplayDebuggerCategory::MakeInstance);
		gamplayDebugger.RegisterCategory("ExampleCategory", category, EGameplayDebuggerCategoryState::EnabledInGame, 5);
	}
}

void FExampleModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"Module Shutdown");

	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger& gamplayDebugger = IGameplayDebugger::Get();
		gamplayDebugger.UnregisterCategory("ExampleCategory");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExampleModule, Example)