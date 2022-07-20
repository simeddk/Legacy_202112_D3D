#include "stdafx.h"
#include "MultiWorldDemo.h"

void MultiWorldDemo::Initialize()
{
	shader = new Shader(L"05_World.fxo");

	//Create VertexBuffer
	{
		vertices[0].Position = Vector3(-0.5f - 0.5f, -0.5f - 0.5f, +0.0f);
		vertices[1].Position = Vector3(-0.5f - 0.5f, +0.5f - 0.5f, +0.0f);
		vertices[2].Position = Vector3(+0.5f - 0.5f, -0.5f - 0.5f, +0.0f);
		vertices[3].Position = Vector3(+0.5f - 0.5f, +0.5f - 0.5f, +0.0f);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Create IndexBuffer
	{
		UINT indices[] = { 0, 1, 2, 2, 1, 3 };

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}

	for (UINT i = 0; i < 10; i++)
	{
		Vector3 scale = Math::RandomVec3(0.5f, 2.0f);
		Vector3 position = Math::RandomVec3(-3.0f, 3.0f);
		position.z = 0.0f;

		Matrix S, T;
		D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
		D3DXMatrixTranslation(&T, position.x, position.y, position.z);

		worlds[i] = S * T;
		colors[i] = Math::RandomColor4();
	}
}

void MultiWorldDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void MultiWorldDemo::Update()
{
	//Index
	static UINT index = 0;
	{
		if (Keyboard::Get()->Down(VK_ADD)) index++;
		if (Keyboard::Get()->Down(VK_SUBTRACT)) index--;

		index = Math::Clamp<UINT>(index, 0, ARRAYSIZE(worlds) - 1);

		ImVec4 textColor = ImVec4(colors[index].r, colors[index].g, colors[index].b, colors[index].a);
		ImGui::TextColored(textColor, "[%d]", index);

		Vector2 position = Vector2(worlds[index]._41, worlds[index]._42);
		Vector2 scale = Vector2(worlds[index]._11, worlds[index]._22);
		ImGui::TextColored(textColor, "Position : %.2f, %.2f", position.x, position.y);
		ImGui::TextColored(textColor, "Scale : %.2f, %.2f", scale.x, scale.y);
	}

	//Scale
	if (Keyboard::Get()->Press(VK_SHIFT))
	{
		if (Keyboard::Get()->Press('D'))
			worlds[index]._11 += 2.0f * Time::Delta();
		else if (Keyboard::Get()->Press('A'))
			worlds[index]._11 -= 2.0f * Time::Delta();

		if (Keyboard::Get()->Press('W'))
			worlds[index]._22 += 2.0f * Time::Delta();
		else if (Keyboard::Get()->Press('S'))
			worlds[index]._22 -= 2.0f * Time::Delta();
	}
	else
	{
		if (Keyboard::Get()->Press('D'))
			worlds[index]._41 += 2.0f * Time::Delta();
		else if (Keyboard::Get()->Press('A'))
			worlds[index]._41 -= 2.0f * Time::Delta();

		if (Keyboard::Get()->Press('W'))
			worlds[index]._42 += 2.0f * Time::Delta();
		else if (Keyboard::Get()->Press('S'))
			worlds[index]._42 -= 2.0f * Time::Delta();
	}

	//Rotation
	if (Keyboard::Get()->Press('Q'))
	{
		for (auto& W : worlds)
		{
			Vector3 scale, rotation, position;
			Math::MatrixDecompose(W, scale, rotation, position);
			rotation.z += 10.0f * Time::Delta();

			Matrix S, R, T;
			D3DXMatrixScaling(&S, scale.x, scale.y, scale.y);
			D3DXMatrixRotationZ(&R, rotation.z);
			D3DXMatrixTranslation(&T, position.x, position.y, position.z);
			
			W = S * R * T; //RH = T * R * S
			
		}
	}


	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void MultiWorldDemo::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	static bool bWireFrame = false;
	ImGui::Checkbox("Wireframe Mode", &bWireFrame);

	for (UINT i = 0; i < 10; i++)
	{
		shader->AsMatrix("World")->SetMatrix(worlds[i]);
		shader->AsVector("Color")->SetFloatVector(colors[i]);

		shader->DrawIndexed(0, (bWireFrame ? 1 : 0), 6);
	}
	
}
