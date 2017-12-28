#pragma once
#include "component.h"
#include "Transform.h"
#include "model.h"
#include "light.h"
#include "spherecollider.h"

class Game;

class GameObject
{
private:
	Game*						game;
	GameObject*					parent;
	vector<GameObject*>			childrenList;
	
	vector<Component*>			componentList;

public:
	// Variables
	char*						name = "";
	char*						tag = "";
	bool						isEnabled = true;

	Transform*					transform;

	// Methods
	GameObject(Game* game);
	GameObject(Game* game, char* name);
	GameObject(Game* game, char* name, XMVECTOR position);

	Game* GetGame();

	void SetParent(GameObject* parent);
	void RemoveParent();
	GameObject* GetParent();

	void AddChildren(GameObject* children);
	bool RemoveChildren(GameObject* children);
	GameObject* GetChildByName(char* name);
	GameObject* GetChildByTag(char* tag);
	GameObject* GetChildByIndex(int index);
	vector<GameObject*> GetChildren();

	template <class T> T* AddComponent();
	template <class T> bool RemoveComponent();
	template <class T> T* GetComponent();

	void Update(XMMATRIX* world);
};

template<class T>
inline T* GameObject::AddComponent()
{
	for (Component* component : componentList)
	{
		if (component == dynamic_cast<T*>(component))
		{
			return NULL;
		}
	}
	componentList.push_back(new T(this));
	return (T*) componentList.back();
}

// TODO: If the component gets removed after storing it outside, it is probably changing values from other objects!
// TODO: Transform should not be removeable.
template<class T>
inline bool GameObject::RemoveComponent()
{
	int i = 0;
	for(Component* component : componentList)
	{
		if (component == dynamic_cast<T*>(component))
		{
			delete componentList[i];
			componentList.erase(componentList.begin() + i);
			return true;
		}
		i++;
	}
	return false;
}

template<class T>
inline T* GameObject::GetComponent()
{
	for(Component* component : componentList)
	{
		if (component == dynamic_cast<T*>(component))
		{
			return (T*) component;
		}
	}
	return NULL;
}