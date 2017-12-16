#pragma once
#include <d3d11.h>
#include <math.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

#include "component.h"

class Transform : public Component
{
private:
	XMMATRIX		world = XMMatrixIdentity();

	void CalculateWorldMatrix();

public:
	XMVECTOR		scale = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR		rotation = XMVectorZero();
	XMVECTOR		position = XMVectorZero();

	XMVECTOR		up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR		forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR		right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	Transform(NewGameObject* parentObject);
	Transform(NewGameObject* parentObject, XMVECTOR position);
	~Transform();

	void SetWorldMatrix(XMMATRIX world);
	XMMATRIX GetWorldMatrix();

	void Update();

	void LookAtXZ(XMVECTOR point);
	void RotateNormal(XMVECTOR axis, float degrees);
};