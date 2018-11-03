#pragma once
#include "Object.h"

class Barrier : public Object
{
public:
	Barrier(int parentWidth, int parentHeight) : Object(parentWidth, parentHeight, { 0,0,3,2 }) { update(); }
	~Barrier(){}
	Barrier(const Barrier &orig) 
		: Object(
			orig.GetParentWidth(), 
			orig.GetParentHeight(), 
			orig.GetComponentBounds(), 
			orig.getHitpoints()) 
	{ update(); }

	Barrier& operator=(Barrier&& other) {
		// this may be called once or twice. 
		// if called twice, 'other' is the just-moved-from V subobject
		hitpoints = other.hitpoints;
		update();
		SetBounds(other.GetComponentBounds());
		return *this;
	}

	void hit() {
		hitpoints--; 
		update();
	}

	std::vector<CHAR_INFO> getImage() {
		std::vector<CHAR_INFO> img;
		std::string strImage;
		WORD colour;

		switch (getHitpoints()) {
		default:
		case 1:
			strImage = images[2];
			colour = colours[2];
			break;
		case 2:
			strImage = images[1];
			colour = colours[1];
			break;
		case 3:
			strImage = images[0];
			colour = colours[0];
			break;
		}

		for (short i = 0; i < (int) strImage.length(); i++) {
			CHAR_INFO character;
			character.Char.UnicodeChar = 0;
			character.Char.AsciiChar = strImage[i];
			character.Attributes = colour;
			img.push_back(character);
		}

		return img;
	}

	void update() {
		SetComponentString(getImage());
	}

	void move(){}
private:
	const std::array<WORD, 3> colours =
	{
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY ,
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
		
	};

	const std::array<std::string, 3> images = {
		"==="
		"'''",

		"= ="
		" ''",

		"=  "
		" ''"
	};
};