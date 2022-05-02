#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

UCLASS()
class U04_MULTIPLAY_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()
		
public:
	UCGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();

public:
	UFUNCTION(BlueprintCallable, Exec)
		void LoadMenu();

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& InAddress);

private:
	TSubclassOf<class UUserWidget> MenuClass;
};
