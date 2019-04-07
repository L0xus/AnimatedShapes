#pragma once

// File includes
#include "Shape.h"

class Triangle : public Shape
{
public:

	Triangle(float _width, float _height, vec2 offset = {0.0, 0.0});
	Triangle(const Triangle& _copy);
	~Triangle() {};

	virtual Shape* Clone() override {
		return new Triangle(*this);
	};

protected:

	float width;
	float height;

};

