// File includes
#include "Shape.h"

void Shape::SetLocation(vec2 _newLocation)
{
	location = _newLocation;
}

void Shape::SetScale(vec2 _newScale)
{
	scale = _newScale;
}

void Shape::SetRotation(float _newRotation)
{
	rotation = _newRotation;
}

void Shape::SetColour(vec4 _newColour)
{
	colour = _newColour;
}

void Shape::Draw(GLuint _program)
{
	// Make sure to use this shapes vao
	glUseProgram(_program);
	glBindVertexArray(vao);

	// Send location and colour information to the vertex shader
	GLuint locationLoc = glGetUniformLocation(_program, "location");
	glProgramUniform2f(_program, locationLoc, location.x, location.y);
	GLuint colourLoc = glGetUniformLocation(_program, "colour");
	glProgramUniform4f(_program, colourLoc, colour.x, colour.y, colour.z, colour.w);

	// Send the vertices down the pipeline to be drawn
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	// Unbind this shapes vao, so the next shape can bind it's vao
	glBindVertexArray(0);
}

void Shape::SetupBuffers()
{
	// Set up the vertex array and vertex and element buffer objects
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind these objects to our member variables
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Defines how the elements are laid out in the vertex array
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// Unbind this shapes vao
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}