#pragma once

// File includes
#include "Shape.h"

class Hexagon :
	public Shape
{
public:

	Hexagon(float _width, float height, vec2 _offset = { 0.0, 0.0 });
	Hexagon(const Hexagon& _copy);
	~Hexagon() {};

	virtual Shape* Clone() override {
		return new Hexagon(*this);
	}

protected:

	float width;
	float height;

};

