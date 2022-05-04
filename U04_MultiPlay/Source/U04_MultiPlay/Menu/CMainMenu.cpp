#include "CMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UCMainMenu::Initialize()
{
	bool success = Super::Initialize();
	if (success == false)
		return false;

	if (HostButton == nullptr) return false;
	HostButton->OnClicked.AddDynamic(this, &UCMainMenu::HostServer);

	if (JoinButton == nullptr) return false;
	JoinButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenJoinMenu);

	if (CancelJoinMenuButton == nullptr) return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenMainMenu);

	return true;
}

void UCMainMenu::SetMenuInterface(IIMenuInterface* InMenuInterface)
{
	MenuInterface = InMenuInterface;
}

void UCMainMenu::SetUp()
{
	AddToViewport();
	bIsFocusable = true;

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	UWorld* world = GetWorld();
	if (world == nullptr) return;

	APlayerController* playerController = world->GetFirstPlayerController();
	if (playerController == nullptr) return;
	
	playerController->SetInputMode(inputMode);
	playerController->bShowMouseCursor = true;
}

void UCMainMenu::TearDown()
{
	RemoveFromViewport();
	bIsFocusable = false;

	FInputModeGameOnly inputMode;

	UWorld* world = GetWorld();
	if (world == nullptr) return;

	APlayerController* playerController = world->GetFirstPlayerController();
	if (playerController == nullptr) return;

	playerController->SetInputMode(inputMode);
	playerController->bShowMouseCursor = false;
}

void UCMainMenu::HostServer()
{
	MenuInterface->Host();
}

void UCMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher == nullptr) return;
	if (JoinMenu == nullptr) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UCMainMenu::OpenMainMenu()
{
	if (MenuSwitcher == nullptr) return;
	if (MainMenu == nullptr) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}
