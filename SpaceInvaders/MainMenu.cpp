#include "stdafx.h"
#include "MainMenu.h"
#include "StringBuilder.h"
#include <sstream>

MainMenu::MainMenu(int parentWidth, int parentHeight) : ConsoleComponent(parentWidth, parentHeight, 1, 1, parentWidth - 1, 7 )
{

	menu.AddChoice('1', "Play");
	menu.AddChoice('2', "Options");
	menu.AddChoice('X', "Exit");

	StringBuilder builder;
	builder.Add(ConsoleComponent::CenterText("Main Menu", GetWidth()), FOREGROUND_RED);
	builder.AddRepeatingCharacters('-', GetWidth());
	AddMenuText(&builder, menu);

	SetComponentString(builder.getString());
}


MainMenu::~MainMenu()
{
}

InputMenu MainMenu::GetMenu()
{
	return menu;
}
