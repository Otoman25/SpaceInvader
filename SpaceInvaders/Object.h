#pragma once
#include "ConsoleComponent.h"

/*
Used to create a 3x3 object
*/
class Object : public ConsoleComponent
{
public:
	Object(int parentWidth, int parentHeight) : ConsoleComponent(parentWidth, parentHeight, 0, 0, 3, 3) {}
	Object(int parentWidth, int parentHeight, SMALL_RECT bounds, int hp) : hitpoints(hp), ConsoleComponent(parentWidth, parentHeight, bounds) {};
	Object(int parentWidth, int parentHeight, SMALL_RECT bounds) : ConsoleComponent(parentWidth, parentHeight, bounds) {};
	Object(const Object &orig) : ConsoleComponent(orig.GetParentWidth(), orig.GetParentHeight(), orig.GetComponentBounds())  {  }
	~Object() {}

	Object& operator=(Object&& other) {
		// this may be called once or twice. 
		// if called twice, 'other' is the just-moved-from V subobject
		hitpoints = other.hitpoints;
		return *this;
	}

	int getHitpoints() const { return hitpoints; }
	void setHitpoints(int hp) { hitpoints = hp; }
	virtual void update() = 0;
	virtual void hit() = 0;

protected:
	int hitpoints = 3;

private:
};

