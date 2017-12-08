#pragma once
#include <d3d11.h>
#include <math.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

class Light {
private:
	XMVECTOR directionalLightVector;
	XMVECTOR directionalLightColour;
	XMVECTOR ambientLightColour;
public:
	Light();
	void SetVector(float x, float y, float z);
	void SetColour(float r, float g, float b);
	void SetAmbientColour(float r, float g, float b, float a);
	XMVECTOR GetVector();
	XMVECTOR GetColour();
	XMVECTOR GetAmbientColour();
};