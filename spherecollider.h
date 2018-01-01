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

	SphereCollider(GameObject*  parentObject);

	bool CheckCollision(GameObject* otherObject);
	__event void OnCollision(GameObject* thisObject, GameObject* otherObject);

	void Update();

	XMVECTOR GetWorldPosition();
	float GetRadius();
};