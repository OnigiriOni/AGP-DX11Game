#pragma once
#include "component.h"

class Gate : public Component
{
private:

public:
	int requiredKeys = 2;

	float openSpeed = 0.3f;
	bool opening = false;

	XMVECTOR closedPosition;

	Gate(GameObject* parentObject);

	void Update();

	void OnCollision(GameObject* thisObject, GameObject* otherObject);

	void OpenGate();
};