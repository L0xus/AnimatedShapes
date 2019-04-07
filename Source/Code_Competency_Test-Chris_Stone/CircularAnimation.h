#pragma once

// File includes
#include "Animation.h"

class CircularAnimation : public Animation
{
public:

	CircularAnimation(vec2 _pointOfRotation, int _direction);
	CircularAnimation(const CircularAnimation& _copy);
	~CircularAnimation() {};

	virtual void UpdateAnimation(double _delta, Shape* _subject) override;

	virtual Animation* Clone() override {
		return new CircularAnimation(*this);
	}

protected:

	vec2 pivot;
	int direction;

};