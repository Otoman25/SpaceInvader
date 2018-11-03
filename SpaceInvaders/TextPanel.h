#pragma once
#include "ConsoleComponent.h"

class TextPanel : public ConsoleComponent
{
public:
	TextPanel(std::string text, int panelWidth);
	TextPanel(std::string text, int panelWidth, bool border);
	TextPanel(const TextPanel &orig) : text(orig.text), ConsoleComponent(orig.GetParentWidth(), orig.GetParentHeight(), orig.GetComponentBounds()) {
		SetComponentString(orig.string());
	}
	void BuildPanel();
	~TextPanel();

	/*
		FIX setText, panel not showing after changing text
	*/
	void setText(std::string str) { text = str; SetDimensions(str.length(), 1); BuildPanel(); }
	void setText(std::string str, int width) { text = str; SetDimensions(width, 1); BuildPanel(); }
private:
	boolean border = false;
	std::string text;
};

