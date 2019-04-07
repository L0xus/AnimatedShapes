#pragma once

// File includes
#include "Entity.h"
#include "Controller.h"

// Definitions
#define VERT_SHADER_PATH "Assets/Shaders/Vertex.glsl"
#define FRAG_SHADER_PATH "Assets/Shaders/Fragment.glsl"

// Singleton class, representing the canvas
class GameInstance
{
public:

	static GameInstance& Instance();	// Access point to the singlton instance
	static void DestroyInstance();

	static void KeyCallback(GLFWwindow* window, int _key, int _scanCode, int _action, int _mods);
	std::vector<Controller*> GetControllers() const {
		return controllers;
	}

	void SpawnEntity(std::string _identifier);
	void ClearEntities();
	void Update(double _delta);
	void Draw(GLFWwindow* window);

	virtual void SetupProgram();

protected:

	GameInstance();
	~GameInstance();

	GLuint program;
	std::vector<Entity*> entities;
	std::vector<Controller*> controllers; // Can handle multiple controllers
	
private:

	static GameInstance* sCanvas;	// Static instance variable

};

