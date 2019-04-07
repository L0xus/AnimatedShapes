// File includes
#include "BoxAnimation.h"
#include "Entity.h"

BoxAnimation::BoxAnimation(float _lowerBound, float _upperBound, float _leftBound, float _rightBound, int _directionX, int _directionY)
{
	// Error checking, cannot have a negative direction, lower bounds must be less than upper
	if (_lowerBound >= _upperBound || _leftBound >= _rightBound) throw invalid_argument{ "Invalid bounds" };
	if (_directionX != -1 && _directionX != 1) throw invalid_argument{ "DirectionX must be -1 or 1" };
	if (_directionY != -1 && _directionY != 1) throw invalid_argument{ "DirectionY must be -1 or 1" };

	// Assign variables
	upperBound = _upperBound;
	lowerBound = _lowerBound;
	leftBound = _leftBound;
	rightBound = _rightBound;
	
	currentAxis = -1; // Start moving on the X axis
	directionX = _directionX;
	directionY = _directionY;
}

BoxAnimation::BoxAnimation(const BoxAnimation & _copy)
{
	animationSpeed = _copy.animationSpeed;
	playing = _copy.playing;
	upperBound = _copy.upperBound;
	lowerBound = _copy.lowerBound;
	leftBound = _copy.leftBound;
	rightBound = _copy.rightBound;
	currentAxis = _copy.currentAxis;
	directionX = _copy.directionX;
	directionY = _copy.directionY;
}

void BoxAnimation::UpdateAnimation(double _delta, Shape * _subject)
{
	if (playing) {
		vec2 location = _subject->GetLocation();
		// Process X axis movement
		if (currentAxis == -1)
		{
			location.x += (animationSpeed * directionX * (float)_delta);
			// Change current axis direction and swap axis if bounds are reached
			if (location.x >= rightBound) {
				location.x = rightBound;
				directionX *= -1;
				currentAxis *= -1;
			}
			if (location.x <= leftBound) {
				location.x = leftBound;
				directionX *= -1;
				currentAxis *= -1;
			}
		}
		// Process Y axis movement
		else
		{
			// Change current axis direction and swap axis if bounds are reached
			location.y += (animationSpeed * directionY * (float)_delta);
			if (location.y >= upperBound) {
				location.y = upperBound;
				directionY *= -1;
				currentAxis *= -1;
			}
			if (location.y <= lowerBound) {
				location.y = lowerBound;
				directionY *= -1;
				currentAxis *= -1;
			}
		}
		_subject->SetLocation(location);
	}
}