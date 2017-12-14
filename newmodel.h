#pragma once
#include "component.h"
#include "objfilemodel.h"
#include "light.h"
#include "renderer.h"

class NewModel : public Component
{
private:
	ObjFileModel*				object;
	ID3D11ShaderResourceView*	texture;

	XMVECTOR					boundingSpereCentre;
	float						boundingSphereRadius;

	void CalculateModelCentre();
	void CalculateBoundingSphereRadius();

public:
	NewModel();

	HRESULT SetModel(char* filename);
	HRESULT SetTexture(char* filename);
	void Draw(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection, Light* light);

	void Update();

	XMVECTOR GetBoundingSphereWorldSpacePosition(XMMATRIX* objectWorld);
	float GetBoundingSphereRadius(XMVECTOR objectScale);
};