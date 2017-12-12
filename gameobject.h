#pragma once
#include "model.h"

class GameObject
{
protected:
	// Variables
	Model*					g_pModel = NULL;
	vector<GameObject*>		g_Children;
	XMMATRIX				g_World;

	// Methods
	void CalculateWorldMatrix();

public:
	// Variables
	XMVECTOR				scale = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR				rotation = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR				position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	// Methods
	GameObject();

	void SetModel(ID3D11Device* device, ID3D11DeviceContext* context, char* filename);
	void AddChildren(GameObject* children);
	bool RemoveChildren(GameObject* children);

	void Execute(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection, Light* light);

	virtual void Update();

	void LookAtXZ(XMVECTOR point);
	void Rotate(XMVECTOR axis, float degrees);
	void MoveForward(float distance);
	void MoveRight(float distance);
};