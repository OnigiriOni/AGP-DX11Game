#pragma once
#include "gameobject.h"

class Maze
{
private:
	struct HeightMapType
	{
		float x, y, z;
	};

public:
	Maze();

	HRESULT GenerateMazeFromHightMap(char* filename);
};