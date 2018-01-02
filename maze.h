#pragma once
#include "gameobject.h"

class Maze
{
private:
	Game* game;

	struct MazeStruct
	{
		float x, y, z;
	};

	vector<GameObject*> maze;
	vector<GameObject*> keys;
	vector<GameObject*> guardians;
	GameObject*			gate;
	GameObject*			player;
	
	void GenerateMaze(MazeStruct* information);

public:
	Maze(Game* game);

	HRESULT GenerateMazeFromHightMap(char* filename);

	vector<GameObject*> GetMaze();
	vector<GameObject*> GetKeys();
	vector<GameObject*> GetGuardians();
	GameObject* GetGate();
	GameObject* GetPlayer();

	bool RemoveKey(GameObject* object);
};