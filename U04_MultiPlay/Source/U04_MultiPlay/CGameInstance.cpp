#include "CGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Menu/CMainMenu.h"
#include "Menu/CMenuWidget.h"

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> menuBPClass(TEXT("/Game/Menu/WB_MainMenu"));
	if (menuBPClass.Succeeded())
		MenuClass = menuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> inGameMenuBPClass(TEXT("/Game/Menu/WB_InGameMenu"));
	if (inGameMenuBPClass.Succeeded())
		InGameMenuClass = inGameMenuBPClass.Class;
}

void UCGameInstance::Init()
{
	
}

void UCGameInstance::LoadMenu()
{
	if (MenuClass == nullptr) return;

	Menu = CreateWidget<UCMainMenu>(this, MenuClass);
	if (Menu == nullptr) return;
	
	Menu->SetMenuInterface(this);
	Menu->SetUp();
}

void UCGameInstance::Host()
{
	if (!!Menu)
		Menu->TearDown();

	UEngine* engine = GetEngine();
	if (engine == nullptr) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Host"));

	UWorld* world = GetWorld();
	if (world == nullptr) return;
	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UCGameInstance::Join(const FString& InAddress)
{
	if (!!Menu)
		Menu->TearDown();

	UEngine* engine = GetEngine();
	if (engine == nullptr) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join to %s"), *InAddress));

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (playerController == nullptr) return;
	playerController->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::InGameLoadMenu()
{
	if (InGameMenuClass == nullptr) return;

	UCMenuWidget* inGameMenu = CreateWidget<UCMenuWidget>(this, InGameMenuClass);
	if (inGameMenu == nullptr) return;

	inGameMenu->SetMenuInterface(this);
	inGameMenu->SetUp();
}

void UCGameInstance::LoadMainMenu()
{
	APlayerController* playerController = GetFirstLocalPlayerController();
	if (playerController == nullptr) return;
	playerController->ClientTravel("/Game/ThirdPersonCPP/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}