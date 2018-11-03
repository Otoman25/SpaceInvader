#include "stdafx.h"
#include <sstream>
#include "StringBuilder.h"


StringBuilder::StringBuilder()
{
}

StringBuilder::~StringBuilder()
{
}

StringBuilder::StringBuilder(const StringBuilder &orig) {
	finalString = orig.finalString;
}

void StringBuilder::AddRepeatingCharacters(char character, int amount)
{
	AddRepeatingCharacters(character, amount, false);
}

void StringBuilder::AddRepeatingCharacters(char character, int amount, bool border)
{
	int counter = 0;

	for (int i = 0; i < amount; i++) {
		CHAR_INFO nextChar = CHAR_INFO();

		if (border && (counter == 0 || counter == amount - 1)) {
			nextChar.Char.AsciiChar = BORDER_CHAR_SIDE;
		}
		else {
			nextChar.Char.AsciiChar = character;
		}

		nextChar.Attributes = wCurrentColour;

		finalString.push_back(nextChar);
		counter++;
	}
}

void StringBuilder::Add(std::string string)
{
	Add(string, wCurrentColour, false);
}

void StringBuilder::Add(std::string string, WORD colour)
{
	Add(string, colour, false);
}

void StringBuilder::Add(std::string string, WORD colour, bool border)
{
	int counter = 0;

	for (char character : string) {
		CHAR_INFO nextChar = CHAR_INFO();

		if (border && (counter == 0 || counter == string.length()-1)) {
			nextChar.Char.AsciiChar = BORDER_CHAR_SIDE;
			nextChar.Attributes = wCurrentColour;
		} 
		else {
			nextChar.Char.AsciiChar = character;
			nextChar.Attributes = colour;
		}
		

		finalString.push_back(nextChar);
		counter++;
	}
}

void StringBuilder::SetColour(WORD colour)
{
}

std::vector<CHAR_INFO> StringBuilder::getString()
{
	if(finalString.size() > 0)
		return finalString;

	return std::vector<CHAR_INFO>();
}