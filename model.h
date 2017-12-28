#pragma once
#include "component.h"
#include "objfilemodel.h"

class ObjFileModel;

class Model : public Component
{
private:
	ObjFileModel*				object;
	ID3D11ShaderResourceView*	texture;

	XMVECTOR					boundingSpereCentre;
	float						boundingSphereRadius;

	void CalculateModelCentre();
	void CalculateBoundingSphereRadius();

public:
	Model();
	Model(GameObject* parentObject);

	HRESULT SetModel(char* filename);
	HRESULT SetTexture(char* filename);
	ObjFileModel* GetModel();
	ID3D11ShaderResourceView* GetTexture();

	void Update();

	XMVECTOR GetBoundingSphereCentre();
	float GetBoundingSphereRadius();
};