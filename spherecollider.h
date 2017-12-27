#pragma once
#include "component.h"

class SphereCollider : public Component
{
private:
	void SetSphere();

	__event void CollisionEvent(GameObject* otherObject); // TODO: Event handler ???

public:
	XMVECTOR		localePosition;
	float			radiusScale;
	float			radius;

	SphereCollider(GameObject*  parentObject);

	bool CheckCollision(GameObject* otherObject);
	void OnCollision(GameObject* otherObject);

	void Update();

	XMVECTOR GetWorldPosition();
	float GetRadius();
};