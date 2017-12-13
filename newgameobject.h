#pragma once
#include "component.h"
#include "Transform.h"
#include "newmodel.h"

class NewGameObject
{
private:
	ID3D11Device*				g_pD3DDevice;
	ID3D11DeviceContext*		g_pImmediateContext;

	NewGameObject*				parent = NULL;
	vector<NewGameObject*>		childrenList;
	
	vector<Component*>			componentList;

public:
	// Variables
	char*						name = "";
	char*						tag = "";
	bool						isEnabled = true;

	// Methods
	NewGameObject();
	NewGameObject(char* name);
	NewGameObject(char* name, XMVECTOR position);

	//void AddParent(NewGameObject* parent);
	//bool RemoveParent(NewGameObject* parent);
	//NewGameObject* GetParent();

	//void AddChildren(NewGameObject* childrenList);
	//bool RemoveChildren(NewGameObject* childrenList);
	//NewGameObject* GetChildByName();
	//NewGameObject* GetChildByTag();
	//NewGameObject* GetChildByIndex();
	//vector<NewGameObject*> GetChildren();

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

	/*for (int i = 0; i < componentList.size(); i++)
	{
		if (componentList[i] == Component)
		{
			return false;
		}
	}

	componentList.push_back(new T());
	return true;*/
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

	/*for (int i = 0; i < componentList.size(); i++)
	{
		if (componentList[i] == Component)
		{
			componentList.erase(entities.begin() + i);
			return true;
		}
	}
	return false;*/
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
