#include "player.h"
#include "gameobject.h"
#include "inputmanager.h"
#include "maze.h"

Player::Player(GameObject* parentObject)
{
	gameObject = parentObject;
	name = "Player";

	__hook(&SphereCollider::OnCollision, gameObject->GetComponent<SphereCollider>(), &Player::OnCollision);
}

void Player::Update()
{
	if (!isEnabled) return;

	Movement();
}

void Player::Movement()
{
	// Stores the old position of the GameObject for possible collision
	oldPosition = gameObject->transform->position;

	ReadInputStates();

	if (IsKeyPressed(DIK_W))
	{
		gameObject->transform->position += gameObject->transform->forward * moveSpeed;
	}

	if (IsKeyPressed(DIK_S))
	{
		gameObject->transform->position -= gameObject->transform->forward * moveSpeed;
	}

	if (IsKeyPressed(DIK_A))
	{
		gameObject->transform->position -= gameObject->transform->right * moveSpeed;
	}

	if (IsKeyPressed(DIK_D))
	{
		gameObject->transform->position += gameObject->transform->right * moveSpeed;
	}

	if (IsKeyPressed(DIK_E))
	{
		gameObject->transform->RotateNormal(gameObject->transform->up, rotateSpeed);
	}

	if (IsKeyPressed(DIK_Q))
	{
		gameObject->transform->RotateNormal(gameObject->transform->up, -rotateSpeed);
	}
}

void Player::OnCollision(GameObject* thisObject, GameObject* otherObject)
{
	if (otherObject->name == "Key")
	{
		keys++;

		//destroy the key
		
	}
}