#include "stdafx.h"
#include "InputMenu.h"
#include <sstream>
#include <iostream>
#include <array>

InputMenu::InputMenu()
{
}


InputMenu::~InputMenu()
{
}

void InputMenu::AddChoice(char character, std::string label)
{
	MenuOption opt = { character, label };
	menu.push_back(opt);
}

char InputMenu::WaitForInput(std::string characters) {
	char returnChar;
	bool hasBeenSet = false;
	float fTimeElapsed = 0.0f;

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	Sleep(10);

	while (1) {
		while (!hasBeenSet) {
			if ((int)floor(fTimeElapsed) % 1 == 0) {
				for(char c : characters){
					if (keyDown(c)) {
						returnChar = c;
						hasBeenSet = true;
						break;
					}
				}
			}

			Sleep(5);
		}

		Sleep(10);

		return returnChar;
	}
}

char InputMenu::WaitForInput()
{
	std::stringstream ss;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	for (MenuOption opt : menu) {
		ss << opt.inputCharacter;
	}
	
	return WaitForInput(ss.str());
}

int InputMenu::WaitForAnyKey()
{
	Sleep(100);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	std::array<int, 2> keys = { VK_RETURN, VK_SPACE };
	Sleep(5);
	while (1) {
		for (int i = 0; i < (keys.size()); i++) {
			if (keyDown(keys[i])) return keys[i];
		}
	}
}

bool InputMenu::keyDown(char key) {
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}

bool InputMenu::keyUp(char key) {
	return (GetAsyncKeyState(key) & 0x0001) != 0;
}

std::vector<std::string> InputMenu::GetFormattedMenu()
{
	std::vector<std::string> menuVec;
	std::stringstream ss;

	menuVec.push_back("Please press the key the corresponds to the desired option:");

	for (MenuOption opt : menu) {
		ss << opt.inputCharacter << " - " << opt.label;
		menuVec.push_back(ss.str());
		ss = std::stringstream();
	}

	return menuVec;
}

std::string InputMenu::GetInputString() {
	return GetInputString(20);
}

std::string InputMenu::GetInputString(int size) {
	std::stringstream ss;
	char *buffer = new char[size];
	DWORD read;
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hIn);
	ReadConsole(hIn, buffer, size * sizeof(char), &read, nullptr);

	std::cout << GetLastError();

	if (read < size) FlushConsoleInputBuffer(hIn);
	std::string input(buffer, (read * 2));

	for (char character : input) {
		if (character == '\n') break;

		if (character != '\0' && character != '\r') ss << character;
	}

	delete buffer;
	return ss.str();
}
