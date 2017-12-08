#pragma once
#include <d3d11.h>
#include <math.h>

#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

class Camera
{
private:
	float x, y ,z;
	float dx, dz;
	float rotation;
	XMVECTOR position;
	XMVECTOR lookat;
	XMVECTOR up;
	XMMATRIX view;

public:
	Camera();
	Camera(XMVECTOR position);
	Camera(XMVECTOR position, float rotation);
	Camera(float x, float y, float z, float rotation);
	~Camera();
	void Rotate(float degree);
	void Forward(float distance);
	void Up(float distance);
	XMMATRIX CalculateViewMatrix();
	XMVECTOR GetPosition();
};