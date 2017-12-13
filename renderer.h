#pragma once

class Renderer
{
private:
	Renderer() {}
	
public:
	Renderer(Renderer const&) = delete;
	void operator=(Renderer const&) = delete;

	static Renderer& GetInstance();
};