// File includes
#include "UpDownAnimation.h"
#include "Entity.h"

UpDownAnimation::UpDownAnimation(float _lowerBounds, float _upperBounds, int _initialDirection)
{
	// Error checking: make sure parameters are valid
	if (_lowerBounds >= _upperBounds) throw invalid_argument{ "Invalid bounds" };
	if (_initialDirection != -1 && _initialDirection != 1) throw invalid_argument{ "Direction must be -1 or 1" };

	// Assign variables
	direction = _initialDirection;
	lowerBounds = _lowerBounds;
	upperBounds = _upperBounds;
}

UpDownAnimation::UpDownAnimation(const UpDownAnimation & copy)
{
	animationSpeed = copy.GetAnimationSpeed();
	playing = copy.playing;
	lowerBounds = copy.lowerBounds;
	upperBounds = copy.upperBounds;
	direction = copy.direction;
}

void UpDownAnimation::UpdateAnimation(double _delta, Shape * _subject)
{
	if (playing) {
		vec2 location = _subject->GetLocation();
		// Add movement on to the current location
		location.y += (animationSpeed * direction * (float)_delta);
		// Change direction if bounds are reached
		if (location.y >= upperBounds) {
			location.y = upperBounds;
			direction *= -1;
		}
		if (location.y <= lowerBounds) {
			location.y = lowerBounds;
			direction *= -1;
		}
		_subject->SetLocation(location);
	}
}

void UpDownAnimation::SetBounds(float _upperBounds, float _lowerBounds)
{
	upperBounds = _upperBounds;
	lowerBounds = _lowerBounds;
}
