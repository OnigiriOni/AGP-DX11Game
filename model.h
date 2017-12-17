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
	Model(NewGameObject* parentObject);

	HRESULT SetModel(char* filename);
	HRESULT SetTexture(char* filename);
	ObjFileModel* GetModel();
	ID3D11ShaderResourceView* GetTexture();

	void Update();

	XMVECTOR GetBoundingSphereWorldSpacePosition(XMMATRIX* objectWorld);
	float GetBoundingSphereRadius(XMVECTOR objectScale);
};