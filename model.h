#pragma once
#include "objfilemodel.h"
#include "light.h"

class Model {
private:
	ID3D11Device*			m_pD3DDevice;
	ID3D11DeviceContext*	m_pImmediateContext;

	ObjFileModel*			m_pObject;
	ID3D11VertexShader*		m_pVShader;
	ID3D11PixelShader*		m_pPShader;
	ID3D11InputLayout*		m_pInputLayout;
	ID3D11Buffer*			m_pConstantBuffer;

	XMMATRIX				world;
	// rotation
	float xAngle;
	float yAngle;
	float zAngle;
	// scale
	float xScale;
	float yScale;
	float zScale;
	// position
	float xPos;
	float yPos;
	float zPos;
	// collision
	XMVECTOR boundingSpereCentre;
	float boundingSphereRadiusSquared;

	// Methods
	HRESULT LoadShaders();
	HRESULT CreateConstantBuffer();
	void CalculateModelCentre();
	void CalculateBoundingSphereRadius();
	void CalculateWorldMatrix();

public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT LoadObjModel(char* filename);
	void Draw(XMMATRIX* view, XMMATRIX* projection, Light* light);
	void SetPosition(XMVECTOR position);
	void SetPosition(float x, float y, float z);
	void SetRotation(XMVECTOR rotation);
	void SetRotation(float x, float y, float z);
	void SetScale(XMVECTOR scale);
	void SetScale(float x, float y, float z);
	void Rotate(XMVECTOR axis, float degrees);
	void LookAtXZ(XMVECTOR position);
	XMVECTOR GetBoundingSphereWorldSpacePosition();
	float GetBoundingSphereRadius();
	bool CheckCollision(Model* model);
	XMVECTOR GetPosition();
	XMVECTOR GetRotation();
	XMVECTOR GetScale();
};