#include "light.h"

Light::Light()
{
	directionalLightVector = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	directionalLightColour = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	ambientLightColour = XMVectorSet(0.1f, 0.1f, 0.1f, 1.0f);
}

void Light::SetVector(float x, float y, float z)
{
	directionalLightVector = XMVectorSet(x, y, z, 0.0f);
}

void Light::SetColour(float r, float g, float b)
{
	directionalLightColour = XMVectorSet(r, g, b, 0.0f);
}

void Light::SetAmbientColour(float r, float g, float b, float a)
{
	ambientLightColour = XMVectorSet(r, g, b, a);
}

XMVECTOR Light::GetVector()
{
	return directionalLightVector;
}

XMVECTOR Light::GetColour()
{
	return directionalLightColour;
}

XMVECTOR Light::GetAmbientColour()
{
	return ambientLightColour;
}
