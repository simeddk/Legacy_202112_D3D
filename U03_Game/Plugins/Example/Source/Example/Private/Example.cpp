#include "Example.h"
#include "GameplayDebugger.h"
#include "DebuggerCategory/CGameplayDebuggerCategory.h"
#include "ToolbarCommand/CToolbarCommand.h"
#include "LevelEditor.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FExampleModule"

void FExampleModule::StartupModule()
{
	/*
	TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);
	for (const FSlateBrush* bursh : brushes)
		GLog->Log(bursh->GetResourceName().ToString());
	*/

	UE_LOG(LogTemp, Error, L"Module Started");

	//GameplayDebuggerCategory
	{
		IGameplayDebugger& gamplayDebugger = IGameplayDebugger::Get();
		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&CGameplayDebuggerCategory::MakeInstance);
		gamplayDebugger.RegisterCategory("ExampleCategory", category, EGameplayDebuggerCategoryState::EnabledInGame, 5);
	}

	//ToolbarCommand
	{
		CToolbarCommand::Register();
		ToolbarExtender = MakeShareable(new FExtender());

		TSharedPtr<FUICommandList> commandList = MakeShareable(new FUICommandList());
		commandList->MapAction
		(
			CToolbarCommand::Get().Button,
			FExecuteAction::CreateRaw(this, &FExampleModule::ToolbarButton_Clicked),
			FCanExecuteAction()
		);

		Extension = ToolbarExtender->AddToolBarExtension
		(
			"Compile",
			EExtensionHook::After,
			commandList,
			FToolBarExtensionDelegate::CreateRaw(this, &FExampleModule::AddToolbarExtension)
		);

		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	//StyleSet
	{
		StyleSet = MakeShareable(new FSlateStyleSet("ExampleStyleSet"));
		
		FString path = IPluginManager::Get().FindPlugin("Example")->GetContentDir();
		StyleSet->SetContentRoot(path);

		FSlateImageBrush* brush = new FSlateImageBrush(path / L"Icon.png", FVector2D(48, 48));
		StyleSet->Set("Example.ToolbarIcon", brush);

		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
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

	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	ToolbarExtender.Reset();

	CToolbarCommand::Unregister();

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	StyleSet.Reset();
}

void FExampleModule::AddToolbarExtension(FToolBarBuilder& InBuilder)
{
	//FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode");
	FSlateIcon icon = FSlateIcon("ExampleStyleSet", "Example.ToolbarIcon");

	InBuilder.AddToolBarButton
	(
		CToolbarCommand::Get().Button,
		NAME_None,
		FText::FromString("YesJam"),
		FText::FromString("NoJam"),
		icon
	);
}

void FExampleModule::ToolbarButton_Clicked()
{
	UE_LOG(LogTemp, Warning, L"Hello Miku");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExampleModule, Example)