#pragma once


#include "GCBSTYLE.h"
#include "ConsoleComponent.h"

class GConsole
{
public:
	void Draw();
	void ClearConsole();
	void ClearConsole(char clearCharacter);
	GConsole();
	GConsole(int width, int height);
	~GConsole();
	void sleep(int seconds);
	void ToggleCursor();
	void SetCursorPos(int x, int y);
	void SetCursorPos(COORD pos);
	void AddComponent(ConsoleComponent* component);
	int GetConsoleWidth() { return iWidth; }
	int GetConsoleHeight() { return iHeight; }
	void SetTitle(std::wstring title) { SetConsoleTitle((LPCWSTR)title.c_str()); }
private:
	bool RenderBorder = true; //Draw the border after writing to the buffer
	const char DEFAULT_CLEAR_CHAR = ' ';
	const int iWidth; // Max characters in x axis
	const int iHeight;  // Max rows in console window
	int sTotalCharacters;
	std::vector<CHAR_INFO> cConsoleBuffer; //Created with dimensions iWidth*iHeight, used to store the all characters and colours to display on ConsoleDraw()

	HANDLE hHandle;

	//Functions
	void CreateConsole();
	void AddBorderToBuffer();
	void ClearConsole(CHAR_INFO clearCharacter);
	void DrawStringAtLocation(std::string string, SMALL_RECT bounds);
	void DrawStringAtLocation(std::vector<CHAR_INFO> string, SMALL_RECT bounds);
	void DrawStringAtLocation(std::vector<CHAR_INFO> string, SMALL_RECT bounds, GCBSTYLE style);

	//Defaults
	static const int DEFAULT_HEIGHT = 28;
	static const int DEFAULT_WIDTH = 118;
};

