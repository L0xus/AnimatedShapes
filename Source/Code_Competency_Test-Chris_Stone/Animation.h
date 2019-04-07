#pragma once

// File includes
#include "Utils.h"
#include "Shape.h"

class Animation
{
public:

	Animation();
	~Animation() {};

	void StartAnimation();
	void StopAnimation();
	bool IsAnimationPlaying() const {
		return playing;
	}

	void SetAnimationSpeed(float _newSpeed);
	float GetAnimationSpeed() const {
		return animationSpeed;
	}

	virtual void UpdateAnimation(double _delta, Shape* _subject) = 0;
	virtual Animation* Clone() = 0;		// To support the prototype method

protected:

	float animationSpeed;
	bool playing;

};