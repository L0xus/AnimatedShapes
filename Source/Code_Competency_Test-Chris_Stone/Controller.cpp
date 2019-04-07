// File includes
#include "Controller.h"
#include "Canvas.h"
#include "EntityPrototypeFactory.h"

unsigned int Controller::numControllers = 0;

Controller::Controller()
{
	// If there are no controllers, this becomes controller 0, etc.
	controllerID = numControllers;

	// Increment the number of controllers when a new one is spawned
	numControllers++;

	// Set the controls for the first controller
	switch (controllerID) {
	case 0: {
		spawnKey1 = GLFW_KEY_1;
		spawnKey2 = GLFW_KEY_2;
		spawnKey3 = GLFW_KEY_3;
		spawnKey4 = GLFW_KEY_4;
		clearKey = GLFW_KEY_C;
		updateKey = GLFW_KEY_U;
		break;
	}
	default: break;
	}
}

Controller::~Controller()
{
	// Decrement the number of controllers when one is destroyed
	numControllers--;
}

void Controller::HandleInput(int key, int action)
{
	// If the user pressed a key down
	if (action == GLFW_PRESS) {
		// Check key value vs our key bindings
		if (key == spawnKey1) {
			GameInstance::Instance().SpawnEntity("Square");
		}
		else if (key == spawnKey2) {
			GameInstance::Instance().SpawnEntity("Triangle");
		}
		else if (key == spawnKey3) {
			GameInstance::Instance().SpawnEntity("Circle");
		}
		else if (key == spawnKey4) {
			GameInstance::Instance().SpawnEntity("Hexagon");
		}
		else if (key == clearKey) {
			GameInstance::Instance().ClearEntities();
		}
		else if (key == updateKey) {
			EntityPrototypeFactory::Instance().LoadPrototypesFromFile();
		}
	}
}