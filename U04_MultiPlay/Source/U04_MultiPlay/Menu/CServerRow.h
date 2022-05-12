#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CServerRow.generated.h"

UCLASS()
class U04_MULTIPLAY_API UCServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ServerName;
};
