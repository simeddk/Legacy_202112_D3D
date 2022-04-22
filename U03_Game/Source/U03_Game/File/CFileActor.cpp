#include "CFileActor.h"
#include "Global.h"
#include "Serialization/BufferArchive.h"

ACFileActor::ACFileActor()
{
	CHelpers::CreateActorComponent<UInputComponent>(this, &InputComponent, "InputComponent");
}

void ACFileActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	CheckNull(controller);
	EnableInput(controller);
	
	InputComponent->BindAction("SaveFile", EInputEvent::IE_Pressed, this, &ACFileActor::OnSaveFile);
	InputComponent->BindAction("LoadFile", EInputEvent::IE_Pressed, this, &ACFileActor::OnLoadFile);
}


void ACFileActor::OnSaveFile()
{
	FDataStruct data;
	data.ID = "someddk";
	data.Key = 777;

	FBufferArchive buffer;
	//buffer << data.ID;
	//buffer << data.Key;
	buffer << data;

	CheckTrue(buffer.Num() < 1);
	buffer.FlushCache();

	FString path = FPaths::ProjectDir() + FString("Test.bin");
	bool b = FFileHelper::SaveArrayToFile(buffer, *path);

	buffer.Empty();

	CLog::Print(b ? "Save Succeed" : "Save Failed");

	buffer.Close();
}

void ACFileActor::OnLoadFile()
{
	FString path = FPaths::ProjectDir() + FString("Test.bin");
	
	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *path);

	FMemoryReader reader = FMemoryReader(buffer, true);
	reader.Seek(0);

	FDataStruct data;
	//reader << data.ID;
	//reader << data.Key;
	reader << data;

	CLog::Print(data.ID.ToString(), -1, 10.0f, FColor::Green);
	CLog::Print((int32)data.Key, -1, 10.0f, FColor::Green);

	reader.FlushCache();
	reader.Close();
}