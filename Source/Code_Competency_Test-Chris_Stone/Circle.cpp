// File includes
#include "Circle.h"

#define NUM_CIRCLE_SIDES 64

Circle::Circle(float _radius, vec2 _offset)
{
	// Make sure radius is not negative or zero
	if (_radius <= 0) throw invalid_argument{ "Radius must be more than 0.0" };

	// Load the vertices and indices, then construct OpenGL objects
	/* I use GetPolygonVertices for circles as well, by using the radius for both
	width and height, and having a high number of fixed sides (64 in this case).*/
	Utils::GetPolygonVertices(_radius, _radius, NUM_CIRCLE_SIDES, _offset, vertices, indices);
	SetupBuffers();
	
	// Set variables
	radius = _radius;
}

Circle::Circle(const Circle & _copy)
{
	vertices = _copy.vertices;
	indices = _copy.indices;
	colour = _copy.colour;
	location = _copy.location;
	vbo = _copy.vbo;
	vao = _copy.vao;
	ebo = _copy.ebo;
	radius = _copy.radius;
}