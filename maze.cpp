#include "maze.h"

Maze::Maze()
{
}

HRESULT Maze::GenerateMazeFromHightMap(char* filename)
{
	HRESULT hr = S_OK;

	FILE* file;
	BITMAPINFOHEADER infoHeader;
	BITMAPFILEHEADER fileHeader;
	int width, depth, height;
	int size;
	unsigned char* image;

	hr = fopen_s(&file, filename, "rb");
	if (FAILED(hr)) return hr;

	fread(&fileHeader, sizeof(fileHeader), 1, file);
	fread(&infoHeader, sizeof(infoHeader), 1, file);

	width = infoHeader.biWidth;
	height = infoHeader.biHeight;

	size = width * height * 3;

	image = new unsigned char[size];

	fseek(file, fileHeader.bfOffBits, SEEK_SET);

	fread(image, 1, size, file);

	fclose(file);


	// Create the array
	HeightMapType* heightMap = new HeightMapType[width * height];

	int o = 0;
	int index;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			depth = image[o];
			index = (height * i) + j;
			heightMap[index].x = (float) j;
			heightMap[index].y = (float) depth;
			heightMap[index].z = (float) i;

			o += 3;
		}
	}

	delete[] image;
}
