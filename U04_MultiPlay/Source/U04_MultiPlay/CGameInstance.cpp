#include "CGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Menu/CMainMenu.h"

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> menuBPClass(TEXT("/Game/Menu/WB_MainMenu"));
	if (menuBPClass.Succeeded())
		MenuClass = menuBPClass.Class;

}

void UCGameInstance::Init()
{
	
}

void UCGameInstance::LoadMenu()
{
	if (MenuClass == nullptr) return;

	UCMainMenu* menu = CreateWidget<UCMainMenu>(this, MenuClass);
	if (menu == nullptr) return;
	
	menu->AddToViewport();

	menu->bIsFocusable = true;

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(menu->TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	APlayerController* playerController = GetFirstLocalPlayerController();
	playerController->SetInputMode(inputMode);
	playerController->bShowMouseCursor = true;

	menu->SetMenuInterface(this);
}

void UCGameInstance::Host()
{
	UEngine* engine = GetEngine();
	if (engine == nullptr) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Host"));

	UWorld* world = GetWorld();
	if (world == nullptr) return;
	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UCGameInstance::Join(const FString& InAddress)
{
	UEngine* engine = GetEngine();
	if (engine == nullptr) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join to %s"), *InAddress));

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (playerController == nullptr) return;
	playerController->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}