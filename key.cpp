#include "key.h"
#include "gameobject.h"

Key::Key(GameObject * parentObject)
{
	gameObject = parentObject;
	name = "Key";
}

void Key::Update()
{
	if (!isEnabled) return;

	Rotate();
}

void Key::Rotate()
{
	gameObject->transform->RotateNormal(gameObject->transform->up, rotateSpeed);
}
