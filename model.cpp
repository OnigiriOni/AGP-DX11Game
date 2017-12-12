#include "model.h"

// Const buffer structs. Pack to 16 bytes. Don't let any single element cross a 16 byte boundary
struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;		// 64 bytes ( 4 x 4 = 16 floats x 4 bytes)
	XMVECTOR directionalLightVector;	// 16 bytes
	XMVECTOR directionalLightColour;	// 16 bytes
	XMVECTOR ambientLightColour;		// 16 bytes
	//XMFLOAT2 packing_bytes;				// 2x4 bytes = 8 bytes
};										// TOTAL SIZE = 112 bytes				
int model_cb_byteWidth = 112;	// The size of the combined buffer bytes. Always update after a const buffer struct change

Model::Model(ID3D11Device* device, ID3D11DeviceContext* context, char* filename)
{
	m_pD3DDevice = device;
	m_pImmediateContext = context;

	LoadObjModel(filename);
}

HRESULT Model::LoadObjModel(char* filename)
{
	m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	if (m_pObject->filename == "FILE NOT LOADED")
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
	
	CalculateModelCentre();
	CalculateBoundingSphereRadius();

	return S_OK;
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

void Model::CalculateModelCentre()
{
	float xMin = 0.0f, yMin = 0.0f, zMin = 0.0f;
	float xMax = 0.0f, yMax = 0.0f, zMax = 0.0f;

	for (int i = 0; i < m_pObject->numverts; i++)
	{
		// Min-Max for X
		if (m_pObject->vertices[i].Pos.x > xMax)
		{
			xMax = m_pObject->vertices[i].Pos.x;
		}
		else if (m_pObject->vertices[i].Pos.x < xMin)
		{
			xMin = m_pObject->vertices[i].Pos.x;
		}
		// Min-Max for Y
		if (m_pObject->vertices[i].Pos.y > yMax)
		{
			yMax = m_pObject->vertices[i].Pos.y;
		}
		else if (m_pObject->vertices[i].Pos.y < yMin)
		{
			yMin = m_pObject->vertices[i].Pos.y;
		}
		// Min-Max for Z
		if (m_pObject->vertices[i].Pos.z > zMax)
		{
			zMax = m_pObject->vertices[i].Pos.z;
		}
		else if (m_pObject->vertices[i].Pos.z < zMin)
		{
			zMin = m_pObject->vertices[i].Pos.z;
		}
	}

	float x = (xMax + xMin) / 2;
	float y = (yMax + yMin) / 2;
	float z = (zMax + zMin) / 2;

	boundingSpereCentre = XMVectorSet(x, y, z, 0.0f);
}

void Model::CalculateBoundingSphereRadius()
{
	float distanceSquared = 0.0f;

	for (int i = 0; i < m_pObject->numverts; i++)
	{
		float distance = pow((m_pObject->vertices[i].Pos.x - boundingSpereCentre.x), 2) + pow((m_pObject->vertices[i].Pos.y - boundingSpereCentre.y), 2) + pow((m_pObject->vertices[i].Pos.z - boundingSpereCentre.z), 2);
		if (distance > distanceSquared)
		{
			distanceSquared = distance;
		}
	}

	boundingSphereRadiusSquared = distanceSquared;
}

void Model::Draw(XMMATRIX* world, XMMATRIX* view, XMMATRIX* projection, Light* light)
{
	XMMATRIX transpose;
	transpose = XMMatrixTranspose(*world);

	// Set the values for the constant buffer
	MODEL_CONSTANT_BUFFER model_cb_values;
	model_cb_values.directionalLightVector = XMVector3Transform(light->GetVector(), transpose);
	model_cb_values.directionalLightVector = XMVector3Normalize(model_cb_values.directionalLightVector);
	model_cb_values.directionalLightColour = light->GetColour();
	model_cb_values.ambientLightColour = light->GetAmbientColour();
	model_cb_values.WorldViewProjection = (*world) * (*view) * (*projection);

	// Upload the values for the constant buffer
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->UpdateSubresource(m_pConstantBuffer, 0, 0, &model_cb_values, 0, 0);

	m_pObject->Draw();
}
/*
XMVECTOR Model::GetBoundingSphereWorldSpacePosition()
{
	XMVECTOR offset = XMVectorSet(boundingSpereCentre.x, boundingSpereCentre.y, boundingSpereCentre.z, 0.0f);

	return XMVector3Transform(offset, *world);
}
*/
/*
float Model::GetBoundingSphereRadius()
{
	float scaleMax = scale.x;
	if (scale.y > scaleMax)
	{
		scaleMax = scale.y;
	}
	if (scale.z > scaleMax)
	{
		scaleMax = scale.z;
	}
	return boundingSphereRadiusSquared * scaleMax;
}
*/
/*
bool Model::CheckCollision(Model* model)
{
	if (model == this)
	{
		return false;
	}

	XMVECTOR thisBoundingSpherePosition = GetBoundingSphereWorldSpacePosition();
	XMVECTOR modelBoundingSpherePosition = model->GetBoundingSphereWorldSpacePosition();

	float distanceSquared = pow((modelBoundingSpherePosition.x - thisBoundingSpherePosition.x), 2) + pow((modelBoundingSpherePosition.y - thisBoundingSpherePosition.y), 2) + pow((modelBoundingSpherePosition.z - thisBoundingSpherePosition.z), 2);

	if (distanceSquared < (model->GetBoundingSphereRadius() + GetBoundingSphereRadius()))
	{
		return true;
	}
	return false;
}
*/