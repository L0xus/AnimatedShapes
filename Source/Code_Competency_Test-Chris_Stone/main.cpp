// Library includes
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Windows.h>

// CRT for catching memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// File includes
#include "Utils.h"
#include "EntityPrototypeFactory.h"
#include "Canvas.h"

// Use macro to get data on memory leaks in debug mode
#ifdef _DEBUG
#define CRT() {_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG); }
#else
#define CRT() {}
#endif

int main(void) {
	CRT();

	// Exit if the program can't initialize glfw
	if (!glfwInit()) { exit(EXIT_FAILURE); }

	// Create a 600x600 window and make it the current context
	GLFWwindow* window = glfwCreateWindow(600, 600, "Code Competency Test - Chris Stone", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Exit if the program can't initialize glew
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }

	// Swap buffers once every screen update
	glfwSwapInterval(1);

	GameInstance::Instance().SetupProgram();

	double currentTime = 0.0f;
	double previousTime = glfwGetTime();
	double deltaTime = 0.0f;

	// Main program loop
	while (!glfwWindowShouldClose(window)) {
		// Get delta time since last frame
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// Call the display and update of the canvas
		GameInstance::Instance().Draw(window);
		GameInstance::Instance().Update(deltaTime);
		glfwPollEvents();
	}

	// Clean up and exit
	GameInstance::DestroyInstance();
	EntityPrototypeFactory::DestroyInstance();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}