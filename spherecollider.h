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

	bool CheckCollision(NewGameObject* otherObject);

	void Update();

	XMVECTOR GetWorldPosition();
	float GetRadius();
};