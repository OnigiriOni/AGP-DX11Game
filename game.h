#pragma once
#include "newgameobject.h"

class Game
{
private:
	vector<NewGameObject*>		entityList;

	XMMATRIX					world = XMMatrixIdentity();

	//TODO: Fix this bad inplementation of an collision error fix in the first frame (every object collides because they are at pos: 0,0,0 (not the object thiat checks the collision) )!
	int							updates;

	void AddEntity(NewGameObject* gameObject);
	bool RemoveEntity(NewGameObject* gameObject);

public:
	bool						isEnabled = true;

	Game();

	vector<NewGameObject*> GetEntities();

	bool SetHierarchie(NewGameObject* child);
	bool SetHierarchie(NewGameObject* parent, NewGameObject* child);

	int GetUpdates();

	void Update();
};