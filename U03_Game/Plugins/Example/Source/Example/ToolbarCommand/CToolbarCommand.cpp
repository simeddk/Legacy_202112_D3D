#include "CToolbarCommand.h"

CToolbarCommand::CToolbarCommand()
	: TCommands
	(
		"ExampleButton",
		FText::FromString("ExampleButton"),
		NAME_None,
		FEditorStyle::GetStyleSetName()
	)
{
}

CToolbarCommand::~CToolbarCommand()
{
}

void CToolbarCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE "CToolbarCommand"
	UI_COMMAND
	(
		Button,
		"FriendlyName",
		"My Toolbar Button",
		EUserInterfaceActionType::Button,
		FInputGesture()
	);
#undef LOCTEXT_NAMESPACE
}