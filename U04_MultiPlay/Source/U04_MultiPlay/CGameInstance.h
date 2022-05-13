#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Menu/IMenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CGameInstance.generated.h"

UCLASS()
class U04_MULTIPLAY_API UCGameInstance : public UGameInstance, public IIMenuInterface
{
	GENERATED_BODY()
		
public:
	UCGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();

public:
	UFUNCTION(BlueprintCallable, Exec)
		void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
		void InGameLoadMenu();

	UFUNCTION(Exec)
		void Host() override;

	UFUNCTION(Exec)
		void Join(uint32 Index) override;

	virtual void LoadMainMenu() override;
	
	void RefreshServerList() override;

private:
	void OnCreateSessionComplete(FName InSessionName, bool InSuccess);
	void OnDestroySessionComplete(FName InSessionName, bool InSuccess);
	void OnFindSessionComplete(bool InSucess);
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InResult);

	void CreateSession();

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UCMainMenu* Menu;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
};
