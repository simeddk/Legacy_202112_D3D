#pragma once

class Freedom : public Camera
{
public:
	Freedom();
	~Freedom();

	void Update() override;

	void Speed(float move, float rotation = 2.0f);

private:
	float moveSpeed = 20.0f;
	float rotationSpeed = 2.0f;
};