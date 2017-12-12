#include "player.h"

Player::Player()
{

}

void Player::SetCamera(Camera* camera)
{
	p_pCamera = camera;
}

void Player::Update()
{
	Movement();
}

void Player::Movement()
{
	ReadInputStates();
	if (IsKeyPressed(DIK_W))
	{
		MoveForward(0.001f);
	}

	if (IsKeyPressed(DIK_S))
	{
		MoveForward(-0.001f);
	}

	if (IsKeyPressed(DIK_A))
	{
		MoveRight(-0.001f);
	}

	if (IsKeyPressed(DIK_D))
	{
		MoveRight(0.001f);
	}

	if (IsKeyPressed(DIK_Q))
	{
		Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), -0.005f);
	}

	if (IsKeyPressed(DIK_E))
	{
		Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), 0.005f);
	}
}
