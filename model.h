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

	float x, y, z;
	float xAngle, yAngle, zAngle;
	float scale;

public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT LoadObjModel(char* filename);
	HRESULT LoadAll();
	HRESULT LoadVShader(HRESULT hr, ID3DBlob *VS, ID3DBlob *error);
	HRESULT LoadPShader(HRESULT hr, ID3DBlob *VS, ID3DBlob *error);
	HRESULT CreateInputLayout(HRESULT hr, ID3DBlob *shader);
	int CreateConstantBuffer();
};