#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CHasButton.generated.h"

UCLASS()
class U03_GAME_API ACHasButton : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	
public:	
	ACHasButton();

	void ApplyColor(FLinearColor InColor);

protected:
	virtual void BeginPlay() override;


};
