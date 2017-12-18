#pragma once
#include "component.h"
#include "Transform.h"
#include "model.h"
#include "light.h"
#include "spherecollider.h"

class Game;

class NewGameObject
{
private:
	Game*						game;
	NewGameObject*				parent;
	vector<NewGameObject*>		childrenList;
	
	vector<Component*>			componentList;

public:
	// Variables
	char*						name = "";
	char*						tag = "";
	bool						isEnabled = true;

	Transform*					transform;

	// Methods
	NewGameObject(Game* game);
	NewGameObject(Game* game, char* name);
	NewGameObject(Game* game, char* name, XMVECTOR position);

	void SetParent(NewGameObject* parent);
	void RemoveParent();
	NewGameObject* GetParent();

	void AddChildren(NewGameObject* children);
	bool RemoveChildren(NewGameObject* children);
	NewGameObject* GetChildByName(char* name);
	NewGameObject* GetChildByTag(char* tag);
	NewGameObject* GetChildByIndex(int index);
	vector<NewGameObject*> GetChildren();

	template <class T> T* AddComponent();
	template <class T> bool RemoveComponent();
	template <class T> T* GetComponent();

	void Update(XMMATRIX* world);
};

template<class T>
inline T* NewGameObject::AddComponent()
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

template<class T>
inline T* NewGameObject::GetComponent()
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