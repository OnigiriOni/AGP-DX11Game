#include "camera.h"

Camera::Camera()
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->rotation = 0.0;

	CalculateViewMatrix();
}

Camera::Camera(XMVECTOR position)
{
	this->x = position.x;
	this->y = position.y;
	this->z = position.z;
	this->rotation = 0.0;

	CalculateViewMatrix();
}

Camera::Camera(XMVECTOR position, float rotation)
{
	this->x = position.x;
	this->y = position.y;
	this->z = position.z;
	this->rotation = rotation;

	CalculateViewMatrix();
}

Camera::Camera(float x, float y, float z, float rotation)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->rotation = rotation;

	CalculateViewMatrix();
}

Camera::~Camera()
{

}

void Camera::Rotate(float degree)
{
	rotation += degree;

	//CalculateViewMatrix();
}

void Camera::Forward(float distance)
{
	this->x += distance * dx;
	this->z += distance * dz;

	//CalculateViewMatrix();
}

void Camera::Up(float distance)
{
	this->y += distance;

	//CalculateViewMatrix();
}

XMMATRIX Camera::CalculateViewMatrix()
{
	dx = sin(rotation * (XM_PI / 180.0));
	dz = cos(rotation * (XM_PI / 180.0));

	position = XMVectorSet(x, y, z, 0.0);
	lookat = XMVectorSet(x + dx, y, z + dz, 0.0);
	up = XMVectorSet(0.0, 1.0, 0.0, 0.0);

	view = XMMatrixLookAtLH(position, lookat, up);

	return view;
}