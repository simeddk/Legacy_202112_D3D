#include "CMontagesComponent.h"
#include "Global.h"

UCMontagesComponent::UCMontagesComponent()
{

}


void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	DataTable->GetAllRows<FMontageData>("", MontageDatas);
	for (const FMontageData* data : MontageDatas)
		CLog::Print(data->AnimMontage->GetName() + ", " + FString::SanitizeFloat(data->PlayRate));
	
}


