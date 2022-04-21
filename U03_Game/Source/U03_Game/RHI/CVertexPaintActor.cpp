#include "CVertexPaintActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACVertexPaintActor::ACVertexPaintActor()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/StaticMeshes/SM_Cube.SM_Cube'");
	Mesh->SetStaticMesh(mesh);

	UMaterialInstanceConstant* material;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_VertexColor_Inst.MAT_VertexColor_Inst'");
	Mesh->SetMaterial(0, material);
}

void ACVertexPaintActor::BeginPlay()
{
	Super::BeginPlay();
	
	UKismetSystemLibrary::K2_SetTimer(this, "ChangeVertexColor", 1.0f, true);
}

void ACVertexPaintActor::ChangeVertexColor()
{
	Mesh->SetLODDataCount(1, Mesh->LODData.Num());

	UStaticMesh* mesh = Mesh->GetStaticMesh();

	FStaticMeshComponentLODInfo* lodInfo = &Mesh->LODData[0];
	lodInfo->PaintedVertices.Empty();
	lodInfo->OverrideVertexColors = new FColorVertexBuffer();

	FStaticMeshLODResources* resource = &mesh->RenderData->LODResources[0];

	TArray<FColor> colors;
	colors.Reserve(resource->GetNumVertices() - 1);

	for (int32 i = 0; i < resource->GetNumVertices(); i++)
	{
		colors.Add(FColor::MakeRandomColor());
	}
	
	lodInfo->OverrideVertexColors->InitFromColorArray(colors);

	BeginInitResource(lodInfo->OverrideVertexColors);
	Mesh->MarkRenderStateDirty();
}