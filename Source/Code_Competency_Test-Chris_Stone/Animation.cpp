// File includes
#include "Animation.h"

Animation::Animation()
{
	// Animation does not play by default. Default speed is 1
	animationSpeed = 1.0f;
	playing = false;
}

void Animation::StartAnimation()
{
	playing = true;
}

void Animation::StopAnimation()
{
	playing = false;
}

void Animation::SetAnimationSpeed(float _newSpeed)
{
	animationSpeed = _newSpeed;
}