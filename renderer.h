#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#include <stdio.h>
#include <math.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

#include "model.h"
#include "camera.h"
#include "light.h"

class Renderer
{
private:
	static Renderer*			instance;

	ID3D11VertexShader*			vertexShader;
	ID3D11PixelShader*			pixelShader;
	ID3D11InputLayout*			inputLayout;
	ID3D11Buffer*				constantBuffer;
	ID3D11SamplerState*			sampler;

	// Const buffer structs. Pack to 16 bytes. Don't let any single element cross a 16 byte boundary
	struct MODEL_CONSTANT_BUFFER
	{
		XMMATRIX WorldViewProjection;		// 64 bytes ( 4 x 4 = 16 floats x 4 bytes)
		XMVECTOR directionalLightVector;	// 16 bytes
		XMVECTOR directionalLightColour;	// 16 bytes
		XMVECTOR ambientLightColour;		// 16 bytes
		//XMFLOAT2 packingBytes;			// 2x4 bytes = 8 bytes
	};										// TOTAL SIZE = 112 bytes
	int model_cb_byteWidth = 112;		// The size of the combined buffer bytes. Always update after a const buffer struct change

	//TODO: lists of cameras and lights
	Camera* camera;
	Light* light;

	HRESULT LoadShaders();
	HRESULT CreateConstantBuffer();
	HRESULT CreateSampler();
	HRESULT CreateRasterizerState();
	HRESULT CreateDepthStencilState();

	Renderer() {}
	
public:
	ID3D11Device*				device;
	ID3D11DeviceContext*		immediateContext;

	ID3D11RasterizerState*		rasterSolid = 0;
	ID3D11RasterizerState*		rasterSkyBox = 0;
	ID3D11DepthStencilState*	depthWriteSolid = 0;
	ID3D11DepthStencilState*	depthWriteSkyBox = 0;

	static Renderer* GetInstance();

	HRESULT InitialiseGraphics(ID3D11Device* device, ID3D11DeviceContext* context);
	void AddCamera(Camera* camera);
	void AddLight(Light* light);

	void Draw(Model* model, XMMATRIX* world);
};