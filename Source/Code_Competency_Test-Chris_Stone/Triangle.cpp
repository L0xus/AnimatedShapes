// File includes
#include "Triangle.h"

Triangle::Triangle(float _width, float _height, vec2 _offset)
{
	// Make sure width and height are not negative or zero
	if (_width <= 0.0 || _height <= 0.0) throw invalid_argument{ "Width and height must be more than 0.0" };

	// Load the vertices and indices, then construct OpenGL objects
	Utils::GetTriangleVertices(_width, _height, _offset, vertices, indices);
	SetupBuffers();

	// Assign variables
	width = _width;
	height = _height;
}

Triangle::Triangle(const Triangle & _copy)
{
	vertices = _copy.vertices;
	indices = _copy.indices;
	colour = _copy.colour;
	location = _copy.location;
	vbo = _copy.vbo;
	vao = _copy.vao;
	ebo = _copy.ebo;
	width = _copy.width;
	height = _copy.height;
}