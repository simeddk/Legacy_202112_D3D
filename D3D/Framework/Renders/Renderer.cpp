#include "Framework.h"
#include "Renderer.h"

Renderer::Renderer(Shader * shader)
	: shader(shader)
	, bCreateShader(false)
{
	Initialize();
}

Renderer::Renderer(wstring shaderFile)
	: bCreateShader(true)
{
	shader = new Shader(shaderFile);

	Initialize();
}


void Renderer::Initialize()
{
	transform = new Transform(shader);
	perFrame = new PerFrame(shader);
}


Renderer::~Renderer()
{
	SafeDelete(transform);
	SafeDelete(perFrame);

	SafeDelete(vertexBuffer);
	SafeDelete(indexBuffer);

	if (bCreateShader == true)
		SafeDelete(shader);
}

void Renderer::Update()
{
	perFrame->Update();
	transform->Update();
}

void Renderer::Render()
{
	if (vertexBuffer != nullptr)
	{
		vertexBuffer->Render();

		if (indexBuffer != nullptr)
			indexBuffer->Render();
	}

	D3D::GetDC()->IASetPrimitiveTopology(topology);

	perFrame->Render();
	transform->Render();
}
