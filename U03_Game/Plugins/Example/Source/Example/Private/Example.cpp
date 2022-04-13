#include "Example.h"
#include "GameplayDebugger.h"

#define LOCTEXT_NAMESPACE "FExampleModule"

void FExampleModule::StartupModule()
{
	UE_LOG(LogTemp, Error, L"Module Started");
}

void FExampleModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"Module Shutdown");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExampleModule, Example)