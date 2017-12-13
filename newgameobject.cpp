#include "newgameobject.h"
#include "game.h"

NewGameObject::NewGameObject(Game* game)
{
	NewGameObject::game = game;
	name = "GameObject";
	componentList.push_back(new Transform());
}

NewGameObject::NewGameObject(Game* game, char* name)
{
	NewGameObject::game = game;
	NewGameObject::name = name;
	componentList.push_back(new Transform());
}

NewGameObject::NewGameObject(Game* game, char* name, XMVECTOR position)
{
	NewGameObject::game = game;
	NewGameObject::name = name;
	componentList.push_back(new Transform(position));
}

bool NewGameObject::AddParent(NewGameObject* parent)
{
	if (NewGameObject::parent != parent)
	{
		NewGameObject::parent = parent;
		return true;
	}
	return false;
}

bool NewGameObject::RemoveParent()
{
	if (parent)
	{
		if (game->AddEntity(this))
		{
			parent = NULL;
			return true;
		}
	}
	return false;
}

NewGameObject* NewGameObject::GetParent()
{
	return parent;
}

bool NewGameObject::AddChildren(NewGameObject* children)
{
	for (NewGameObject* gameObject : childrenList)
	{
		if (gameObject == children)
		{
			return false;
		}
	}

	if (children->GetParent() == NULL)
	{
		if (game->RemoveEntity(children))
		{
			if (children->AddParent(this))
			{
				childrenList.push_back(children);
				return true;
			}
		}
	}
	else
	{
		if (children->RemoveParent())
		{
			if (children->AddParent(this))
			{
				childrenList.push_back(children);
				return true;
			}
		}
	}
	return false;
}

bool NewGameObject::RemoveChildren(NewGameObject* children)
{
	int i = 0;
	for (NewGameObject* gameObject : childrenList)
	{
		if (gameObject == children)
		{
			if (children->RemoveParent())
			{
				if (game->AddEntity(children))
				{
					childrenList.erase(childrenList.begin() + i);
					return true;
				}
			}
		}
		// Removes the gameObject regardless of hierarchie from this gameObject
		if (gameObject->RemoveChildren(children)) return true; // bad performance
		i++;
	}
	return false;
}

NewGameObject* NewGameObject::GetChildByName(char* name)
{
	for (NewGameObject* children : childrenList)
	{
		if (children->name == name)
		{
			return children;
		}
	}
}

NewGameObject* NewGameObject::GetChildByTag(char* tag)
{
	for (NewGameObject* children : childrenList)
	{
		if (children->tag == tag)
		{
			return children;
		}
	}
}

NewGameObject* NewGameObject::GetChildByIndex(int index)
{
	return childrenList[index];
}

vector<NewGameObject*> NewGameObject::GetChildren()
{
	return childrenList;
}

void NewGameObject::Update()
{
	// Update for all enabled components
	for (Component* component : componentList)
	{
		if (component->isEnabled)
		{
			component->Update();
		}
	}

	// Update for all enabled children
	for (NewGameObject* children : childrenList)
	{
		if (children->isEnabled)
		{
			children->Update();
		}
	}
}
