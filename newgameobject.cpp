#include "newgameobject.h"

NewGameObject::NewGameObject()
{
	name = "GameObject";
	componentList.push_back(new Transform());
}

NewGameObject::NewGameObject(char * name)
{
	NewGameObject::name = name;
	componentList.push_back(new Transform());
}

NewGameObject::NewGameObject(char * name, XMVECTOR position)
{
	NewGameObject::name = name;
	componentList.push_back(new Transform(position));
}

void NewGameObject::Update()
{
}
