// Library includes
#include <math.h>

// File includes
#include "Utils.h"

// Checks that an openGL shader was loaded properly
void Utils::PrintShaderLog(GLuint _shader) {
		int len = 0;
		int chWrittn = 0;
		glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &len);
		if (len > 0) {
			// If not, print the debug message
			char* log = new char[len];
			glGetShaderInfoLog(_shader, len, &chWrittn, log);
			cout << "Shader Info Log: " << log << endl;
			delete[] log;
		}
}

// Checks that an openGL proram was loaded properly
void Utils::PrintProgramLog(int _program) {
	int len = 0;
	int chWrittn = 0;
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		// If not, print the debug message
		char* log = new char[len];
		glGetProgramInfoLog(_program, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		delete[] log;
	}
}

// Checks for general openGL errors
bool Utils::CheckOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		// If an error was found, print the debug message
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

// Reads a shader from a file source
std::string Utils::ReadShaderSource(const char * _filePath) {
	string content = "";
	ifstream fileStream(_filePath, ios::in);
	string line = "";
	while (getline(fileStream, line)) {
		content.append(line + "\n");
	}
	fileStream.close();
	// Return the shader in string form
	return content;
}

void Utils::GetSquareVertices(float _sideLength, vec2 _offset, std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices) {
	// Initialize local variables
	Vertex v1, v2, v3, v4;
	float x = _sideLength / 2.0f;
	vec3 offset = { _offset, 0.0 };

	// Set all the vertices
	v1.position = vec3(-x, x, 0.0) + offset;		// Top left
	_vertices.push_back(v1);
	v2.position = vec3(x, x, 0.0) + offset;		// Top right
	_vertices.push_back(v2);
	v3.position = vec3(x, -x, 0.0) + offset;		// Bottom right
	_vertices.push_back(v3);
	v4.position = vec3(-x, -x, 0.0) + offset;	// Bottom left
	_vertices.push_back(v4);

	// Set the indices so that openGL knows how to draw the shape without having to repear vertices
	_indices = { 0, 1, 2,	// First triangle
				2, 3, 0 };	// Second triangle
}

void Utils::GetTriangleVertices(float _width, float _height, vec2 _offset, std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices) {
	// Initialize local variables
	Vertex v1, v2, v3;
	float w = _width / 2.0f;
	float h = _height / 2.0f;
	vec3 offset = { _offset, 0.0 };
	
	// Set all the vertices
	v1.position = vec3(-w, -h, 0.0) + offset;
	_vertices.push_back(v1);
	v2.position = vec3(w, -h, 0.0) + offset;
	_vertices.push_back(v2);
	v3.position = vec3(0.0f, h, 0.0) + offset;
	_vertices.push_back(v3);

	// Set the indices
	_indices = { 0, 1, 2 };
}

void Utils::GetPolygonVertices(float _width, float _height, int _numSides, vec2 _offset, std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices) {
	// Initialize local variables
	vec3 offset = { _offset, 0.0 };
	float angleBetween = (360.0f / (float)_numSides) * ((float)PI / 180.0f);

	// Get center point
	Vertex origin;
	origin.position = offset;
	_vertices.push_back(origin);

	// Get first point
	Vertex first;
	first.position = vec3(cos(0.0f) * _width, sin(0.0f) * _height, 0.0f) + offset;
	_vertices.push_back(first);

	// Get remaining points
	for (auto i = 1; i < _numSides; i++) {
		Vertex v;
		v.position = vec3((_width * cos(i * angleBetween)), (_height * sin(i * angleBetween)), 0.0f) + offset;
		_vertices.push_back(v);

		// Add the indices to draw the triangle for the last section
		_indices.push_back(i);
		_indices.push_back(0);
		_indices.push_back(i + 1);
	}

	// Complete the polygon by adding the last triangle
	_indices.push_back(_numSides);
	_indices.push_back(0);
	_indices.push_back(1);
}