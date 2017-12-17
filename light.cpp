#include "light.h"
#include "renderer.h"

Light::Light(NewGameObject* parentObject)
{
	gameObject = parentObject;
	name = "Light";
	
	directionalLightVector = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	directionalLightColour = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	ambientLightColour = XMVectorSet(0.1f, 0.1f, 0.1f, 1.0f);

	Renderer::GetInstance()->AddLight(this);
}

void Light::Update()
{
}
