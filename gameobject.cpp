#include "gameobject.h"
#include "game.h"

GameObject::GameObject(Game* game)
{
	GameObject::game = game;
	name = "GameObject";
	componentList.push_back(new Transform(this));
	transform = (Transform*) componentList.back();

	// Set this as child of game
	game->SetHierarchie(NULL, this);
}

GameObject::GameObject(Game* game, char* name)
{
	GameObject::game = game;
	GameObject::name = name;
	componentList.push_back(new Transform(this));
	transform = (Transform*)componentList.back();

	// Set this as child of game
	game->SetHierarchie(NULL, this);
}

GameObject::GameObject(Game * game, XMVECTOR position)
{
	GameObject::game = game;
	name = "GameObject";
	componentList.push_back(new Transform(this, position));
	transform = (Transform*)componentList.back();

	// Set this as child of game
	game->SetHierarchie(NULL, this);
}

GameObject::GameObject(Game* game, char* name, XMVECTOR position)
{
	GameObject::game = game;
	GameObject::name = name;
	componentList.push_back(new Transform(this, position));
	transform = (Transform*)componentList.back();

	// Set this as child of game
	game->SetHierarchie(NULL, this);
}

GameObject::~GameObject()
{
	game->SetHierarchie(NULL, this);
	game->RemoveEntity(this);
	game = nullptr;
	delete game;
	parent = nullptr;
	delete parent;
	for (GameObject* child : childrenList)
	{
		delete child;
	}
	for (Component* component : componentList)
	{
		delete component;
	}
	transform = nullptr;
	delete transform;
}

Game * GameObject::GetGame()
{
	return game;
}

void GameObject::SetParent(GameObject* parent)
{
	GameObject::parent = parent;
}

void GameObject::RemoveParent()
{
	parent = NULL;
}

GameObject* GameObject::GetParent()
{
	return parent;
}

void GameObject::AddChildren(GameObject* children)
{
	childrenList.push_back(children);
}

bool GameObject::RemoveChildren(GameObject* children)
{
	int i = 0;
	for (GameObject* gameObject : childrenList)
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

GameObject* GameObject::GetChildByName(char* name)
{
	for (GameObject* children : childrenList)
	{
		if (children->name == name)
		{
			return children;
		}
	}
}

GameObject* GameObject::GetChildByTag(char* tag)
{
	for (GameObject* children : childrenList)
	{
		if (children->tag == tag)
		{
			return children;
		}
	}
}

GameObject* GameObject::GetChildByIndex(int index)
{
	return childrenList[index];
}

vector<GameObject*> GameObject::GetChildren()
{
	return childrenList;
}

void GameObject::Update(XMMATRIX* world)
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
	for (GameObject* children : childrenList)
	{
		children->Update(&transform->GetWorldMatrix());
	}
}