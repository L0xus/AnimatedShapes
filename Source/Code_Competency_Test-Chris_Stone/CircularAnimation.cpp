// Library includes
#include <math.h>

// File includes
#include "CircularAnimation.h"
#include "Entity.h"

CircularAnimation::CircularAnimation(vec2 _pointOfRotation, int _direction)
{
	// Error checking
	if (_direction != -1 && _direction != 1) throw invalid_argument{ "Direction must be -1 or 1" };

	// Assign variables
	pivot = _pointOfRotation;
	direction = _direction;
}

CircularAnimation::CircularAnimation(const CircularAnimation & _copy)
{
	animationSpeed = _copy.GetAnimationSpeed();
	playing = _copy.playing;
	pivot = _copy.pivot;
	direction = _copy.direction;
}

void CircularAnimation::UpdateAnimation(double _delta, Shape * _subject)
{
	if (playing) {
		// Get current location and angle to rotate by
		vec2 location = _subject->GetLocation();
		float angle = (direction * animationSpeed * (float)_delta);

		// Adjust location as if pivot is origin
		location -= pivot;

		// Rotate around the origin
		float newX = location.x * cos(angle) - location.y * sin(angle);
		float newY = location.x * sin(angle) + location.y * cos(angle);

		// Move add offset back and update the subject
		location = vec2(newX, newY) + pivot;
		_subject->SetLocation(location);
	}
}
