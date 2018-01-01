#pragma once
#include "component.h"

class Transform : public Component
{
private:
	XMMATRIX		world = XMMatrixIdentity();
	XMMATRIX		worldWithoutRotation = XMMatrixIdentity();

	void CalculateWorldMatrix();

public:
	XMVECTOR		scale = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR		rotation = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR		position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR		up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR		forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR		right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	Transform(GameObject* parentObject);
	Transform(GameObject* parentObject, XMVECTOR position);
	~Transform();

	void SetWorldMatrix(XMMATRIX world);
	XMMATRIX GetWorldMatrix();
	XMMATRIX GetWorldWithoutRotation();

	void Update();

	void LookAtXZ(XMVECTOR point);
	void RotateNormal(XMVECTOR axis, float degrees);
};