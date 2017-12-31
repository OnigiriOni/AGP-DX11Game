#pragma once
#include "gameobject.h"

class Game
{
private:
	vector<GameObject*>		entityList;

	XMMATRIX					world = XMMatrixIdentity();

	//TODO: Fix this bad inplementation of an collision error fix in the first frame (every object collides because they are at pos: 0,0,0 (not the object thiat checks the collision) )!
	int							updates;

	void AddEntity(GameObject* gameObject);
	bool RemoveEntity(GameObject* gameObject);

	void PreUpdate();
	void PostUpdate();

public:
	bool						isEnabled = true;

	Game();

	vector<GameObject*> GetEntities();

	bool SetHierarchie(GameObject* child);
	bool SetHierarchie(GameObject* parent, GameObject* child);

	int GetUpdates();

	void Update();

	void Start();
};