#pragma once
#include "stdafx.h"
#include "GCBSTYLE.h"
#include "InputMenu.h"
#include "StringBuilder.h"

class ConsoleComponent {
public:
	ConsoleComponent() : parentWidth(1), parentHeight(1) {};
	ConsoleComponent(int width, int height, int x1, int y1, int x2, int y2) : parentWidth(width), parentHeight(height) { SetBounds(x1, y1, x2, y2); }
	ConsoleComponent(int width, int height, SMALL_RECT bounds) : parentWidth(width), parentHeight(height), rWindowBounds(bounds) {}
	ConsoleComponent(const ConsoleComponent &orig) : parentWidth(orig.parentWidth), parentHeight(orig.parentHeight) { SetBounds(orig.rWindowBounds); componentString = orig.componentString; }

	ConsoleComponent& operator=(ConsoleComponent&& other) {
		// this may be called once or twice. 
		// if called twice, 'other' is the just-moved-from V subobject
		SetBounds(other.GetComponentBounds());
		return *this;
	}

	static std::string LeftText(std::string text, int lineLength) { return JustifyText(text, lineLength, TEXT_LEFT); }
	static std::string CenterText(std::string text, int lineLength) { return JustifyText(text, lineLength, TEXT_CENTER); }
	static std::string RightText(std::string text, int lineLength) { return JustifyText(text, lineLength, TEXT_RIGHT); }
	static std::string JustifyText(std::string text, int lineLength, GCBENUM justify);

	void AddMenuText(StringBuilder * str, InputMenu menu); //Add The Menu To The Component Display (Text Is LEFT Justified, 1 Option Per Line)

	void SetPosition(int x, int y) { rWindowBounds.Top = x; rWindowBounds.Left = y; }
	void SetDimensions(int cols, int rows) { rWindowBounds.Right = rWindowBounds.Left + cols; rWindowBounds.Bottom = rWindowBounds.Top + rows; }
	void SetDefaultBounds() { rWindowBounds = defaultBounds; }
	void SetComponentString(std::vector<CHAR_INFO> str) { componentString = str; }

	void Translate(int x, int y);

	int GetParentWidth() const { return this->parentWidth; }
	int GetParentHeight() const { return this->parentHeight; }
	int GetWidth() const { return rWindowBounds.Right - rWindowBounds.Left; }
	int GetHeight() const { return rWindowBounds.Bottom - rWindowBounds.Top; }
	std::vector<CHAR_INFO> string() const { return componentString; };
	std::vector<CHAR_INFO>* GetComponentString() { return &componentString; };
	SMALL_RECT GetComponentBounds() const { return rWindowBounds; }
	InputMenu GetDefaultMenu() { return defaultMenu; }

protected:
	std::vector<CHAR_INFO> componentString;	
	void SetBounds(SMALL_RECT bounds) { rWindowBounds = bounds; defaultBounds = bounds; }
	void SetBounds(int x, int y, int cols, int rows) { rWindowBounds.Top = x; rWindowBounds.Left = y; rWindowBounds.Bottom = rows; rWindowBounds.Right = cols; defaultBounds = rWindowBounds; }
	
private:
	SMALL_RECT rWindowBounds;
	SMALL_RECT defaultBounds;
	const int parentWidth;
	const int parentHeight;

	InputMenu defaultMenu = InputMenu();

};