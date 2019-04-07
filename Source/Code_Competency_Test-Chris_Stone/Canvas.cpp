// File includes
#include "Canvas.h"
#include "Utils.h"
#include "Square.h"
#include "EntityPrototypeFactory.h"

// Set the static instance to 0
GameInstance* GameInstance::sCanvas = 0;

GameInstance::GameInstance()
{
	// Load prototypes from file
	EntityPrototypeFactory::Instance().LoadPrototypesFromFile();

	// Add a new controller
	controllers.push_back(new Controller());

	// Set the callback key to the canvas KeyCallback function
	glfwSetKeyCallback(glfwGetCurrentContext(), GameInstance::KeyCallback);
}

GameInstance::~GameInstance()
{
	// Clean up all entities
	ClearEntities();

	// Delete all controllers
	for (auto controller : controllers) {
		delete controller;
		controller = 0;
	}
	controllers.clear();
}

void GameInstance::SetupProgram()
{
	// Read the source for the vertex and fragment shaders
	string vSource = Utils::ReadShaderSource(VERT_SHADER_PATH);
	string fSource = Utils::ReadShaderSource(FRAG_SHADER_PATH);

	// Convert to char array so we don't have to input string size manually
	const char* vshaderSource = vSource.c_str();
	const char* fshaderSource = fSource.c_str();

	// Create the shader objects
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Assign the shader source code to the shader objects
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);

	// Compile vertex shader and test for errors
	GLint vertCompiled = 0;
	glCompileShader(vShader);
	Utils::CheckOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled == GL_FALSE) {
		cout << "Vertex Compilation Failed! \n";
		Utils::PrintShaderLog(vShader);
	}

	// Compile fragement shader and test for errors
	GLint fragCompiled = 0;
	glCompileShader(fShader);
	Utils::CheckOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled == GL_FALSE) {
		cout << "Fragment Compilation Failed! \n";
		Utils::PrintShaderLog(fShader);
	}

	// Create and link program and test for errors
	program = glCreateProgram();
	GLint linked = 0;
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);
	Utils::CheckOpenGLError();
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		cout << "Linking Failed!\n";
		Utils::PrintProgramLog(program);
	}
}

GameInstance& GameInstance::Instance()
{
	// Lazy initialization of instance
	if (!sCanvas) {
		sCanvas = new GameInstance();
	}
	return *sCanvas;
}

void GameInstance::DestroyInstance()
{
	delete sCanvas;
	sCanvas = 0;
}

void GameInstance::KeyCallback(GLFWwindow * window, int _key, int _scanCode, int _action, int _mods)
{
	// Get rid of 'unreferenced parameter warning' - unecessary, but clean builds are nice
	window;
	_scanCode;
	_mods;

	// Handle input for all controllers
	for (auto controller : GameInstance::Instance().GetControllers()) {
		controller->HandleInput(_key, _action);
	}
}

void GameInstance::SpawnEntity(std::string _identifier)
{
	// Get the entity from the prototype factory
	Entity* entity = EntityPrototypeFactory::Instance().GetEntity(_identifier);

	// If the entity is valid
	if (entity) {
		// Try to play the animation
		try {
			entity->PlayAnimation(0);
		}
		catch (out_of_range) {
			// Print warning if animation couldn't be played
			std::cerr << "Could not play animation" << std::endl;
		}

		// Add new entity to the vector
		entities.push_back(entity);
	}
}

void GameInstance::ClearEntities()
{
	// Delete all entities and clear vector
	for (auto entity : entities) {
		delete entity;
		entity = 0;
	}
	entities.clear();
}

void GameInstance::Update(double _delta)
{
	// Update each entity
	for (auto entity : entities) {
		entity->Update(_delta);
	}
}

void GameInstance::Draw(GLFWwindow* window)
{
	// Clear the colour and depth buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw each entity
	for (auto entity : entities) {
		entity->Draw(program);
	}

	// Swap buffers
	glfwSwapBuffers(window);
}