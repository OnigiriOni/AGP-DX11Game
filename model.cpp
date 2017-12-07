#include "model.h"

Model::Model(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_pD3DDevice = device;
	m_pImmediateContext = context;

	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	xAngle = 0.0f;
	yAngle = 0.0f;
	zAngle = 0.0f;
	scale = 1.0f;
}

HRESULT Model::LoadObjModel(char* filename)
{
	m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	if (m_pObject->filename == "FILE NOT LOADED")
	{
		return S_FALSE;
	}
	else
	{
		return S_OK;
	}
}

HRESULT Model::LoadAll()
{
	HRESULT hr = S_OK;
	ID3DBlob *VS, *PS, *error;

	if (FAILED(LoadVShader(hr, VS, error)))
	{
		return S_FALSE;
	}

	if (FAILED(LoadPShader(hr, PS, error)))
	{
		return S_FALSE;
	}

	if (FAILED(CreateInputLayout(hr, VS)))
	{
		return S_FALSE;
	}

	return hr;
}

// Load and compile vertex shader - use vs_5_0 to target DX11 hardware only
HRESULT Model::LoadVShader(HRESULT hr, ID3DBlob *VS, ID3DBlob *error)
{
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

	hr = m_pD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVShader);

	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
}

// Load and compile pixel shader - use vs_5_0 to target DX11 hardware only
HRESULT Model::LoadPShader(HRESULT hr, ID3DBlob *PS, ID3DBlob *error)
{
	hr = D3DX11CompileFromFile("model_shaders.hlsl", 0, 0, "ModelPS", "vs_4_0", 0, 0, 0, &PS, &error, 0);

	if (error != 0)
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))
		{
			return hr;
		}
	}

	hr = m_pD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPShader);
	
	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);
}

HRESULT Model::CreateInputLayout(HRESULT hr, ID3DBlob *Shader)
{
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), Shader->GetBufferPointer(), Shader->GetBufferSize(), &m_pInputLayout);

	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	return S_OK;
}

int Model::CreateConstantBuffer()
{
	return S_OK;
}
