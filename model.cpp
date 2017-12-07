#include "model.h"

// Const buffer structs. Pack to 16 bytes. Don't let any single element cross a 16 byte boundary
struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;		// 64 bytes ( 4 x 4 = 16 floats x 4 bytes)
};										// TOTAL SIZE = 64 bytes				
int model_cb_byteWidth = 64;	// The size of the combined buffer bytes. Always update after a const buffer struct change

Model::Model(ID3D11Device* device, ID3D11DeviceContext* context)
{
	m_pD3DDevice = device;
	m_pImmediateContext = context;

	xAngle = 0.0;
	yAngle = 0.0;
	zAngle = 0.0;
	xScale = 1.0;
	yScale = 1.0;
	zScale = 1.0;
	xPos = 0.0;
	yPos = 0.0;
	zPos = 0.0;
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
		Model::LoadShaders();
		Model::CreateConstantBuffer();
		return S_OK;
	}
}

HRESULT Model::LoadShaders()
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

	hr = m_pD3DDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVShader);

	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
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

	hr = m_pD3DDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPShader);

	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);
#pragma endregion

#pragma region InputLayout
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pInputLayout);

	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);
#pragma endregion

	return S_OK;
}

HRESULT Model::CreateConstantBuffer()
{
	HRESULT hr = S_OK;

	// Create constant buffer
	D3D11_BUFFER_DESC constant_buffer_desc;
	ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));
	constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT;	// Can use UpdateSubresource() to update
	constant_buffer_desc.ByteWidth = model_cb_byteWidth;	// MUST be a multiple of 16, calculate from CB struct
	constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;// Useas a constant buffer
	hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc, NULL, &m_pConstantBuffer);

	if (FAILED(hr))	// return error code on failure
	{
		return hr;
	}

	return S_OK;
}

void Model::Draw(XMMATRIX *view, XMMATRIX *projection)
{
	XMMATRIX world;
	world = XMMatrixIdentity();
	world *= XMMatrixScaling(xScale, yScale, zScale);
	world *= XMMatrixRotationX(XMConvertToRadians(xAngle));
	world *= XMMatrixRotationY(XMConvertToRadians(yAngle));
	world *= XMMatrixRotationZ(XMConvertToRadians(zAngle));
	
	world *= XMMatrixTranslation(xPos, yPos, zPos);
	
	// Set the values for the constant buffer
	MODEL_CONSTANT_BUFFER model_cb_values;
	model_cb_values.WorldViewProjection = world * (*view) * (*projection);

	// Upload the values for the constant buffer
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &model_cb_values, 0, 0);

	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);
	
	m_pObject->Draw();
}

void Model::SetPosition(float x, float y, float z)
{
	xPos = x;
	yPos = y;
	zPos = z;
}

void Model::SetRotation(float x, float y, float z)
{
	xAngle = x;
	yAngle = y;
	zAngle = z;
}

void Model::SetScale(float x, float y, float z)
{
	xScale = x;
	yScale = y;
	zScale = z;
}

XMVECTOR Model::GetPosition()
{
	return XMVectorSet(xPos, yPos,  zPos, 0.0);
}

XMVECTOR Model::GetRotation()
{
	return XMVectorSet(xAngle, yAngle, zAngle, 0.0);
}

XMVECTOR Model::GetScale()
{
	return XMVectorSet(xScale, yScale, zScale, 0.0);
}
