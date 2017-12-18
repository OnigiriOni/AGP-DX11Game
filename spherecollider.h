#pragma once
#include "component.h"

class SphereCollider : public Component
{
private:
	void SetSphere();

public:
	XMVECTOR		localePosition;
	float			radiusScale;
	float			radius;

	SphereCollider(NewGameObject*  parentObject);

	bool CheckCollision(SphereCollider* otherCollider);
	bool CheckCollision(SphereCollider* otherCollider, SphereCollider* thisCollider);

	void Update();

	XMVECTOR GetWorldPosition();
	float GetRadius();
};