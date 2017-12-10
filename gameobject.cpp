#include "gameobject.h"

void GameObject::CalculateWorldMatrix()
{
	g_World = XMMatrixIdentity();
	g_World *= XMMatrixScalingFromVector(scale);
	g_World *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	g_World *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	g_World *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	g_World *= XMMatrixTranslationFromVector(position);
}

GameObject::GameObject()
{
	g_pModel = NULL;

	scale = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	rotation = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	position = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
}

void GameObject::SetModel(ID3D11Device* device, ID3D11DeviceContext* context, char* filename)
{
	g_pModel = new Model(device, context, filename);
}

void GameObject::AddChildren(GameObject* children)
{
	g_Children.push_back(children);
}

bool GameObject::RemoveChildren(GameObject* children)
{
	for (int i = 0; i < g_Children.size(); i++)
	{
		if (children == g_Children[i])
		{
			g_Children.erase(g_Children.begin() + i);
			return true;
		}
		if (g_Children[i]->RemoveChildren(children) == true) return true;
	}
	return false;
}

void GameObject::Update(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection, Light* light)
{
	CalculateWorldMatrix();

	g_World *= *world;

	if (g_pModel) g_pModel->Draw(&g_World, view, projection, light);

	for (int i = 0; i< g_Children.size(); i++)
	{
		g_Children[i]->Update(&g_World, view, projection, light);
	}
}

void GameObject::LookAtXZ(XMVECTOR point)
{
	float angle = atan2((point.x - position.x), (point.z - position.z)) * (180.0f / XM_PI);
	rotation.y = angle;
}

// Rotates the model around an (single) axis in world space by degrees
void GameObject::Rotate(XMVECTOR axis, float degrees)
{
	axis = XMVector3Normalize(axis);

	rotation.x += axis.x * degrees;
	rotation.y += axis.y * degrees;
	rotation.z += axis.z * degrees;
}

void GameObject::MoveForward(float distance)
{
	float dx = sin(rotation.y * (XM_PI / 180.0));
	float dz = cos(rotation.y * (XM_PI / 180.0));

	position.x += distance * dx;
	position.z += distance * dz;
}