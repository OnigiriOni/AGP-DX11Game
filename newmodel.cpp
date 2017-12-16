#include "newmodel.h"
#include "newgameobject.h"
#include "renderer.h"

void NewModel::CalculateModelCentre()
{
	float xMin = 0.0f, yMin = 0.0f, zMin = 0.0f;
	float xMax = 0.0f, yMax = 0.0f, zMax = 0.0f;

	for (int i = 0; i < object->numverts; i++)
	{
		// Min-Max for X
		if (object->vertices[i].Pos.x > xMax)
		{
			xMax = object->vertices[i].Pos.x;
		}
		else if (object->vertices[i].Pos.x < xMin)
		{
			xMin = object->vertices[i].Pos.x;
		}
		// Min-Max for Y
		if (object->vertices[i].Pos.y > yMax)
		{
			yMax = object->vertices[i].Pos.y;
		}
		else if (object->vertices[i].Pos.y < yMin)
		{
			yMin = object->vertices[i].Pos.y;
		}
		// Min-Max for Z
		if (object->vertices[i].Pos.z > zMax)
		{
			zMax = object->vertices[i].Pos.z;
		}
		else if (object->vertices[i].Pos.z < zMin)
		{
			zMin = object->vertices[i].Pos.z;
		}
	}

	float x = (xMax + xMin) / 2;
	float y = (yMax + yMin) / 2;
	float z = (zMax + zMin) / 2;

	boundingSpereCentre = XMVectorSet(x, y, z, 0.0f);
}

void NewModel::CalculateBoundingSphereRadius()
{
	float distanceSquared = 0.0f;

	for (int i = 0; i < object->numverts; i++)
	{
		float distance = pow((object->vertices[i].Pos.x - boundingSpereCentre.x), 2) + pow((object->vertices[i].Pos.y - boundingSpereCentre.y), 2) + pow((object->vertices[i].Pos.z - boundingSpereCentre.z), 2);
		if (distance > distanceSquared)
		{
			distanceSquared = distance;
		}
	}
	boundingSphereRadius = sqrt(distanceSquared);
}

NewModel::NewModel(NewGameObject* parentObject)
{
	gameObject = parentObject;
}

HRESULT NewModel::SetModel(char * filename)
{
	Renderer* renderer = Renderer::GetInstance();

	object = new ObjFileModel(filename, renderer->device, renderer->immediateContext);
	
	if (object->filename == "FILE NOT LOADED")
	{
		return S_FALSE;
	}

	CalculateModelCentre();
	CalculateBoundingSphereRadius();

	renderer = nullptr;
	return S_OK;
}

HRESULT NewModel::SetTexture(char* filename)
{
	Renderer* renderer = Renderer::GetInstance();

	if (D3DX11CreateShaderResourceViewFromFile(renderer->device, filename, NULL, NULL, &texture, NULL))
	{
		return S_FALSE;
	}
	
	renderer = nullptr;
	return S_OK;
}

ObjFileModel * NewModel::GetModel()
{
	return object;
}

ID3D11ShaderResourceView * NewModel::GetTexture()
{
	return texture;
}

void NewModel::Update()
{
	Renderer* renderer = Renderer::GetInstance();

	XMMATRIX world = gameObject->transform->GetWorldMatrix();

	renderer->Draw(this, &world);

	renderer = nullptr;
}

XMVECTOR NewModel::GetBoundingSphereWorldSpacePosition(XMMATRIX* objectWorld)
{
	return XMVector3Transform(boundingSpereCentre, *objectWorld);
}

float NewModel::GetBoundingSphereRadius(XMVECTOR objectScale)
{
	float scaleMax = objectScale.x;
	if (objectScale.y > scaleMax)
	{
		scaleMax = objectScale.y;
	}
	if (objectScale.z > scaleMax)
	{
		scaleMax = objectScale.z;
	}
	return boundingSphereRadius * scaleMax;
}