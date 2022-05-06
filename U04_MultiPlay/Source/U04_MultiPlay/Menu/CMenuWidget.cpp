#include "CMenuWidget.h"

void UCMenuWidget::SetMenuInterface(IIMenuInterface* InMenuInterface)
{
	MenuInterface = InMenuInterface;
}

void UCMenuWidget::SetUp()
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

void UCMenuWidget::TearDown()
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