#pragma once

// File includes
#include "Shape.h"

class Square : public Shape
{
public:

	Square(float _sideLength, vec2 _offset = { 0.0, 0.0 });
	Square(const Square& _copy);
	~Square() {};

	virtual Shape* Clone() override {
		return new Square(*this);
	}

protected:

	float sideLength;

};

