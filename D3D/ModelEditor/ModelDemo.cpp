#include "stdafx.h"
#include "ModelDemo.h"
#include "Converter.h"

void ModelDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(16, -3, 0);
	Context::Get()->GetCamera()->Position(-4, 9, -17);
	((Freedom *)Context::Get()->GetCamera())->Speed(10, 2);

	shader = new Shader(L"13_Model.fxo");

	Tank();
	Kachujin();
	Tower();
	Airplane();

	sky = new CubeSky(L"Environment/GrassCube1024.dds");
	sky->Pass(2);
	planeShader = new Shader(L"10_Mesh.fx");

	plane = new MeshPlane(planeShader, 6, 6);
	plane->GetTransform()->Scale(12, 1, 12);
	plane->DiffuseMap(L"Floor.png");
}

void ModelDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(tank);
	SafeDelete(kachujin);
	SafeDelete(tower);
	SafeDelete(airplane);

	SafeDelete(sky);
	SafeDelete(planeShader);
	SafeDelete(plane);
}

void ModelDemo::Update()
{
	//Lambert Test
	static Vector3 LightDirection = Vector3(-1, -1, +1);
	ImGui::SliderFloat3("LightDirection", LightDirection, -1, +1);
	shader->AsVector("LightDirection")->SetFloatVector(LightDirection);
	planeShader->AsVector("LightDirection")->SetFloatVector(LightDirection);

	//WireFrame Test
	static UINT pass = 0;
	ImGui::InputInt("Pass", (int *)&pass);
	pass %= 2;
	
	

	sky->Update();
	plane->Update();

	if (tank != nullptr)
	{
		tank->Pass(pass);
		tank->Update();
	}

	if (kachujin != nullptr)
	{
		kachujin->Pass(pass);
		kachujin->Update();
	}

	if (tower != nullptr)
	{
		tower->Pass(pass);
		tower->Update();
	}

	if (airplane != nullptr)
	{
		airplane->Pass(pass);
		airplane->Update();
	}
}

void ModelDemo::Render()
{
	sky->Render();
	plane->Render();

	if (tank != nullptr)
		tank->Render();

	if (kachujin != nullptr)
		kachujin->Render();

	if (tower != nullptr)
		tower->Render();

	if (airplane != nullptr)
		airplane->Render();
}

void ModelDemo::Tank()
{
	tank = new ModelRender(shader);
	tank->ReadMesh(L"Tank/Tank");
	tank->ReadMaterial(L"Tank/Tank");
}

void ModelDemo::Kachujin()
{
	kachujin = new ModelRender(shader);
	kachujin->ReadMesh(L"Kachujin/Mesh");
	kachujin->ReadMaterial(L"Kachujin/Mesh");
	kachujin->GetTransform()->Position(5, 0, 0);
	kachujin->GetTransform()->Scale(0.01f, 0.01f, 0.01f);
}

void ModelDemo::Tower()
{
	tower = new ModelRender(shader);
	tower->ReadMesh(L"Tower/Tower");
	tower->ReadMaterial(L"Tower/Tower");
	tower->GetTransform()->Position(-5, 0, 0);
	tower->GetTransform()->Scale(0.01f, 0.01f, 0.01f);
}

void ModelDemo::Airplane()
{
	airplane = new ModelRender(shader);
	airplane->ReadMesh(L"B787/Airplane");
	airplane->ReadMaterial(L"B787/Airplane");
	airplane->GetTransform()->Position(-10, 0, 0);
	airplane->GetTransform()->Scale(0.001f, 0.001f, 0.001f);
}
