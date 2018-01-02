#include "maze.h"
#include "gate.h"
#include "player.h"
#include "key.h"

void Maze::GenerateMaze(MazeStruct* information)
{
	// Wall base
	if (information->y == 0) // 0 blue
	{
		maze.push_back(new GameObject(game, "Wall", XMVectorSet(information->x, 0.0f, information->z, 0.0f)));
		maze.back()->AddComponent<Model>()->SetModel("assets/wall_base.obj");
		maze.back()->GetComponent<Model>()->SetTexture("assets/wall_base.bmp");
		//maze.back()->AddComponent<SphereCollider>(); // too much performance loss
	}
	// Wall gate
	if (information->y == 36) // 36 blue
	{
		gate = new GameObject(game, "Gate", XMVectorSet(information->x, 0.0f, information->z, 0.0f));
		gate->AddComponent<Model>()->SetModel("assets/wall_gate.obj");
		gate->GetComponent<Model>()->SetTexture("assets/wall_gate.bmp");
		gate->AddComponent<SphereCollider>();
		gate->AddComponent<Gate>();
	}
	// Key
	if (information->y == 127) // 127 blue
	{
		keys.push_back(new GameObject(game, "Key", XMVectorSet(information->x, 5.0f, information->z, 0.0f)));
		keys.back()->AddComponent<Model>()->SetModel("assets/key.obj");
		keys.back()->GetComponent<Model>()->SetTexture("assets/key.bmp");
		keys.back()->AddComponent<SphereCollider>();
		keys.back()->AddComponent<Key>();
	}
	// Guardian
	if (information->y == 201) // 201 blue
	{
		guardians.push_back(new GameObject(game, "Guardian", XMVectorSet(information->x, 15.0f, information->z, 0.0f)));
		guardians.back()->AddComponent<Model>()->SetModel("assets/guardian.obj");
		guardians.back()->GetComponent<Model>()->SetTexture("assets/guardian.bmp");
		guardians.back()->AddComponent<SphereCollider>();
	}
	// Player spawn
	if (information->y == 14) // 14 blue
	{
		player = new GameObject(game, "Player", XMVectorSet(information->x, 5.0f, information->z, 0.0f));
		player->transform->rotation = XMVectorSet(0.0f, 90.0f, 0.0f, 0.0f);
		player->AddComponent<Camera>()->clearMode = SKYBOX;
		player->GetComponent<Camera>()->SetSkyBox("assets/cube.obj", "assets/texture.bmp");
		player->AddComponent<SphereCollider>()->isActive = true;
		player->AddComponent<Player>()->maze = this;
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

GameObject * Maze::GetPlayer()
{
	return player;
}

bool Maze::RemoveKey(GameObject* object)
{
	int i = 0;
	for (GameObject* key : keys)
	{
		if (key == object)
		{
			keys.erase(keys.begin() + i);
			return true;
		}
		i++;
	}
	return false;
}
