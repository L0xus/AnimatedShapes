#pragma once

// File includes
#include "PugiXML/pugixml.hpp"
#include "Utils.h"

using namespace pugi;

struct EntityData {
	vec4 colour;
	int animID;
	float animSpeed;
	vec2 spawnLocation;
};

struct SquareData {
	EntityData entityInfo;
	float sideLength;
};

struct TriangleData {
	EntityData entityInfo;
	float width;
	float height;
};

struct CircleData {
	EntityData entityInfo;
	float radius;
};

struct HexagonData {
	EntityData entityInfo;
	float width;
	float height;
};

class XMLReader
{
public:

	static XMLReader& Instance();
	static void DestroyInstance();

	void GetSquareData(SquareData& _data);
	void GetTriangleData(TriangleData& _data);
	void GetCircleData(CircleData& _data);
	void GetHexagonData(HexagonData& _data);
	void GetEntityData(EntityData& _data, xml_node _node);

	bool OpenFile(const char* _filePath);

protected:

	XMLReader() {};
	~XMLReader() {};

	vec4 GetColourFromNode(pugi::xml_node _colour);

	xml_document currentDocument;

private:

	static XMLReader* sReader;
	

};

