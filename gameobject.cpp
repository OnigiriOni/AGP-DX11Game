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
	name = "GameObject";
}

GameObject::GameObject(char* name)
{
	GameObject::name = name;
}

void GameObject::SetModel(ID3D11Device* device, ID3D11DeviceContext* context, char* filenameModel)
{
	//g_pModel = new Model(device, context, filenameModel);
}

void GameObject::SetModel(ID3D11Device* device, ID3D11DeviceContext* context, char* filenameModel, char* filenameTexture)
{
	//g_pModel = new Model(device, context, filenameModel, filenameTexture);
}

Model* GameObject::GetModel()
{
	return g_pModel;
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

void GameObject::UpdateCollisionTree(XMMATRIX* world, XMVECTOR* scale)
{
	CalculateWorldMatrix();
	g_World *= *world;

	g_WorldScale = GameObject::scale * (*scale);

	if (g_pModel)
	{
		g_WorldPosition = g_pModel->GetBoundingSphereWorldSpacePosition(&g_World);
	}

	for (int i = 0; i< g_Children.size(); i++)
	{
		g_Children[i]->UpdateCollisionTree(&g_World, &g_WorldScale);
	}
}

bool GameObject::CheckCollision(GameObject* otherGameObject)
{
	return CheckCollision(otherGameObject, this);
}

bool GameObject::CheckCollision(GameObject* otherGameObject, GameObject* thisObject)
{
	if (otherGameObject == thisObject)
	{
		return false;
	}

	// Check collision if both GameObjects have models
	if (g_pModel && otherGameObject->g_pModel)
	{
		XMVECTOR otherWorldPosition = otherGameObject->g_WorldPosition;

		float thisBSRadius = g_pModel->GetBoundingSphereRadius(scale);
		float otherBSRadius = otherGameObject->g_pModel->GetBoundingSphereRadius(otherGameObject->scale);

		float distanceSquared = pow((otherWorldPosition.x - g_WorldPosition.x), 2) + pow((otherWorldPosition.y - g_WorldPosition.y), 2) + pow((otherWorldPosition.z - g_WorldPosition.z), 2);
		
		if (distanceSquared < pow(otherBSRadius + thisBSRadius, 2))
		{
			return true;
		}
	}

	// Iterate through compared tree child nodes
	for (int i = 0; i< otherGameObject->g_Children.size(); i++)
	{
		// Check for collsion against all compared tree child nodes
		if (CheckCollision(otherGameObject->g_Children[i], thisObject) == true) return true;
	}

	// Iterate through composite object child nodes
	for (int i = 0; i< g_Children.size(); i++)
	{
		// Check all the child nodes of the composite object against compared tree
		if (g_Children[i]->CheckCollision(otherGameObject, thisObject) == true) return true;
	}

	return false;
}

void GameObject::Execute(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection, Light* light)
{
	//CalculateWorldMatrix();

	//g_World *= *world;

	//if (g_pModel) g_pModel->Draw(&g_World, view, projection, light);

	//// TODO: Scale gets transported through all child objects, fix this
	//for (int i = 0; i< g_Children.size(); i++)
	//{
	//	g_Children[i]->Execute(&g_World, view, projection, light);
	//	g_Children[i]->Update();
	//}
}

void GameObject::Update()
{
	
}

XMVECTOR GameObject::GetWorldScale()
{
	return g_WorldScale;
}

XMVECTOR GameObject::GetWorldPosition()
{
	return g_WorldPosition;
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

void GameObject::MoveRight(float distance)
{
	MoveRight(distance, this);
}

void GameObject::MoveRight(float distance, GameObject* rootObject)
{
	float oldPosition = position.x;
	position.x += distance;

	rootObject->UpdateCollisionTree(&XMMatrixIdentity(), &scale);

	if (CheckCollision(rootObject))
	{
		position.x = oldPosition;
	}
}
