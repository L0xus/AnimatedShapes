#pragma once

// File includes
#include "Animation.h"

class BoxAnimation : public Animation
{
public:

	BoxAnimation(float _lowerBound, float _upperBound, float _leftBound, float _rightBound, int _directionX, int _directionY);
	BoxAnimation(const BoxAnimation& _copy);
	~BoxAnimation() {};

	virtual void UpdateAnimation(double _delta, Shape* _subject) override;

	virtual Animation* Clone() override {
		return new BoxAnimation(*this);
	}

protected:

	float upperBound;
	float lowerBound;
	float rightBound;
	float leftBound;

	int currentAxis;
	int directionX;
	int directionY;
};

