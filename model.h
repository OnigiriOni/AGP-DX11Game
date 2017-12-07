#pragma once
#include "objfilemodel.h"

class Model {
private:
	ID3D11Device*			m_pD3DDevice;
	ID3D11DeviceContext*	m_pImmediateContext;

	ObjFileModel*			m_pObject;
	ID3D11VertexShader*		m_pVShader;
	ID3D11PixelShader*		m_pPShader;
	ID3D11InputLayout*		m_pInputLayout;
	ID3D11Buffer*			m_pConstantBuffer;

	float xAngle;
	float yAngle;
	float zAngle;
	float xScale;
	float yScale;
	float zScale;
	float xPos;
	float yPos;
	float zPos;

public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT LoadObjModel(char* filename);
	HRESULT LoadShaders();
	HRESULT CreateConstantBuffer();
	void Draw(XMMATRIX* view, XMMATRIX* projection);
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	XMVECTOR GetPosition();
	XMVECTOR GetRotation();
	XMVECTOR GetScale();
};