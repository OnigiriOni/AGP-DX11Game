#pragma once
#include "component.h"

class NewCamera : public Component
{
private:
	XMMATRIX				view;
	XMMATRIX				projection;

	float					fieldOfView = 70.0f;
	float					aspectRatio = 640.0f / 480.0f;
	float					nearPlane = 1.0f;
	float					farPlane = 200.0f;

	void CalculateProjectionMatrix();
	void CalculateViewMatrix();

public:
	NewCamera(NewGameObject* parentObject);

	XMMATRIX GetProjectionMatrix();
	XMMATRIX GetViewMatrix();

	void Update();

	void SetFieldOfView(float newFieldOfView);
	void SetAspectRatio(float screenWidth, float screenHeight);
	void SetNearPlane(float newNearPlane);
	void SetFarPlane(float newFarPlane);
};