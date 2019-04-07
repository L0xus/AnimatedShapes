#pragma once

// Library includes
#include <map>

// File includes
#include "XMLReader.h"
#include "Utils.h"

// Definitions
#define PROTOTYPE_FILE_PATH "Assets/XML/ShapeDefinitions.xml"

// Forward declarations of required classes
class Entity;
class Shape;
class Animation;

class EntityPrototypeFactory
{
public:

	static EntityPrototypeFactory& Instance();	// Access point to singleton instance
	static void DestroyInstance();

	Entity* GetEntity(std::string _identifier);
	void LoadPrototypesFromFile();

protected:

	EntityPrototypeFactory() {};
	~EntityPrototypeFactory();

	bool ConstructSquareFromFile();
	bool ConstructTriangleFromFile();
	bool ConstructCircleFromFile();
	bool ConstructHexagonFromFile();
	void ClearPrototypes();

	Animation* AnimationFromID(int ID);
	Entity* ConstructEntity(Shape* _shape, EntityData _data);

	std::map<std::string, Entity*> prototypes;	// Using map so that prototypes can be cloned given their name

private:

	static EntityPrototypeFactory* sPrototypeFactory;	// static instance variable

};

