#pragma once
#include "Object.h"

enum DAMAGE {
	ENEMY = 1,
	PLAYERANDBARRIER = 2
};

class Particle : public Object {
public:
	Particle(int x, int y, COORD direction, DAMAGE dmg) : Object(1, 1, {0,0,1,1}), velocity(direction), damages(dmg) {
		Translate(x, y);
		SetComponentString(image());
	}

	Particle(const Particle &orig) : Object(1, 1, orig.GetComponentBounds()), damages(orig.damages) ,velocity(orig.velocity) {
		SetComponentString(image());
	}

	void update() {}
	void hit() {}
	void move() {
		Translate(velocity.X, velocity.Y);
	}

	Particle& operator=(Particle&& other) {
		// this may be called once or twice. 
		// if called twice, 'other' is the just-moved-from V subobject
		velocity = other.velocity;
		SetComponentString(image());
		SetBounds(other.GetComponentBounds());
		return *this;
	}

	std::vector<CHAR_INFO> image() {
		std::vector<CHAR_INFO> img;
		CHAR_INFO character;
		character.Char.UnicodeChar = 0;
		if(velocity.Y >= 0) character.Char.AsciiChar = imgChar[1];
		else character.Char.AsciiChar = imgChar[0];
		character.Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
		img.push_back(character);
		return img;
	}

	DAMAGE getDamageType() { return damages; }
private:
	std::array<char,2> imgChar = {
		'^',
		'¤'
	};
	COORD velocity;
	DAMAGE damages;
};