#pragma once
#include "model.h"

class GameObject
{
private:
	// Variables
	Model*					g_pModel;
	vector<GameObject*>		g_Children;
	XMMATRIX				g_World;

	

	// Methods
	void CalculateWorldMatrix();

public:
	// Variables
	XMVECTOR				scale;
	XMVECTOR				rotation;
	XMVECTOR				position;

	// Methods
	GameObject();

	void SetModel(ID3D11Device* device, ID3D11DeviceContext* context, char* filename);
	void AddChildren(GameObject* children);
	bool RemoveChildren(GameObject* children);

	void Update(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection, Light* light);

	void LookAtXZ(XMVECTOR point);
	void Rotate(XMVECTOR axis, float degrees);
	void MoveForward(float distance);
};