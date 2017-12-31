#include "renderer.h"

Renderer* Renderer::instance = nullptr;

Renderer* Renderer::GetInstance()
{
	if (!instance)
	{
		instance = new Renderer();
	}
	return instance;
}

HRESULT Renderer::InitialiseGraphics(ID3D11Device* device, ID3D11DeviceContext* context)
{
	Renderer::device = device;
	immediateContext = context;

	if (FAILED(CreateSampler()))
	{
		return S_FALSE;
	}

	if (FAILED(LoadShaders()))
	{
		return S_FALSE;
	}

	if (FAILED(CreateConstantBuffer()))
	{
		return S_FALSE;
	}

	if (FAILED(CreateRasterizerState()))
	{
		return S_FALSE;
	}

	if (FAILED(CreateDepthStencilState()))
	{
		return S_FALSE;
	}

	return S_OK;
}

void Renderer::AddCamera(Camera* camera)
{
	Renderer::camera = camera;
}

void Renderer::AddLight(Light* light)
{
	Renderer::light = light;
}

Camera * Renderer::GetCamera()
{
	return camera;
}

HRESULT Renderer::LoadShaders()
{
	HRESULT hr = S_OK;
	ID3DBlob *VS, *PS, *error;

#pragma region VShader
	// Load and compile vertex shader - use vs_5_0 to target DX11 hardware only

	hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelVS", "vs_4_0", 0, 0, 0, &VS, &error, 0);

	if (error != 0)
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))
		{
			return hr;
		}
	}

	hr = device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &vertexShader);

	if (FAILED(hr))
	{
		return hr;
	}

	immediateContext->VSSetShader(vertexShader, 0, 0);
#pragma endregion

#pragma region PShader
	// Load and compile pixel shader - use vs_5_0 to target DX11 hardware only

	hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelPS", "ps_4_0", 0, 0, 0, &PS, &error, 0);

	if (error != 0)
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))
		{
			return hr;
		}
	}

	hr = device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pixelShader);

	if (FAILED(hr))
	{
		return hr;
	}

	immediateContext->PSSetShader(pixelShader, 0, 0);
#pragma endregion

#pragma region InputLayout
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = device->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &inputLayout);

	if (FAILED(hr))
	{
		return hr;
	}

	immediateContext->IASetInputLayout(inputLayout);
#pragma endregion

	return S_OK;
}

HRESULT Renderer::CreateConstantBuffer()
{
	HRESULT hr = S_OK;

	// Create constant buffer
	D3D11_BUFFER_DESC constant_buffer_desc;
	ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));
	constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT;	// Can use UpdateSubresource() to update
	constant_buffer_desc.ByteWidth = model_cb_byteWidth;	// MUST be a multiple of 16, calculate from CB struct
	constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// Useas a constant buffer
	hr = device->CreateBuffer(&constant_buffer_desc, NULL, &constantBuffer);

	if (FAILED(hr))	// return error code on failure
	{
		return hr;
	}

	return S_OK;
}

HRESULT Renderer::CreateSampler()
{
	HRESULT hr = S_OK;

	// Create the sampler desc
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&sampler_desc, &sampler);

	if (FAILED(hr))	// return error code on failure
	{
		return hr;
	}

	return S_OK;
}

HRESULT Renderer::CreateRasterizerState()
{
	HRESULT hr = S_OK;

	D3D11_RASTERIZER_DESC rasterizer_desc;
	ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));
	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_BACK;

	hr = device->CreateRasterizerState(&rasterizer_desc, &rasterSolid);
	if (FAILED(hr)) return hr;

	rasterizer_desc.CullMode = D3D11_CULL_FRONT;

	hr = device->CreateRasterizerState(&rasterizer_desc, &rasterSkyBox);
	if (FAILED(hr)) return hr;

	return S_OK;
}

HRESULT Renderer::CreateDepthStencilState()
{
	HRESULT hr = S_OK;

	D3D11_DEPTH_STENCIL_DESC depthStencil_desc;
	ZeroMemory(&depthStencil_desc, sizeof(depthStencil_desc));
	depthStencil_desc.DepthEnable = true;
	depthStencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencil_desc.StencilEnable = false;

	hr = device->CreateDepthStencilState(&depthStencil_desc, &depthWriteSolid);
	if (FAILED(hr)) return hr;

	depthStencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	hr = device->CreateDepthStencilState(&depthStencil_desc, &depthWriteSkyBox);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void Renderer::Draw(Model* model, XMMATRIX* world)
{
	ID3D11ShaderResourceView* texture = model->GetTexture();

	XMMATRIX view = camera->GetViewMatrix();
	XMMATRIX projection = camera->GetProjectionMatrix();

	XMMATRIX transpose;
	transpose = XMMatrixTranspose(*world);

	// Set the values for the constant buffer
	MODEL_CONSTANT_BUFFER model_cb_values;
	model_cb_values.directionalLightVector = XMVector3Transform( light->directionalLightVector, transpose);
	model_cb_values.directionalLightVector = XMVector3Normalize(model_cb_values.directionalLightVector);
	model_cb_values.directionalLightColour = light->directionalLightColour;
	model_cb_values.ambientLightColour = light->ambientLightColour;
	model_cb_values.WorldViewProjection = (*world) * (view) * (projection);

	// Upload the values for the constant buffer
	immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	immediateContext->UpdateSubresource(constantBuffer, 0, 0, &model_cb_values, 0, 0);

	immediateContext->PSSetSamplers(0, 1, &sampler);
	immediateContext->PSSetShaderResources(0, 1, &texture);

	model->GetModel()->Draw();
}