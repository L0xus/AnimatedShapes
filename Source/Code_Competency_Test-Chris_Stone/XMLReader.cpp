// File includes
#include "XMLReader.h"

XMLReader* XMLReader::sReader = 0;

XMLReader & XMLReader::Instance()
{
	if (!sReader) {
		sReader = new XMLReader();
	}
	return *sReader;
}

void XMLReader::DestroyInstance()
{
	delete sReader;
	sReader = 0;
}

void XMLReader::GetSquareData(SquareData & _data)
{
	// Find the square node
	xml_node squareNode = currentDocument.child("prototypes").child("square");

	// Get the shape dependant information
	_data.sideLength = (float)std::atof(squareNode.child("sideLength").child_value());

	// Get the general entity information
	GetEntityData(_data.entityInfo, squareNode);
}

void XMLReader::GetTriangleData(TriangleData & _data)
{
	// Find the square node
	xml_node triangleNode = currentDocument.child("prototypes").child("triangle");

	// Get the shape dependant information
	_data.width = (float)std::atof(triangleNode.child("width").child_value());
	_data.height = (float)std::atof(triangleNode.child("height").child_value());

	// Get the general entity information
	GetEntityData(_data.entityInfo, triangleNode);
}

void XMLReader::GetCircleData(CircleData & _data)
{
	// Find the square node
	xml_node circleNode = currentDocument.child("prototypes").child("circle");

	// Get the shape dependant information
	_data.radius = (float)std::atof(circleNode.child("radius").child_value());

	// Get the general entity information
	GetEntityData(_data.entityInfo, circleNode);
}

void XMLReader::GetHexagonData(HexagonData & _data)
{
	// Find the square node
	xml_node hexagonNode = currentDocument.child("prototypes").child("hexagon");

	// Get the shape dependant information
	_data.width = (float)std::atof(hexagonNode.child("width").child_value());
	_data.height = (float)std::atof(hexagonNode.child("height").child_value());

	// Get the general entity information
	GetEntityData(_data.entityInfo, hexagonNode);
}

void XMLReader::GetEntityData(EntityData & _data, xml_node _node)
{
	// Get the shape colour
	_data.colour = GetColourFromNode(_node.child("colour"));

	// Get the animation information
	xml_node animation = _node.child("animation");
	_data.animID = std::atoi(animation.child("ID").child_value());
	_data.animSpeed = (float)std::atof(animation.child("speed").child_value());

	// Get the spawn point
	xml_node spawnPoint = _node.child("spawnPoint");
	_data.spawnLocation.x = (float)std::atof(spawnPoint.child("x").child_value());
	_data.spawnLocation.y = (float)std::atof(spawnPoint.child("y").child_value());
}

vec4 XMLReader::GetColourFromNode(xml_node _colour)
{
	float r, g, b, a;
	// Find and cast the r, g, b, and a values of the colour
	r = (float)std::atof(_colour.child("r").child_value());
	g = (float)std::atof(_colour.child("g").child_value());
	b = (float)std::atof(_colour.child("b").child_value());
	a = (float)std::atof(_colour.child("a").child_value());
	return { r, g, b, a };
}

bool XMLReader::OpenFile(const char * _filePath)
{
	// Open the specified file
	xml_parse_result result = currentDocument.load_file(_filePath);
	if (result.status != status_ok) {
		// Print debug message
		std::cout << "XML [" << _filePath << "] parsed with errors, attr value: [" << currentDocument.child("node").attribute("attr").value() << "]\n";
		std::cout << "Error description: " << result.description() << "\n";
		std::cout << "Error offset: " << result.offset << " (error at [..." << (_filePath + result.offset) << "]\n\n";
		return false;
	}
	return true;
}