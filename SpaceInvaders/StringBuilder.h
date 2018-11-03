#pragma once
#include "stdafx.h"

class StringBuilder
{
public:
	StringBuilder();
	~StringBuilder();
	StringBuilder(const StringBuilder &orig);

	void AddRepeatingCharacters(char character, int amount);
	void AddRepeatingCharacters(char character, int amount, bool border);
	void Add(std::string string);
	void Add(std::string string, WORD colour);
	void Add(std::string string, WORD colour, bool border);
	void SetColour(WORD colour);
	static WORD DefaultColour() { return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; }
	void Clear() { finalString.clear(); }
	std::vector<CHAR_INFO> getString();
private:
	std::vector<CHAR_INFO> finalString;
	WORD wCurrentColour = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	const char BORDER_CHAR_SIDE = '|';
};

