#include "game.h"

bool Game::SetHierarchie(NewGameObject* child)
{
	if (SetHierarchie(NULL, child))
	{
		return true;
	}
	return false;
}

bool Game::SetHierarchie(NewGameObject* parent, NewGameObject* child)
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

Game::Game()
{
}

void Game::AddEntity(NewGameObject* gameObject)
{
	for (NewGameObject* entity : entityList)
	{
		if (entity == gameObject)
		{
			return;
		}
	}
	entityList.push_back(gameObject);
}

bool Game::RemoveEntity(NewGameObject * gameObject)
{
	int i = 0;
	for (NewGameObject* entity : entityList)
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
	for (NewGameObject* gameObject : entityList)
	{
		gameObject->Update(&world);
	}
}