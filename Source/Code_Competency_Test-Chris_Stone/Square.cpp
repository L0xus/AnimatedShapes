// File includes
#include "Square.h"

Square::Square(float _sideLength, vec2 _offset)
{
	// Make sure side length not negative or zero
	if (_sideLength <= 0.0) throw invalid_argument{ "Side length must be more than 0.0" };

	// Load the vertices and indices, then construct OpenGL objects
	Utils::GetSquareVertices(_sideLength, _offset, vertices, indices);
	SetupBuffers();

	// Assign variables
	sideLength = _sideLength;
}

Square::Square(const Square & _copy)
{
	vertices = _copy.vertices;
	indices = _copy.indices;
	colour = _copy.colour;
	location = _copy.location;
	vbo = _copy.vbo;
	vao = _copy.vao;
	ebo = _copy.ebo;
	sideLength = _copy.sideLength;
}