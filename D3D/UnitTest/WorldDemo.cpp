#include "stdafx.h"
#include "WorldDemo.h"

void WorldDemo::Initialize()
{
	shader = new Shader(L"05_World.fxo");

	//Create VertexBuffer
	{
		vertices[0].Position = Vector3(-0.5f, -0.5f, +0.0f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, +0.0f);
		vertices[2].Position = Vector3(+0.5f, -0.5f, +0.0f);
		vertices[3].Position = Vector3(+0.5f, +0.5f, +0.0f);

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

	D3DXMatrixIdentity(&world);
}

void WorldDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void WorldDemo::Update()
{
	Matrix S, T;

	//Scale Test
	static Vector3 scale = Vector3(1, 1, 1);
	if (Keyboard::Get()->Press(VK_RIGHT))
		scale.x += 2.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_LEFT))
		scale.x -= 2.0f * Time::Delta();

	if (Keyboard::Get()->Press(VK_UP))
		scale.y += 2.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_DOWN))
		scale.y -= 2.0f * Time::Delta();

	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);

	//Translation Test
	static Vector3 position = Vector3(0, 0, 0);
	if (Keyboard::Get()->Press('D'))
		position.x += 2.0f * Time::Delta();
	else if (Keyboard::Get()->Press('A'))
		position.x -= 2.0f * Time::Delta();

	if (Keyboard::Get()->Press('W'))
		position.y += 2.0f * Time::Delta();
	else if (Keyboard::Get()->Press('S'))
		position.y -= 2.0f * Time::Delta();
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * T;

	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void WorldDemo::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	static bool bWireFrame = false;
	ImGui::Checkbox("Wireframe Mode", &bWireFrame);

	shader->DrawIndexed(0, (bWireFrame ? 1 : 0), 6);
}
