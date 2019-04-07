#pragma once

// Library includes
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
using namespace glm;

#define PI 3.14159265359

// Contains information about a vertex (could contain normals and texture coordinates as well as position)
struct Vertex {
	vec3 position;
};

class Utils
{
public:

	static void PrintShaderLog(GLuint _shader);
	static void PrintProgramLog(int _program);
	static bool CheckOpenGLError();

	static std::string ReadShaderSource(const char* _filePath);

	static void GetSquareVertices(float _sideLength, vec2 _offset, std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices);
	static void GetTriangleVertices(float _width, float _height, vec2 _offset, std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices);
	static void GetPolygonVertices(float _width, float _height, int _numSides, vec2 _offset, std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices);
};