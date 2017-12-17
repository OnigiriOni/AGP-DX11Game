#pragma once
#include <d3d11.h>
#include <math.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

#include "model.h"
#include "light.h"

class GameObject
{
protected:
	// Variables
	Model*					g_pModel = NULL;
	vector<GameObject*>		g_Children;
	XMMATRIX				g_World;

	XMVECTOR				g_WorldScale;
	XMVECTOR				g_WorldPosition;

	// Methods
	void CalculateWorldMatrix();

public:
	// Variables
	char*					name;
	XMVECTOR				scale = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR				rotation = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR				position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	// Methods
	GameObject();
	GameObject(char* name);

	void SetModel(ID3D11Device* device, ID3D11DeviceContext* context, char* filenameModel);
	void SetModel(ID3D11Device* device, ID3D11DeviceContext* context, char* filenameModel, char* filenameTexture);

	Model* GetModel();
	void AddChildren(GameObject* children);
	bool RemoveChildren(GameObject* children);

	void UpdateCollisionTree(XMMATRIX* world, XMVECTOR* scale);
	bool CheckCollision(GameObject* otherGameObject);
	bool CheckCollision(GameObject* otherGameObject, GameObject* rootObject);

	void Execute(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection, Light* light);
	virtual void Update();

	XMVECTOR GetWorldScale();
	XMVECTOR GetWorldPosition();

	void LookAtXZ(XMVECTOR point);
	void Rotate(XMVECTOR axis, float degrees);
	void MoveForward(float distance);
	void MoveRight(float distance);
	void MoveRight(float distance, GameObject* collisionRootObject);
};