#include "gate.h"
#include "gameobject.h"
#include "player.h"

Gate::Gate(GameObject* parentObject)
{
	gameObject = parentObject;
	name = "Gate";
	closedPosition = gameObject->transform->position;

	__hook(&SphereCollider::OnCollision, gameObject->GetComponent<SphereCollider>(), &Gate::OnCollision);
}

void Gate::Update()
{
	if (!isEnabled) return;

	if (opening) OpenGate();
}

void Gate::OnCollision(GameObject* thisObject, GameObject* otherObject)
{
	// Tell the player that it requires an amount of keys to open (sadly I don't have text rendering implemented)

	// Open the gate if the player has enough keys
	if (otherObject->name == "Player")
	{
		if (otherObject->GetComponent<Player>()->keys >= requiredKeys)
		{
			if (gameObject->transform->position.x >= closedPosition.x - 39.3f)
			{
				opening = true;
			}
		}
	}
}

void Gate::OpenGate()
{
	gameObject->transform->position -= gameObject->transform->right * openSpeed;

	if (gameObject->transform->position.x <= closedPosition.x - 39.3f)
	{
		opening = false;
	}
}
