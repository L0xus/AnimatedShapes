#pragma once

// File includes
#include "Animation.h"

class LeftRightAnimation : public Animation
{
public:

	LeftRightAnimation(float _leftBounds, float _rightBounds, int _initialDirection);
	LeftRightAnimation(const LeftRightAnimation& copy);
	~LeftRightAnimation() {};

	virtual void UpdateAnimation(double _delta, Shape* _subject) override;

	void SetBounds(float _leftBounds, float _rightBounds);
	float GetLeftBounds() const {
		return leftBounds;
	}
	float GetRightBounds() const {
		return rightBounds;
	}

	virtual Animation* Clone() override {
		return new LeftRightAnimation(*this);
	}

protected:

	float leftBounds;
	float rightBounds;
	int direction;

};