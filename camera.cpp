#include "camera.h"
#include "gameobject.h"
#include "renderer.h"

void Camera::CalculateProjectionMatrix()
{
	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

void Camera::CalculateViewMatrix()
{
	view = XMMatrixLookAtLH(gameObject->transform->position, gameObject->transform->position + gameObject->transform->forward, gameObject->transform->up);
}

Camera::Camera(GameObject* parentObject)
{
	gameObject = parentObject;
	name = "Camera";

	CalculateProjectionMatrix();
	CalculateViewMatrix();

	Renderer::GetInstance()->AddCamera(this);
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return projection;
}

XMMATRIX Camera::GetViewMatrix()
{
	return view;
}

void Camera::SetSkyBox(char* objectFilename, char* textureFilename)
{
	skyBox = new Model();
	skyBox->SetModel(objectFilename);
	skyBox->SetTexture(textureFilename);
}

void Camera::RenderSkyBox()
{
	Renderer* renderer = Renderer::GetInstance();

	renderer->immediateContext->RSSetState(renderer->rasterSkyBox);
	renderer->immediateContext->OMSetDepthStencilState(renderer->depthWriteSkyBox, 1);

	// Normal skybox - move delay!?!?
	XMMATRIX world = XMMatrixIdentity();
	world *= XMMatrixScalingFromVector(gameObject->transform->scale);
	world *= XMMatrixTranslationFromVector(gameObject->transform->position);

	// Static background - no move delay
	//XMMATRIX world = gameObject->transform->GetWorldMatrix();


	renderer->Draw(skyBox, &world);

	renderer->immediateContext->OMSetDepthStencilState(renderer->depthWriteSolid, 1);
	renderer->immediateContext->RSSetState(renderer->rasterSolid);

	renderer = nullptr;
}

void Camera::Update()
{
	if (!isEnabled) return;

	CalculateViewMatrix();
}

void Camera::SetFieldOfView(float newFieldOfView)
{
	fieldOfView = newFieldOfView;

	CalculateProjectionMatrix();
}

void Camera::SetAspectRatio(float screenWidth, float screenHeight)
{
	aspectRatio = screenWidth / screenHeight;

	CalculateProjectionMatrix();
}

void Camera::SetNearPlane(float newNearPlane)
{
	nearPlane = newNearPlane;

	CalculateProjectionMatrix();
}

void Camera::SetFarPlane(float newFarPlane)
{
	farPlane = newFarPlane;

	CalculateProjectionMatrix();
}