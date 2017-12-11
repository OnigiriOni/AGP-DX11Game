#include "camera.h"

Camera::Camera()
{
	CalculateProjectionMatrix();
	CalculateViewMatrix();
}

Camera::Camera(XMVECTOR position)
{
	Camera::position = position;

	CalculateProjectionMatrix();
	CalculateViewMatrix();
}

Camera::Camera(XMVECTOR position, XMVECTOR rotation)
{
	Camera::rotation = rotation;
	Camera::position = position;

	CalculateProjectionMatrix();
	CalculateViewMatrix();
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return projection;
}

XMMATRIX Camera::GetViewMatrix()
{
	return view;
}

void Camera::Update()
{
	PlayerInput();

	CalculateViewMatrix();
}

void Camera::PlayerInput()
{
	ReadInputStates();
	if (IsKeyPressed(DIK_W))
	{
		MoveForward(0.001f);
	}

	if (IsKeyPressed(DIK_S))
	{
		MoveForward(-0.001f);
	}

	if (IsKeyPressed(DIK_A))
	{
		MoveRight(-0.001f);
	}

	if (IsKeyPressed(DIK_D))
	{
		MoveRight(0.001f);
	}

	if (IsKeyPressed(DIK_Q))
	{
		Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), -0.005f);
	}

	if (IsKeyPressed(DIK_E))
	{
		Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0.005f);
	}
}

void Camera::CalculateProjectionMatrix()
{
	projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

void Camera::CalculateViewMatrix()
{
	float dx = sin(rotation.y * (XM_PI / 180.0f));
	float dz = cos(rotation.y * (XM_PI / 180.0f));

	forward = XMVectorSet(position.x + dx, position.y, position.z + dz, 0.0f);

	view = XMMatrixLookAtLH(position, forward, up);
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