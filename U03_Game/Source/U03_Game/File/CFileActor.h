#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFileActor.generated.h"

USTRUCT(BlueprintType)
struct FDataStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName ID;

	UPROPERTY(EditAnywhere)
		uint32 Key;

	friend FArchive& operator<<(FArchive& InArchive, FDataStruct& InData)
	{
		return InArchive << InData.ID << InData.Key;
	}
};

UCLASS()
class U03_GAME_API ACFileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFileActor();

protected:
	virtual void BeginPlay() override;

private:
	void OnSaveFile();
	void OnLoadFile();

};
