#pragma once

class NewGameObject;

class Component
{
protected:
	NewGameObject* gameObject;

public:
	bool isEnabled = true;

	Component();

	virtual void Update();
};