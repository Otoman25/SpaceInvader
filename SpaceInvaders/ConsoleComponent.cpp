#include "stdafx.h"
#include "ConsoleComponent.h"
#include <sstream>

std::string ConsoleComponent::JustifyText(std::string text, int lineLength, GCBENUM justify)
{
	std::stringstream ss;
	float totalSpace = (float)lineLength - (float)text.length();
	int leftSpaceAmount = 0;

	switch (justify) {
		default:
		case TEXT_CENTER:
			leftSpaceAmount = (int)ceil(totalSpace/2);
			break;
		case TEXT_LEFT:
			leftSpaceAmount = 0;
			break;
		case TEXT_RIGHT:
			leftSpaceAmount = (int) totalSpace;
			break;
	}
	int currentChar = 0;

	for (currentChar = 0; currentChar < leftSpaceAmount; currentChar++) {
		ss << ' ';
	}

	ss << text;
	currentChar += text.length();
	for (; currentChar < lineLength; currentChar++) {
		ss << ' ';
	}

	return ss.str();
}

void ConsoleComponent::AddMenuText(StringBuilder *builder, InputMenu menu) {
	for (std::string opt : menu.GetFormattedMenu()) {
		builder->Add(ConsoleComponent::LeftText(opt, GetWidth()));
	}
}

void ConsoleComponent::Translate(int x, int y)
{
	rWindowBounds.Left += x;
	rWindowBounds.Right += x;

	rWindowBounds.Top += y;
	rWindowBounds.Bottom += y;
}
