#pragma once
#include "Object.h"

class Enemy : public Object
{
public:
	Enemy(int type, int parentWidth, int parentHeight) : Object(parentWidth, parentHeight, { 0,0,3,3 }, type) {
		switch (type) {
		case 1:
			hitpoints = 1;
			typeIndex = 0;
			break;
		case 2:
			hitpoints = 2;
			typeIndex = 1;
			break;
		default:
			hitpoints = 3;
			typeIndex = 2;
			break;
		}

		SetComponentString(getType(typeIndex));
	}

	Enemy(const Enemy &orig)
		: moveCounter(orig.moveCounter), typeIndex(orig.typeIndex), 
		Object(
			orig.GetParentWidth(), 
			orig.GetParentHeight(), 
			orig.GetComponentBounds(), 
			orig.getHitpoints()) 
	{ 
		SetComponentString(getType(typeIndex)); 
	}

	Enemy& operator=(Enemy&& other) {
		hitpoints = other.hitpoints;
		typeIndex = other.typeIndex;
		moveCounter = other.moveCounter;
		SetBounds(other.GetComponentBounds());
		SetComponentString(getType(typeIndex));
		return *this;
	}

	void update() {}

	void move(int direction) {
		move(direction, 0);
		moveCounter++;
	}

	void move(int direction, int yMovement) {
		Translate(direction, yMovement);
		moveCounter++;
	}

	void hit() { hitpoints--; }
	int getType() const { return typeIndex + 1; };

	int getMoveCounter() { return moveCounter; }
	void resetMoveCounter() { moveCounter = 0; }

private:
	int typeIndex;
	int moveCounter = 0;

	std::vector<CHAR_INFO> getType(int type) {
		std::vector<CHAR_INFO> img;
		std::string strImage = images[type];
		WORD colour = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;

		for (short i = 0; i < (int) strImage.length(); i++) {
			CHAR_INFO character;

			character.Char.UnicodeChar = 0;
			if(strImage[i] != ' ') character.Attributes = colours[typeIndex];
			else character.Attributes = colour;

			character.Char.AsciiChar = strImage[i];
			img.push_back(character);
		}

		return img;
	}

	const std::array<WORD, 3> colours = {
		BACKGROUND_RED,
		BACKGROUND_RED | BACKGROUND_BLUE,
		BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY
	};

	const std::array<std::string, 3> images = {
		//Type 1
		" | "
		"+.+"
		" | ",
		//Type 2
		"\\ /"
		" . "
		"/ \\",
		//Type 3
		"   "
		" . "
		"/ \\"
	};
};