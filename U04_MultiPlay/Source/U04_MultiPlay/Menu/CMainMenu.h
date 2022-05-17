#pragma once

#include "CoreMinimal.h"
#include "IMenuInterface.h"
#include "CMenuWidget.h"
#include "CMainMenu.generated.h"

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUserName;
};

UCLASS()
class U04_MULTIPLAY_API UCMainMenu : public UCMenuWidget
{
	GENERATED_BODY()

public:
	UCMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData> InServerName);
	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void JoinServer();

	UFUNCTION()
		void OpenMainMenu();

	UFUNCTION()
		void OpenHostMenu();
	
	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void QuitPressed();
	
private:
	TSubclassOf<class UCServerRow> ServerRowClass;

private:
	void UpdateChildren();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* CancelJoinMenuButton;
	
	UPROPERTY(meta = (BindWidget))
		class UButton* ConfirmJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ServerHostName;

	UPROPERTY(meta = (BindWidget))
		class UButton* CancelHostMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ConfirmHostMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* ServerList;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

private:
	TOptional<uint32> SelectedIndex;
};
