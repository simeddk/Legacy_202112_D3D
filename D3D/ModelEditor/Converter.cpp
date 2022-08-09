#include "stdafx.h"
#include "Converter.h"

Converter::Converter()
{
	importer = new Assimp::Importer();
}

Converter::~Converter()
{
	SafeDelete(importer);
}

void Converter::ReadFile(wstring file)
{
	this->file = L"../../_Assets/" + file;

	scene = importer->ReadFile
	(
		String::ToString(this->file),
		aiProcess_ConvertToLeftHanded
		| aiProcess_Triangulate
		| aiProcess_GenUVCoords
		| aiProcess_GenNormals
		| aiProcess_CalcTangentSpace
	);

	if (scene == nullptr)
	{
		string str = importer->GetErrorString();

		MessageBoxA(D3D::GetDesc().Handle, str.c_str(), "FBX Import Error", MB_OK);
		exit(-1);
	}
}

void Converter::ExportMesh(wstring savePath)
{
}

void Converter::ReadBoneData(aiNode * node, int index, int parent)
{
}

void Converter::ReadMeshData(aiNode * node, int index)
{
}

void Converter::WriteMeshData(wstring savePath)
{
}
