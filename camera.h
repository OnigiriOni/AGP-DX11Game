#pragma once
#include "component.h"

class Model;

enum CameraClearMode { COLOUR, SKYBOX };

class Camera : public Component
{
private:
	XMMATRIX					view;
	XMMATRIX					projection;

	Model*						skyBox;


	float						fieldOfView = 70.0f;
	float						aspectRatio = 640.0f / 480.0f;
	float						nearPlane = 1.0f;
	float						farPlane = 200.0f;

	void CalculateProjectionMatrix();
	void CalculateViewMatrix();

public:
	CameraClearMode				clearMode = COLOUR;

	Camera(GameObject* parentObject);

	XMMATRIX GetProjectionMatrix();
	XMMATRIX GetViewMatrix();

	void SetSkyBox(char* objectFilename, char* textureFilename);
	void RenderSkyBox();

	void Update();

	void SetFieldOfView(float newFieldOfView);
	void SetAspectRatio(float screenWidth, float screenHeight);
	void SetNearPlane(float newNearPlane);
	void SetFarPlane(float newFarPlane);
};