#include "game.h"

bool Game::SetHierarchie(GameObject* child)
{
	if (SetHierarchie(NULL, child))
	{
		return true;
	}
	return false;
}

bool Game::SetHierarchie(GameObject* parent, GameObject* child)
{
	if (parent == NULL)					// -> Set child to game
	{
		if (child->GetParent() != NULL)		// -> Is child of an object
		{
			child->GetParent()->RemoveChildren(child);
			AddEntity(child);
			child->RemoveParent();
			return true;
		}
		else								// -> Initial set (protected)
		{
			AddEntity(child);
			return true;
		}
	}
	else								// -> Set child to parent
	{
		if (child->GetParent() == NULL)		// Parent is currently game
		{
			RemoveEntity(child);
			parent->AddChildren(child);
			child->SetParent(parent);
			return true;
		}
		else								// Parent is currently another object
		{
			if (child->GetParent() != parent)	// Parent is not current parent
			{
				child->GetParent()->RemoveChildren(child);
				parent->AddChildren(child);
				child->SetParent(parent);
				return true;
			}
		}
	}
	return false;
}

int Game::GetUpdates()
{
	return updates;
}

Game::Game()
{
	updates = 0;
}

vector<GameObject*> Game::GetEntities()
{
	return entityList;
}

void Game::AddEntity(GameObject* gameObject)
{
	for (GameObject* entity : entityList)
	{
		if (entity == gameObject)
		{
			return;
		}
	}
	entityList.push_back(gameObject);
}

bool Game::RemoveEntity(GameObject * gameObject)
{
	int i = 0;
	for (GameObject* entity : entityList)
	{
		if (entity == gameObject)
		{
			entityList.erase(entityList.begin() + i);
			return true;
		}
		i++;
	}
	return false;
}

void Game::Update()
{
	if (!isEnabled) return;

	// Update for all enabled gameObjects
	for (GameObject* gameObject : entityList)
	{
		gameObject->Update(&world);
	}
	updates = 1;
}