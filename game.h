#pragma once
#include "newgameobject.h"
class Game
{
private:
	vector<NewGameObject*>		entities;

public:
	Game();

	void AddEntity(NewGameObject* gameObject);
	//bool RemoveEntity(NewGameObject* gameObject);

	void Update();
};