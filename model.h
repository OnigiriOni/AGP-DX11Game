#pragma once
#include "objfilemodel.h"
#include "light.h"

class Model
{
private:
	ID3D11Device*				m_pD3DDevice;
	ID3D11DeviceContext*		m_pImmediateContext;

	ID3D11ShaderResourceView*	g_pTexture0;
	ID3D11SamplerState*			g_pSampler0;

	ObjFileModel*				m_pObject;
	ID3D11VertexShader*			m_pVShader;
	ID3D11PixelShader*			m_pPShader;
	ID3D11InputLayout*			m_pInputLayout;
	ID3D11Buffer*				m_pConstantBuffer;

	XMVECTOR					boundingSpereCentre;
	float						boundingSphereRadius;

	// Methods
	HRESULT LoadObjModel(char* filename);
	HRESULT LoadShaders();
	HRESULT CreateConstantBuffer();
	HRESULT CreateSampler();

	void CalculateModelCentre();
	void CalculateBoundingSphereRadius();

public:
	Model(ID3D11Device* device, ID3D11DeviceContext* context, char* filenameModel);
	Model(ID3D11Device* device, ID3D11DeviceContext* context, char* filenameModel, char* filenameTexture);

	void SetTexture(char* filename);
	void Draw(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection, Light* light);

	XMVECTOR GetBoundingSphereWorldSpacePosition(XMMATRIX* world);
	float GetBoundingSphereRadius(XMVECTOR scale);
	//bool CheckCollision(Model* model);
};