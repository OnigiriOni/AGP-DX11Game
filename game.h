#pragma once
#include "newgameobject.h"

class Game
{
private:
	vector<NewGameObject*>		entityList;

	XMMATRIX					world = XMMatrixIdentity();

public:
	Game();

	bool AddEntity(NewGameObject* gameObject);
	bool RemoveEntity(NewGameObject* gameObject);

	void Update();
};