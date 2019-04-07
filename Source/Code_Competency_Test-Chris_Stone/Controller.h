#pragma once

// File includes
#include "Utils.h"

class Controller
{
public:

	Controller();
	~Controller();

	virtual void HandleInput(int key, int action);

	unsigned int GetID() const {
		return controllerID;
	}

private:

	unsigned int controllerID;
	static unsigned int numControllers;

	int spawnKey1;
	int spawnKey2;
	int spawnKey3;
	int spawnKey4;
	int clearKey;
	int updateKey;

};

