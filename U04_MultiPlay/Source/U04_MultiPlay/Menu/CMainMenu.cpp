#include "CMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "CServerRow.h"

UCMainMenu::UCMainMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> serverRowClass(TEXT("/Game/Menu/WB_ServerRow"));
	if (serverRowClass.Succeeded())
		ServerRowClass = serverRowClass.Class;
}

bool UCMainMenu::Initialize()
{
	bool success = Super::Initialize();
	if (success == false)
		return false;

	if (HostButton == nullptr) return false;
	HostButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenHostMenu);

	if (CancelHostMenuButton == nullptr) return false;
	CancelHostMenuButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenMainMenu);

	if (ConfirmHostMenuButton == nullptr) return false;
	ConfirmHostMenuButton->OnClicked.AddDynamic(this, &UCMainMenu::HostServer);

	if (JoinButton == nullptr) return false;
	JoinButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenJoinMenu);

	if (CancelJoinMenuButton == nullptr) return false;
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UCMainMenu::OpenMainMenu);

	if (ConfirmJoinMenuButton == nullptr) return false;
	ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UCMainMenu::JoinServer);

	if (QuitButton == nullptr) return false;
	QuitButton->OnClicked.AddDynamic(this, &UCMainMenu::QuitPressed);

	return true;
}

void UCMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UCMainMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); i++)
	{
		auto serverRow = Cast<UCServerRow>(ServerList->GetChildAt(i));
		if (!!serverRow)
			serverRow->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
	}
}

void UCMainMenu::HostServer()
{
	if (!!MenuInterface)
	{
		FString serverName = ServerHostName->Text.ToString();
		MenuInterface->Host(serverName);
	}
}

void UCMainMenu::JoinServer()
{
	if (SelectedIndex.IsSet() && MenuInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index : %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index is not set"));
	}
}

void UCMainMenu::SetServerList(TArray<FServerData> InServerName)
{
	UWorld* world = GetWorld();
	if (world == nullptr) return;

	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FServerData& serverData : InServerName)
	{
		UCServerRow* row = CreateWidget<UCServerRow>(world, ServerRowClass);
		if (row == nullptr) return;

		row->ServerName->SetText(FText::FromString(serverData.Name));
		row->HostUser->SetText(FText::FromString(serverData.HostUserName));
		FString fractionText = FString::Printf(TEXT("%d/%d"), serverData.CurrentPlayers, serverData.MaxPlayers);
		row->ConnectionFraction->SetText(FText::FromString(fractionText));
		row->SetUp(this, i++);

		ServerList->AddChild(row);
	}
}


void UCMainMenu::OpenMainMenu()
{
	if (MenuSwitcher == nullptr) return;
	if (MainMenu == nullptr) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UCMainMenu::OpenHostMenu()
{
	if (MenuSwitcher == nullptr) return;
	if (HostMenu == nullptr) return;
	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UCMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher == nullptr) return;
	if (JoinMenu == nullptr) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (!!MenuInterface)
		MenuInterface->RefreshServerList();
}


void UCMainMenu::QuitPressed()
{
	UWorld* world = GetWorld(); 
	if (world == nullptr) return;

	APlayerController* playerController = world->GetFirstPlayerController();
	if (playerController == nullptr) return;

	playerController->ConsoleCommand("quit");
}


