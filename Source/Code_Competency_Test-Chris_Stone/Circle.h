#pragma once

// File includes
#include "Shape.h"
class Circle :
	public Shape
{
public:
	Circle(float _radius, vec2 _offset = { 0.0, 0.0 });
	Circle(const Circle& _copy);
	~Circle() {};

	virtual Shape* Clone() override {
		return new Circle(*this);
	}

protected:

	float radius;

};

