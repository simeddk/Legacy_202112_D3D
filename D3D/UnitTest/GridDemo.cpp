#include "stdafx.h"
#include "GridDemo.h"

void GridDemo::Initialize()
{
	shader = new Shader(L"06_Grid.fxo");

	vertexCount = (width + 1) * (height + 1);
	vertices = new Vertex[vertexCount];

	//Create VertexData
	for (UINT y = 0; y <= height; y++)
	{
		for (UINT x = 0; x <= width; x++)
		{
			UINT index = (width + 1) * y + x;

			vertices[index].Position.x = (float)x;
			vertices[index].Position.y = (float)y;
			vertices[index].Position.z = 0.0f;
		}
	}

	//Create VertexBuffer
	{
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
}

void GridDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void GridDemo::Update()
{
	
}

void GridDemo::Render()
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
