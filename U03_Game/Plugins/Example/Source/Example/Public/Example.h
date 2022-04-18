#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyle.h"

class FExampleModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void AddToolbarExtension(class FToolBarBuilder& InBuilder);
	void ToolbarButton_Clicked();

private:
	TSharedPtr<FExtender> ToolbarExtender;
	TSharedPtr<const FExtensionBase> Extension;
	TSharedPtr<FSlateStyleSet> StyleSet;
};
