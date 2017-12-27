#include "newcamera.h"
#include "newgameobject.h"
#include "renderer.h"

void NewCamera::CalculateProjectionMatrix()
{
	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

void NewCamera::CalculateViewMatrix()
{
	view = XMMatrixLookAtLH(gameObject->transform->position, gameObject->transform->forward, gameObject->transform->up);
}

NewCamera::NewCamera(NewGameObject* parentObject)
{
	gameObject = parentObject;
	name = "Camera";

	CalculateProjectionMatrix();
	CalculateViewMatrix();

	Renderer::GetInstance()->AddCamera(this);
}

XMMATRIX NewCamera::GetProjectionMatrix()
{
	return projection;
}

XMMATRIX NewCamera::GetViewMatrix()
{
	return view;
}

void NewCamera::Update()
{
	if (!isEnabled) return;

	CalculateViewMatrix();
}

void NewCamera::SetFieldOfView(float newFieldOfView)
{
	fieldOfView = newFieldOfView;

	CalculateProjectionMatrix();
}

void NewCamera::SetAspectRatio(float screenWidth, float screenHeight)
{
	aspectRatio = screenWidth / screenHeight;

	CalculateProjectionMatrix();
}

void NewCamera::SetNearPlane(float newNearPlane)
{
	nearPlane = newNearPlane;

	CalculateProjectionMatrix();
}

void NewCamera::SetFarPlane(float newFarPlane)
{
	farPlane = newFarPlane;

	CalculateProjectionMatrix();
}