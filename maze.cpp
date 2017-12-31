#include "maze.h"

void Maze::GenerateMaze(MazeStruct* information)
{
	// Wall base
	if (information->y == 0) // 100% Black
	{
		maze.push_back(new GameObject(game, "Wall", XMVectorSet(information->x, 0.0f, information->z, 0.0f)));
		maze.back()->AddComponent<Model>()->SetModel("assets/wall_base.obj");
		maze.back()->GetComponent<Model>()->SetTexture("assets/wall_base.bmp");
	}
	// Wall gate
	if (information->y == 36) // 100% Red
	{
		gate = new GameObject(game, "Gate", XMVectorSet(information->x, 0.0f, information->z, 0.0f));
		gate->AddComponent<Model>()->SetModel("assets/wall_gate.obj");
		gate->GetComponent<Model>()->SetTexture("assets/wall_gate.bmp");
	}
	// Key
	if (information->y == 127) // 50% Grey
	{
		keys.push_back(new GameObject(game, "Key", XMVectorSet(information->x, 5.0f, information->z, 0.0f)));
		keys.back()->AddComponent<Model>()->SetModel("assets/key.obj");
		keys.back()->GetComponent<Model>()->SetTexture("assets/key.bmp");
	}
	// Guardian
	if (information->y == 201) // 100% pink
	{
		guardians.push_back(new GameObject(game, "Guardian", XMVectorSet(information->x, 15.0f, information->z, 0.0f)));
		guardians.back()->AddComponent<Model>()->SetModel("assets/guardian.obj");
		guardians.back()->GetComponent<Model>()->SetTexture("assets/guardian.bmp");
	}
	// Player spawn
	if (information->y == 14) // 50% orange
	{
		playerSpawn = new GameObject(game, "PlayerSpawn", XMVectorSet(information->x, 0.0f, information->z, 0.0f));
	}
}

Maze::Maze(Game* game)
{
	Maze::game = game;
}

HRESULT Maze::GenerateMazeFromHightMap(char* filename)
{
	FILE* file;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	int imageSize, index;
	unsigned char* image;
	unsigned char depth;
	int width, height;


	// Open the height map file in binary.
	fopen_s(&file, filename, "rb");

	// Read in the file header.
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);

	// Read in the bitmap info header.
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

	// Save the dimensions of the terrain.
	width = infoHeader.biWidth;
	height = infoHeader.biHeight;

	// Calculate the size of the bitmap image data.
	imageSize = width * height * 3;

	// Allocate memory for the bitmap image data.
	image = new unsigned char[imageSize];
	if (!image)
	{
		return false;
	}

	// Move to the beginning of the bitmap data.
	fseek(file, fileHeader.bfOffBits, SEEK_SET);

	// Read in the bitmap image data.
	fread(image, 1, imageSize, file);

	// Close the file.
	fclose(file);

	// Create the structure to hold the height map data.
	MazeStruct* mazeStruct = new MazeStruct;

	// Initialize the position in the image data buffer.
	int k = 0;

	// Read the image data into the struct.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			depth = image[k];

			index = (height * i) + j;

			mazeStruct->x = (float) j * 39.3f;
			mazeStruct->y = (float) depth;
			mazeStruct->z = (float) i * 39.3f;

			GenerateMaze(mazeStruct);

			k += 3;
		}
	}

	// Release the bitmap image data.
	delete[] image;
	image = 0;
}

vector<GameObject*> Maze::GetMaze()
{
	return maze;
}

vector<GameObject*> Maze::GetKeys()
{
	return keys;
}

vector<GameObject*> Maze::GetGuardians()
{
	return guardians;
}

GameObject * Maze::GetGate()
{
	return gate;
}

GameObject * Maze::GetSpawn()
{
	return playerSpawn;
}
