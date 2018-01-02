#pragma once
#include "component.h"

class Key : public Component
{
private:
	float rotateSpeed = 0.8f;

public:
	int charges = 1;

	Key(GameObject* parentObject);

	void Update();

	void Rotate();
};