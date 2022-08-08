#pragma once
#include "Systems/IExecute.h"

class MultiWorldDemo : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:
	struct Vertex
	{
		Vector3 Position;
	};

private:
	Shader* shader;

	Vertex vertices[4];
	ID3D11Buffer* vertexBuffer;

	ID3D11Buffer* indexBuffer;

	Matrix worlds[10];
	Color colors[10];
};