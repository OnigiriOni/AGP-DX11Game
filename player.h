#pragma once

#include "inputmanager.h"
#include "camera.h"
#include "gameobject.h"

class Player : public GameObject
{
private:
	Camera*				p_pCamera;

public:
	Player();

	void SetCamera(Camera* camera);

	void Update();

	void Movement();
};