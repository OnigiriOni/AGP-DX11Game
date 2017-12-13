#include "renderer.h"

Renderer & Renderer::GetInstance()
{
	static Renderer instance;
	return instance;
}
