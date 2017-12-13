#include "Transform.h"

void Transform::CalculateWorldMatrix()
{
	// World
	world = XMMatrixIdentity();
	world *= XMMatrixScalingFromVector(scale);
	world *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	world *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	world *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	world *= XMMatrixTranslationFromVector(position);

	// Forward
	float dx = sin(rotation.y * (XM_PI / 180.0));
	float dz = cos(rotation.y * (XM_PI / 180.0));
	forward = XMVectorSet(position.x + dx, position.y, position.z + dz, 0.0f);
	forward = XMVector3Normalize(forward);
	
	// Right
	right = XMVector3Cross(forward, up);
}

Transform::Transform()
{
}

Transform::Transform(XMVECTOR position)
{
	Transform::position = position;
}

Transform::~Transform()
{
}

void Transform::Update()
{
	CalculateWorldMatrix();
}

void Transform::LookAtXZ(XMVECTOR point)
{
	float angle = atan2((point.x - position.x), (point.z - position.z)) * (180.0f / XM_PI);
	rotation.y = angle;
}

void Transform::RotateNormal(XMVECTOR normalAxis, float degrees)
{
	normalAxis = XMVector3Normalize(normalAxis);

	rotation.x += normalAxis.x * degrees;
	rotation.y += normalAxis.y * degrees;
	rotation.z += normalAxis.z * degrees;
}
