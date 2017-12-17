#pragma once
#include "inputmanager.h"
#include "gameobject.h"

class Camera : public GameObject
{
private:
	// Variables
	XMVECTOR				forward;
	XMVECTOR				up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX				view;
	XMMATRIX				projection;

	float					fieldOfView = 70.0f;
	float					aspectRatio = 640.0f / 480.0f;
	float					nearPlane = 1.0f;
	float					farPlane = 200.0f;
	
	// Methods
	void CalculateProjectionMatrix();
	void CalculateViewMatrix();

public:
	// Methods
	Camera();
	Camera(XMVECTOR position);
	Camera(XMVECTOR position, XMVECTOR forward);

	XMMATRIX GetProjectionMatrix();
	XMMATRIX GetViewMatrix();

	void Update();

	void PlayerInput();

	void SetFieldOfView(float newFieldOfView);
	void SetAspectRatio(float screenWidth, float screenHeight);
	void SetNearPlane(float newNearPlane);
	void SetFarPlane(float newFarPlane);
};