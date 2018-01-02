#include "player.h"
#include "game.h"
#include "gameobject.h"
#include "inputmanager.h"
#include "maze.h"
#include "key.h"

Player::Player(GameObject* parentObject)
{
	gameObject = parentObject;
	name = "Player";

	__hook(&SphereCollider::OnCollision, gameObject->GetComponent<SphereCollider>(), &Player::OnCollision);
}

Player::~Player()
{
	maze = nullptr;
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
	// Rip performance
	if (otherObject->name == "Wall")
	{
		gameObject->transform->position = oldPosition;
	}

	if (otherObject->name == "Guardian")
	{
		//reduce player health - needs a cooldown timer or the player is dead in 0.000001 seconds.
	}

	if (otherObject->name == "Key")
	{
		keys += otherObject->GetComponent<Key>()->charges;

		maze->RemoveKey(otherObject);
		delete otherObject;
	}
}