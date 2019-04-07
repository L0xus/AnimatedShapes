#pragma once

// Library includes
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

// File includes
#include "Utils.h"

using namespace glm;

// Interface for all shape objects
class Shape
{
public:

	Shape() {};
	virtual ~Shape() = 0 {};

	virtual void Draw(GLuint _program);
	virtual Shape* Clone() = 0;
	
	void SetLocation(vec2 _newLocation);
	vec2 GetLocation() const {
		return location;
	}
	void SetScale(vec2 _newScale);
	vec2 GetScale() const {
		return scale;
	}
	void SetRotation(float _newRotation);
	float GetRotation() const {
		return rotation;
	}
	void SetColour(vec4 _newColour);
	vec4 GetColour() const {
		return colour;
	}

protected:

	virtual void SetupBuffers();

	vec2 location;
	float rotation;
	vec2 scale;
	vec4 colour;

	std::vector<Vertex> vertices;
	vector<GLuint> indices;

	GLuint vao, vbo, ebo;

};

