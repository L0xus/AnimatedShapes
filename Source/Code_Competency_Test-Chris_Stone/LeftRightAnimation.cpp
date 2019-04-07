// File includes
#include "LeftRightAnimation.h"
#include "Entity.h"

LeftRightAnimation::LeftRightAnimation(float _leftBounds, float _rightBounds, int _initialDirection)
{
	// Error checking
	if (_leftBounds >= _rightBounds) throw invalid_argument{ "Invalid bounds" };
	if (_initialDirection != -1 && _initialDirection != 1) throw invalid_argument{ "Direction must be -1 or 1" };

	// Assign variables
	direction = _initialDirection;
	leftBounds = _leftBounds;
	rightBounds = _rightBounds;
}

LeftRightAnimation::LeftRightAnimation(const LeftRightAnimation & copy)
{
	animationSpeed = copy.GetAnimationSpeed();
	playing = copy.playing;
	leftBounds = copy.leftBounds;
	rightBounds = copy.rightBounds;
	direction = copy.direction;
}

void LeftRightAnimation::UpdateAnimation(double _delta, Shape * _subject)
{
	if (playing) {
		vec2 location = _subject->GetLocation();
		// Add movement to the current location
		location.x += (animationSpeed * direction * (float)_delta);
		// Change directions if bounds are reached
		if (location.x >= rightBounds) {
			location.x = rightBounds;
			direction *= -1;
		}
		if (location.x <= leftBounds) {
			location.x = leftBounds;
			direction *= -1;
		}
		_subject->SetLocation(location);
	}
}

void LeftRightAnimation::SetBounds(float _leftBounds, float _rightBounds)
{
	leftBounds = _leftBounds;
	rightBounds = _rightBounds;
}
