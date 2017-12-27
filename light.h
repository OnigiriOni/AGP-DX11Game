#pragma once
#include "component.h"

class Light : public Component
{
private:

public:
	XMVECTOR directionalLightVector;
	XMVECTOR directionalLightColour;
	XMVECTOR ambientLightColour;

	Light(GameObject* parentObject);

	void Update();
};