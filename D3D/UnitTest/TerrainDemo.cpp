#include "stdafx.h"
#include "TerrainDemo.h"

void TerrainDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(13, 0, 0);
	Context::Get()->GetCamera()->Position(100, 95, -130);
	dynamic_cast<Freedom*>(Context::Get()->GetCamera())->Speed(50, 2);

	shader = new Shader(L"09_Terrain.fxo");

	terrain = new Terrain(shader, L"Terrain/Gray256.png");
	terrain->BaseMap(L"Terrain/Cliff (Layered Rock).jpg");
}

void TerrainDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
}

void TerrainDemo::Update()
{
	//Lambert Test
	static Vector3 LightDirection = Vector3(-1, -1, 1);
	ImGui::SliderFloat3("LightDirection", LightDirection, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(LightDirection);

	static UINT Albedo = 1;
	ImGui::RadioButton("Albedo", (int*)&Albedo, 1);
	ImGui::SameLine();
	ImGui::RadioButton("Lambert", (int*)&Albedo, 0);
	shader->AsScalar("Albedo")->SetInt(Albedo);

	terrain->Update();
}

void TerrainDemo::Render()
{
	terrain->Render();
}
