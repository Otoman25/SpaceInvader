#pragma once
#include "stdafx.h"

struct MenuOption {
	char inputCharacter;
	std::string label;
};

class InputMenu
{
public:
	InputMenu();
	~InputMenu();
	void AddChoice(char character, std::string label);
	char WaitForInput();
	char WaitForInput(std::string characters);
	int WaitForAnyKey();
	std::vector<MenuOption> GetMenu() { return menu; }
	std::vector<std::string> GetFormattedMenu();
	std::string GetInputString();
	std::string GetInputString(int size);
private:
	bool keyDown(char key);
	bool keyUp(char key);
	std::vector<MenuOption> menu = std::vector<MenuOption>();
};

