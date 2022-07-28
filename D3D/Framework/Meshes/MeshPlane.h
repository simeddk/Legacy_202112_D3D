#pragma once

class MeshPlane : public Mesh
{
public:
	MeshPlane(Shader* shader, float offsetU = 1.0f, float offsetV = 1.0f);
	~MeshPlane();

private:
	void Create() override;

	float offsetU, offsetV;
};
