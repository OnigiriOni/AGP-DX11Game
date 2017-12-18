#pragma once
#include <d3d11.h>
#include <math.h>
#include <stdio.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

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