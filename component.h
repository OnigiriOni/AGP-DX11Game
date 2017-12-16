#pragma once

class NewGameObject;

class Component
{
protected:
	NewGameObject*	gameObject;

public:
	char*			name = "";
	bool			isEnabled = true;

	Component();

	virtual void Update();
};