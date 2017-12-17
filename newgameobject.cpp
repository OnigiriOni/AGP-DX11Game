#include "newgameobject.h"
#include "game.h"

NewGameObject::NewGameObject(Game* game)
{
	NewGameObject::game = game;
	name = "GameObject";
	componentList.push_back(new Transform(this));
	transform = (Transform*) componentList.back();

	// Set this as child of game
	game->SetHierarchie(NULL, this);
}

NewGameObject::NewGameObject(Game* game, char* name)
{
	NewGameObject::game = game;
	NewGameObject::name = name;
	componentList.push_back(new Transform(this));
	transform = (Transform*)componentList.back();

	// Set this as child of game
	game->SetHierarchie(NULL, this);
}

NewGameObject::NewGameObject(Game* game, char* name, XMVECTOR position)
{
	NewGameObject::game = game;
	NewGameObject::name = name;
	componentList.push_back(new Transform(this, position));
	transform = (Transform*)componentList.back();

	// Set this as child of game
	game->SetHierarchie(NULL, this);
}

void NewGameObject::SetParent(NewGameObject* parent)
{
	NewGameObject::parent = parent;
}

void NewGameObject::RemoveParent()
{
	parent = NULL;
}

NewGameObject* NewGameObject::GetParent()
{
	return parent;
}

void NewGameObject::AddChildren(NewGameObject* children)
{
	childrenList.push_back(children);
}

bool NewGameObject::RemoveChildren(NewGameObject* children)
{
	int i = 0;
	for (NewGameObject* gameObject : childrenList)
	{
		if (gameObject == children)
		{
			childrenList.erase(childrenList.begin() + i);
			return true;
		}
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

void NewGameObject::Update(XMMATRIX* world)
{
	if (!isEnabled) return;

	// Update for all enabled components
	for (Component* component : componentList)
	{
		if (component->name == "Transform")
		{
			transform->Update();
			transform->SetWorldMatrix(transform->GetWorldMatrix() * (*world));
		}
		else
		{
			component->Update();
		}
	}

	// Update for all enabled children
	for (NewGameObject* children : childrenList)
	{
		children->Update(&transform->GetWorldMatrix());
	}
}