#pragma once

// File includes
#include "Animation.h"

class UpDownAnimation : public Animation
{
public:

	UpDownAnimation(float _lowerBounds, float _upperBounds, int _initialDirection);
	UpDownAnimation(const UpDownAnimation& copy);
	~UpDownAnimation() {};

	virtual void UpdateAnimation(double _delta, Shape* _subject) override;

	void SetBounds(float _upperBounds, float _lowerBounds);
	float GetUpperBounds() const {
		return upperBounds;
	}
	float GetLowerBounds() const {
		return lowerBounds;
	}

	virtual Animation* Clone() override {
		return new UpDownAnimation(*this);
	}

protected:

	float upperBounds;
	float lowerBounds;
	int direction;
};