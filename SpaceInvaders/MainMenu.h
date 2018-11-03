#pragma once
#include "ConsoleComponent.h"
#include "stdafx.h"

class MainMenu : public ConsoleComponent
{
public:
	MainMenu(int parentWidth, int parentHeight);
	~MainMenu();

	InputMenu GetMenu();

private:
	InputMenu menu;
};

