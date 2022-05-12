#include "CGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Menu/CMainMenu.h"
#include "Menu/CMenuWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = TEXT("GameSession");

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
	IOnlineSubsystem* subSystem = IOnlineSubsystem::Get();
	if (!!subSystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("SubSystem Found : %s"), *subSystem->GetSubsystemName().ToString());

		SessionInterface = subSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCGameInstance::OnFindSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Found SubSystem"));
	}
}

void UCGameInstance::LoadMenuWidget()
{
	if (MenuClass == nullptr) return;

	Menu = CreateWidget<UCMainMenu>(this, MenuClass);
	if (Menu == nullptr) return;
	
	Menu->SetMenuInterface(this);
	Menu->SetUp();
}

void UCGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto exsistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (!!exsistingSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
		
	}
}

void UCGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings sessionSettings;
		sessionSettings.bIsLANMatch = true;
		sessionSettings.NumPublicConnections = 2;
		sessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, SESSION_NAME, sessionSettings);
	}
}

void UCGameInstance::OnCreateSessionComplete(FName InSessionName, bool InSuccess)
{
	if (InSuccess == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could Not Create Session!!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Session Name : %s"), *InSessionName.ToString());

	if (!!Menu)
		Menu->TearDown();

	UEngine* engine = GetEngine();
	if (engine == nullptr) return;
	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Host"));

	UWorld* world = GetWorld();
	if (world == nullptr) return;
	world->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UCGameInstance::OnDestroySessionComplete(FName InSessionName, bool InSuccess)
{
	if (InSuccess == true)
		CreateSession();
}

void UCGameInstance::Join(const FString& InAddress)
{
	/*if (!!Menu)
		Menu->TearDown();

	UEngine* engine = GetEngine();
	if (engine == nullptr) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Join to %s"), *InAddress));

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (playerController == nullptr) return;
	playerController->ClientTravel(InAddress, ETravelType::TRAVEL_Absolute);*/

	if (!!Menu)
		Menu->SetServerList({ "Session1", "Session2" });
}

void UCGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Sessions"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
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

void UCGameInstance::OnFindSessionComplete(bool InSucess)
{
	if (InSucess == true && SessionSearch.IsValid() && Menu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished Find Session"));

		TArray<FString> serverNames;
		for (const FOnlineSessionSearchResult& searchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Error, TEXT("Found Session Name : %s"), *searchResult.GetSessionIdStr());
			UE_LOG(LogTemp, Error, TEXT("Ping : %d"), searchResult.PingInMs);

			serverNames.Add(searchResult.GetSessionIdStr());
		}

		Menu->SetServerList(serverNames);
	}
}