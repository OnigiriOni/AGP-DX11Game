#pragma once
#include "component.h"

class Maze;

class Player : public Component
{
private:
	float moveSpeed = 0.3f;
	float rotateSpeed = 0.8f;

	XMVECTOR oldPosition;

public:
	Maze* maze;

	int keys = 0;

	Player(GameObject* parentObject);
	~Player();

	void Update();

	void Movement();

	void OnCollision(GameObject* thisObject, GameObject* otherObject);
};