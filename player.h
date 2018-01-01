#pragma once
#include "component.h"

class Player : public Component
{
private:
	float moveSpeed = 0.3f;
	float rotateSpeed = 0.8f;

	XMVECTOR oldPosition;

public:
	int keys = 0;

	Player(GameObject* parentObject);

	void Update();

	void Movement();

	void OnCollision(GameObject* thisObject, GameObject* otherObject);
};