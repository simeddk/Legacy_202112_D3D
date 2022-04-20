#include "CHasButton.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACHasButton::ACHasButton()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/StaticMeshes/SM_MatPreviewMesh_01.SM_MatPreviewMesh_01'");
	Mesh->SetStaticMesh(mesh);

	UMaterialInstanceConstant* material;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Plastic_Inst.MAT_Plastic_Inst'");

	Mesh->SetMaterial(0, material);
}

void ACHasButton::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACHasButton::ApplyColor(FLinearColor InColor)
{
	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(Mesh->GetMaterial(0));

	for (FVectorParameterValue& value : material->VectorParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("BaseColor") == 0)
		{
			material->SetVectorParameterValueEditorOnly(value.ParameterInfo, InColor);
		}
	}

	
}