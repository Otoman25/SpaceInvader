#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(int parentWidth, int parentHeight) : Object(parentWidth, parentHeight, { 0,0,3,3 }, 3) {
		
		SetComponentString(image());
	}

	Player(const Player &orig) : score(orig.score),
		Object(
			orig.GetParentWidth(),
			orig.GetParentHeight(),
			orig.GetComponentBounds(),
			orig.getHitpoints())
	{
		SetComponentString(image());
	}

	Player& operator=(Player&& other) {
		// this may be called once or twice. 
		// if called twice, 'other' is the just-moved-from V subobject
		score = other.score;
		SetComponentString(image());
		return *this;
	}

	std::vector<CHAR_INFO> image() {
		std::vector<CHAR_INFO> img;
		WORD colour = FOREGROUND_BLUE | FOREGROUND_GREEN;

		for (short i = 0; i < (int)playerImage.length(); i++) {
			CHAR_INFO character;

			character.Char.UnicodeChar = 0;
			if (playerImage[i] == 'o') character.Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN ;
			else if (playerImage[i] == '¡') character.Attributes = BACKGROUND_RED;
			else if (playerImage[i] != ' ') character.Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN;
			else character.Attributes = colour;

			if(playerImage[i] != '.') character.Char.AsciiChar = playerImage[i];
			img.push_back(character);
		}

		return img;
	}

	void addScore(int s) {
		score += s;
	}

	int getScore() { return score;  }

	void move(COORD direction) {
		Translate(direction.X, direction.Y);
	}
	void update(){}
	void hit() { hitpoints--; }

private:
	int score = 0;

	const std::string playerImage =
		" o "
		"..."
		"¡ ¡";
};