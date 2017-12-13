#pragma once

class Component
{
private:

public:
	virtual void Update();

	bool isEnabled = true;
	
	Component();
};