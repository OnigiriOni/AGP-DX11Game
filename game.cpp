#include "game.h"

Game::Game()
{
}

void Game::AddEntity(NewGameObject* gameObject)
{
	entities.push_back(gameObject);
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
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->isEnabled)
		{
			entities[i]->Update();
		}
	}
}
