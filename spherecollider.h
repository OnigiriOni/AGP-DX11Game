#pragma once
#include "component.h"

class SphereCollider : public Component
{
private:
	void SetSphere();

	__event void CollisionEvent(NewGameObject* otherObject); // TODO: Event handler ???

public:
	XMVECTOR		localePosition;
	float			radiusScale;
	float			radius;

	SphereCollider(NewGameObject*  parentObject);

	bool CheckCollision(NewGameObject* otherObject);
	void OnCollision(NewGameObject* otherObject);

	void Update();

	XMVECTOR GetWorldPosition();
	float GetRadius();
};