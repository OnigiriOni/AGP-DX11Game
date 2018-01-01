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

	worldWithoutRotation = XMMatrixIdentity();
	worldWithoutRotation *= XMMatrixScalingFromVector(scale);
	worldWithoutRotation *= XMMatrixTranslationFromVector(position);

	// Forward
	float dx = sin(rotation.y * (XM_PI / 180.0));
	float dz = cos(rotation.y * (XM_PI / 180.0));
	forward = XMVectorSet(dx, 0.0f, dz, 0.0f);
	forward = XMVector3Normalize(forward);
	
	// Right
	right = -XMVector3Cross(forward, up);
}

Transform::Transform(GameObject* parentObject)
{
	gameObject = parentObject;
	name = "Transform";
}

Transform::Transform(GameObject* parentObject, XMVECTOR position)
{
	gameObject = parentObject;
	Transform::position = position;
	name = "Transform";
}

Transform::~Transform()
{
}

void Transform::SetWorldMatrix(XMMATRIX world)
{
	Transform::world = world;
}

XMMATRIX Transform::GetWorldMatrix()
{
	return world;
}

XMMATRIX Transform::GetWorldWithoutRotation()
{
	return worldWithoutRotation;
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