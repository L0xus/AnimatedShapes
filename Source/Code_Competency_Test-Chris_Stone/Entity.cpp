// File includes
#include "Entity.h"
#include "Square.h"
#include "Triangle.h"

Entity::Entity(vec2 _location)
{
	SetLocation(_location);
}

Entity::Entity(const Entity & copy)
{
	currentAnimatonIndex = copy.currentAnimatonIndex;
	location = copy.location;

	// use the clone methods of shape and animation to get copies of each
	for (auto shape : copy.shapes) {
		shapes.push_back(shape->Clone());
	}
	for (auto animation : copy.animations) {
		animations.push_back(animation->Clone());
	}
}

Entity::~Entity()
{
	// Delete all shapes and clear the vector
	for (auto shape : shapes) {
		delete shape;
		shape = 0;
	}
	shapes.clear();
	// Delete all animations and clear the vector
	for (auto animation : animations) {
		delete animation;
		animation = 0;
	}
	animations.clear();
}

void Entity::Update(double _delta)
{
	// As long as there is an animation to play, update it
	if (!animations.empty()) {
		/* Play the animation on every shape. This may be modified so 
		that some animations play for one shape, while another plays 
		for a different shape, to create complex entities*/
		for (auto shape : shapes) {
			animations[currentAnimatonIndex]->UpdateAnimation(_delta, shape);
		}
	}
}

void Entity::Draw(GLuint _program)
{
	// Draw every shape that belongs to this entity
	for (auto shape : shapes) {
		shape->Draw(_program);
	}
}

void Entity::AddShape(Shape* _shape)
{
	// Add the shape to the vector, and snap it to this entity's location
	_shape->SetLocation(this->location);
	shapes.push_back(_shape);
}

void Entity::AddAnimation(Animation * _animation)
{
	animations.push_back(_animation);
}

void Entity::PlayAnimation(int _index)
{
	// Check for out of range
	if (_index < 0 || _index >= (int)animations.size()) throw out_of_range{ "invalid index" };
	
	// Start the current animation
	currentAnimatonIndex = _index;
	animations[currentAnimatonIndex]->StartAnimation();
}

void Entity::SetLocation(vec2 _newLocation)
{
	location = _newLocation;
	/* Update all shape locations so they follow this entity.
	Could be modified so that you can set a flag for whether a
	shape should follow it's parent.*/
	for (auto shape : shapes) {
		shape->SetLocation(_newLocation);
	}
}

Entity * Entity::Clone()
{
	return new Entity(*this);
}