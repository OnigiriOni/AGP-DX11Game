#include "spherecollider.h"
#include "newgameobject.h"

void SphereCollider::SetSphere()
{
	Model* model = gameObject->GetComponent<Model>();
	if (model)
	{
		localePosition = model->GetBoundingSphereCentre();
		radius = model->GetBoundingSphereRadius();
		radiusScale = 1.0f;
	}
	else
	{
		localePosition = XMVectorZero();
		radius = 1.0f;
		radiusScale = 1.0f;
	}
}

SphereCollider::SphereCollider(NewGameObject* parentObject)
{
	gameObject = parentObject;
	name = "SphereCollider";

	SetSphere();
}

bool SphereCollider::CheckCollision(SphereCollider* otherCollider)
{
	return CheckCollision(otherCollider, this);
}

bool SphereCollider::CheckCollision(SphereCollider* otherCollider, SphereCollider* thisCollider)
{
	if (otherCollider == thisCollider) return false;

	if (otherCollider->isEnabled && thisCollider->isEnabled)
	{
		XMVECTOR otherWorldPosition = otherCollider->GetWorldPosition();
		XMVECTOR thisWorldPosition = thisCollider->GetWorldPosition();

		float distanceSquared = pow((otherWorldPosition.x - thisWorldPosition.x), 2) + pow((otherWorldPosition.y - thisWorldPosition.y), 2) + pow((otherWorldPosition.z - thisWorldPosition.z), 2);
		
		if (distanceSquared < pow(otherCollider->GetRadius() + thisCollider->GetRadius(), 2))
		{
			return true;
		}
	}
	
	// Iterate through compared tree child nodes
	for (int i = 0; i< otherCollider->gameObject->GetChildren().size(); i++)
	{
		// Check for collsion against all compared tree child nodes
		if (CheckCollision(otherCollider->gameObject->GetChildren()[i]->GetComponent<SphereCollider>(), thisCollider)) return true;
	}

	// Iterate through composite object child nodes
	for (int i = 0; i< thisCollider->gameObject->GetChildren().size(); i++)
	{
		// Check all the child nodes of the composite object against compared tree
		if (thisCollider->gameObject->GetChildren()[i]->GetComponent<SphereCollider>()->CheckCollision(otherCollider, thisCollider)) return true;
	}
}

void SphereCollider::Update()
{
}

XMVECTOR SphereCollider::GetWorldPosition()
{
	return XMVector3Transform(localePosition, gameObject->transform->GetWorldMatrix());
}

float SphereCollider::GetRadius()
{
	XMVECTOR objectScale = gameObject->transform->scale;

	float scaleMax = objectScale.x;
	if (objectScale.y > scaleMax)
	{
		scaleMax = objectScale.y;
	}
	if (objectScale.z > scaleMax)
	{
		scaleMax = objectScale.z;
	}

	return radius * scaleMax * radiusScale;
}