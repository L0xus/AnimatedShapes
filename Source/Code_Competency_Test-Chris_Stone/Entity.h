#pragma once

// File includes
#include "Shape.h"
#include "Utils.h"
#include "Animation.h"

class Entity
{
public:

	Entity(vec2 _location = { 0.0, 0.0 });
	Entity(const Entity& copy);		// Copy constructor for clone
	virtual ~Entity();

	virtual void Update(double _delta);
	virtual void Draw(GLuint _program);

	void AddShape(Shape* _shape);
	std::vector<Shape*>& GetShapes() {
		return shapes;
	}

	void AddAnimation(Animation* _animation);
	void PlayAnimation(int _index);

	void SetLocation(vec2 _newLocation);
	vec2 GetLocation() const {
		return location;
	}

	Entity* Clone();	// Clone operation for prototype pattern

protected:

	std::vector<Shape*> shapes;		// Using vector to support composite shapes
	std::vector<Animation*> animations; // Using vector to support multiple animations 
	int currentAnimatonIndex;

private:

	vec2 location;

};

