#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IMenuInterface.h"
#include "CMainMenu.generated.h"

UCLASS()
class U04_MULTIPLAY_API UCMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IIMenuInterface* InMenuInterface);

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
		void HostServer();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* Host;

	UPROPERTY(meta = (BindWidget))
		class UButton* Join;

private:
	IIMenuInterface* MenuInterface;
};
