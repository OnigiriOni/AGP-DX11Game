#pragma once
//#include "game.h"
#include "component.h"
#include "Transform.h"
#include "newmodel.h"

class Game;
class NewGameObject
{
private:
	Game*						game;
	NewGameObject*				parent = NULL;
	vector<NewGameObject*>		childrenList;
	
	vector<Component*>			componentList;

public:
	// Variables
	char*						name = "";
	char*						tag = "";
	bool						isEnabled = true;

	// Methods
	NewGameObject(Game* game);
	NewGameObject(Game* game, char* name);
	NewGameObject(Game* game, char* name, XMVECTOR position);

	bool AddParent(NewGameObject* parent);
	bool RemoveParent();
	NewGameObject* GetParent();

	bool AddChildren(NewGameObject* children);
	bool RemoveChildren(NewGameObject* children);
	NewGameObject* GetChildByName(char* name);
	NewGameObject* GetChildByTag(char* tag);
	NewGameObject* GetChildByIndex(int index);
	vector<NewGameObject*> GetChildren();

	template <class T> Component* AddComponent();
	template <class T> bool RemoveComponent();
	template <class T> Component* GetComponent();

	void Update();
};

template<class T>
inline Component* NewGameObject::AddComponent()
{
	for (Component* component : componentList)
	{
		if (component == dynamic_cast<T*>(component))
		{
			return NULL;
		}
	}
	componentList.push_back(new T());
	return componentList.back();
}

// TODO: If the component gets removed after storing it outside, it is probably changing values from other objects!
template<class T>
inline bool NewGameObject::RemoveComponent()
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

// TODO: Transform should not be removeable.
template<class T>
inline Component* NewGameObject::GetComponent()
{
	for(Component* component : componentList)
	{
		if (component == dynamic_cast<T*>(component))
		{
			return component;
		}
	}
	return NULL;
}
