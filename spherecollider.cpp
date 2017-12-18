#include "spherecollider.h"
#include "game.h"
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

	__hook(&SphereCollider::CollisionEvent, this, &SphereCollider::OnCollision);
}

bool SphereCollider::CheckCollision(NewGameObject* otherObject)
{
	if (otherObject == gameObject) return false;

	SphereCollider* otherCollider = otherObject->GetComponent<SphereCollider>();

	if (otherCollider)
	{
		if (otherCollider->isEnabled)
		{
			XMVECTOR otherWorldPosition = otherCollider->GetWorldPosition();
			XMVECTOR thisWorldPosition = GetWorldPosition();

			float distanceSquared = pow((otherWorldPosition.x - thisWorldPosition.x), 2) + pow((otherWorldPosition.y - thisWorldPosition.y), 2) + pow((otherWorldPosition.z - thisWorldPosition.z), 2);

			if (distanceSquared < pow(otherCollider->GetRadius() + GetRadius(), 2))
			{
				return true;
			}
		}
	}

	// Iterate through otherObject children
	for (NewGameObject* otherChildren : otherObject->GetChildren())
	{
		if (CheckCollision(otherChildren)) return true;
	}

	// Iterate through this component parent's children
	for (NewGameObject* thisChildren : gameObject->GetChildren())
	{
		thisChildren->name = thisChildren->name;

		SphereCollider* childCollider = thisChildren->GetComponent<SphereCollider>();

		if (childCollider)
		{
			if (childCollider->CheckCollision(otherObject)) return true;
		}
	}

	return false;
}

void SphereCollider::OnCollision(NewGameObject * otherObject)
{
	otherObject->name = otherObject->name;
	name = name;
}

void SphereCollider::Update()
{
	if (!isEnabled) return;
	if (gameObject->GetGame()->GetUpdates() < 1) return;

	vector<NewGameObject*> otherEntities = gameObject->GetGame()->GetEntities();

	for (NewGameObject* entity : otherEntities)
	{
		if (CheckCollision(entity))
		{
			// TODO: Raise event for OnCollision(). With the object, or a struct with position, objects, etc.
			__raise CollisionEvent(entity);
		}
	}
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