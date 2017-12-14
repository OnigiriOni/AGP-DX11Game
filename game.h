#pragma once
#include "newgameobject.h"

class Game
{
private:
	vector<NewGameObject*>		entityList;

	XMMATRIX					world = XMMatrixIdentity();

	bool						isEnabled = true;

	void AddEntity(NewGameObject* gameObject);
	bool RemoveEntity(NewGameObject* gameObject);

public:
	Game();

	bool SetHierarchie(NewGameObject* child);
	bool SetHierarchie(NewGameObject* parent, NewGameObject* child);

	void Update();
};