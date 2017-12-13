#include "game.h"

Game::Game()
{
}

bool Game::AddEntity(NewGameObject* gameObject)
{
	for (NewGameObject* entity : entityList)
	{
		if (entity == gameObject)
		{
			return false;
		}
	}
	entityList.push_back(gameObject);
	return true;
}

bool Game::RemoveEntity(NewGameObject * gameObject)
{
	int i = 0;
	for (NewGameObject* entity : entityList)
	{
		if (entity == gameObject)
		{
			entityList.erase(entityList.begin() + i);
		}
		// Removes the gameObject regardless of hierarchie
		if (entity->RemoveChildren(gameObject)) return true; // bad performance
		i++;
	}
}

//bool Game::RemoveEntity(NewGameObject* gameObject)
//{
//	for (int i = 0; i < entities.size(); i++)
//	{
//		if (gameObject == entities[i])
//		{
//			entities.erase(entities.begin() + i);
//			return true;
//		}
//		if (entities[i]->RemoveChildren(gameObject) == true) return true;
//	}
//	return false;
//}

void Game::Update()
{
	// Update for all enabled gameObjects
	for (NewGameObject* gameObject : entityList)
	{
		if (gameObject->isEnabled)
		{
			gameObject->Update();
		}
	}
}
