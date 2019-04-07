// File includes
#include "Hexagon.h"

Hexagon::Hexagon(float _width, float _height, vec2 _offset)
{
	// Make sure width and height are not negative or zero
	if (_width <= 0.0 || _height <= 0.0) throw invalid_argument{ "Radius must be more than 0.0" };

	// Load the vertices and indices, then construct OpenGL objects
	Utils::GetPolygonVertices(_width, _height, 6, _offset, vertices, indices);
	SetupBuffers();

	// Assign variables
	width = _width;
	height = _height;
}

Hexagon::Hexagon(const Hexagon & _copy)
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