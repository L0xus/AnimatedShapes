// File includes
#include "EntityPrototypeFactory.h"
#include "Entity.h"
#include "Square.h"
#include "Triangle.h"
#include "Circle.h"
#include "Hexagon.h"
#include "LeftRightAnimation.h"
#include "UpDownAnimation.h"
#include "CircularAnimation.h"
#include "BoxAnimation.h"

using namespace pugi;

// Set the static instance to 0
EntityPrototypeFactory* EntityPrototypeFactory::sPrototypeFactory = 0;

EntityPrototypeFactory & EntityPrototypeFactory::Instance()
{
	if (!sPrototypeFactory) {
		sPrototypeFactory = new EntityPrototypeFactory();
	}
	return *sPrototypeFactory;
}

void EntityPrototypeFactory::DestroyInstance()
{
	delete sPrototypeFactory;
	sPrototypeFactory = 0;
}

Entity * EntityPrototypeFactory::GetEntity(std::string _identifier)
{
	std::map<std::string, Entity*>::iterator it = prototypes.find(_identifier);
	if (it == prototypes.end()) {
		std::cerr << "Could not get the prototype" << std::endl;
		return 0;
	}
	return (*it).second->Clone();
}

EntityPrototypeFactory::~EntityPrototypeFactory()
{
	ClearPrototypes();
}

bool EntityPrototypeFactory::ConstructSquareFromFile()
{
	SquareData data;
	XMLReader::Instance().GetSquareData(data);

	Shape* shape = 0;

	// Create the shape from info, while checking for errors
	try {
		shape = new Square(data.sideLength);
	}
	catch (invalid_argument) {
		std::cerr << "Cannot create squre. Invalid arguments." << std::endl;
	}

	// Only create the prototype if the shape is valid
	if (shape) {
		// Create and add the prototype to the map, under the square key
		Entity* entity = ConstructEntity(shape, data.entityInfo);
		prototypes.insert_or_assign("Square", entity);
		return true;
	}
	return false;
}

bool EntityPrototypeFactory::ConstructTriangleFromFile()
{
	TriangleData data;
	XMLReader::Instance().GetTriangleData(data);

	Shape* shape = 0;

	// Create the shape from node info
	try {
		shape = new Triangle(data.width, data.height);
	}
	catch (invalid_argument) {
		std::cerr << "Cannot create triangle. Invalid arguments." << std::endl;
	}

	if (shape) {
		// Create and add the prototype to the map, under the triangle key
		Entity* entity = ConstructEntity(shape, data.entityInfo);
		prototypes.insert_or_assign("Triangle", entity);
		return true;
	}
	return false;
}

bool EntityPrototypeFactory::ConstructCircleFromFile()
{
	CircleData data;
	XMLReader::Instance().GetCircleData(data);

	// Create the shape from node info
	Shape* shape = 0;
	
	try {
		shape = new Circle(data.radius);
	}
	catch (invalid_argument) {
		std::cerr << "Cannot create circle. Invalid arguments." << std::endl;
	}

	if (shape) {
		// Create and add the prototype to the map, under the circle key
		Entity* entity = ConstructEntity(shape, data.entityInfo);
		prototypes.insert(std::pair<std::string, Entity*>("Circle", entity));
		return true;
	}
	return false;
}

bool EntityPrototypeFactory::ConstructHexagonFromFile()
{
	HexagonData data;
	XMLReader::Instance().GetHexagonData(data);

	// Create the shape from node info
	Shape* shape = 0;

	try {
		shape = new Hexagon(data.width, data.height);
	}
	catch (invalid_argument) {
		std::cerr << "Cannot create hexagon. Invalid arguments." << std::endl;
	}

	if (shape) {
		// Create and add the prototype to the map, under the hexagon key
		Entity* entity = ConstructEntity(shape, data.entityInfo);
		prototypes.insert_or_assign("Hexagon", entity);
		return true;
	}
	return false;
}

void EntityPrototypeFactory::ClearPrototypes()
{
	for (auto prototype : prototypes) {
			delete prototype.second;
			prototype.second = 0;
	}
	prototypes.clear();
}

Animation * EntityPrototypeFactory::AnimationFromID(int ID)
{
	Animation* anim = 0;

	switch (ID) {
	case 0: {
		try {
			anim = new LeftRightAnimation(-0.5f, 0.5f, 1);
		}
		catch (invalid_argument) {
			std::cerr << "Invalid animation parameters" << std::endl;
		}
		break;
	}
	case 1: {
		try {
			anim = new UpDownAnimation(-0.5f, 0.5f, (int)1);
		}
		catch (invalid_argument) {
			std::cerr << "Invalid animation parameters" << std::endl;
		}
		break;
	}
	case 2: {
		try {
			anim = new CircularAnimation({ 0.5f, 0.5f }, 1);
		}
		catch (invalid_argument) {
			std::cerr << "Invalid animation parameters" << std::endl;
		}
		break;
	}
	case 3: {
		try {
			anim = new BoxAnimation(-0.5f, 0.5f, -0.5f, 0.5f, 1, 1);
		}
		catch (invalid_argument) {
			std::cerr << "Invalid animation parameters" << std::endl;
		}
		break;
	}
	default: {
		std::cerr << "Could not load the animation" << std::endl;
	}
	}

	return anim;
}

Entity * EntityPrototypeFactory::ConstructEntity(Shape* _shape, EntityData _data)
{
	Entity* entity = new Entity();

	// Set shape colour and add shape to entity
	_shape->SetColour(_data.colour);
	entity->AddShape(_shape);

	// Setup animation and add to entity
	Animation* anim = AnimationFromID(_data.animID);
	if (anim) {
		anim->SetAnimationSpeed(_data.animSpeed);
		entity->AddAnimation(anim);
	}

	// Set the location to the spawn position
	entity->SetLocation(_data.spawnLocation);

	return entity;
}

void EntityPrototypeFactory::LoadPrototypesFromFile()
{
	if (XMLReader::Instance().OpenFile(PROTOTYPE_FILE_PATH)) {
		bool success = false;

		success = ConstructSquareFromFile();
		std::cout << (success ? "Updated square." : "Could not upadate square") << std::endl;

		success = ConstructTriangleFromFile();
		std::cout << (success ? "Updated triangle." : "Could not upadate triangle") << std::endl;

		success = ConstructCircleFromFile();
		std::cout << (success ? "Updated circle." : "Could not upadate circle") << std::endl;

		success = ConstructHexagonFromFile();
		std::cout << (success ? "Updated hexagon." : "Could not upadate hexagon") << std::endl;
	}

	//// Load the XML file
	//xml_document prototypeDoc;
	//xml_parse_result result = prototypeDoc.load_file(PROTOTYPE_FILE_PATH);
	//if (result.status != status_ok) {
	//	// Print debug message
	//	std::cout << "XML [" << PROTOTYPE_FILE_PATH << "] parsed with errors, attr value: [" << prototypeDoc.child("node").attribute("attr").value() << "]\n";
	//	std::cout << "Error description: " << result.description() << "\n";
	//	std::cout << "Error offset: " << result.offset << " (error at [..." << (PROTOTYPE_FILE_PATH + result.offset) << "]\n\n";
	//	// Return if the file could not be opened
	//	return;
	//}

	//xml_node prototypeNodes = prototypeDoc.child("prototypes");
	//bool success = false;

	//// Clear current roster of prototypes
	//ClearPrototypes();

	//success = ConstructSquareFromNode(prototypeNodes.child("square"));
	//std::cout << (success ? "Updated square." : "Could not upadate square") << std::endl;
	//success = ConstructTriangleFromNode(prototypeNodes.child("triangle"));
	//std::cout << (success ? "Updated triangle." : "Could not upadate triangle") << std::endl;
	//success = ConstructCircleFromNode(prototypeNodes.child("circle"));
	//std::cout << (success ? "Updated circle." : "Could not upadate circle") << std::endl;
	//success = ConstructHexagonFromNode(prototypeNodes.child("hexagon"));
	//std::cout << (success ? "Updated hexagon." : "Could not upadate hexagon") << std::endl;
}