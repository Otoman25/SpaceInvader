#include "stdafx.h"

#include <time.h>

#include "StringBuilder.h"
#include "GConsole.h"

void GConsole::Draw() {
	COORD screenSize = { (short)this->iWidth , (short)this->iHeight };
	SMALL_RECT screen = { 0, 0, (short)iWidth, (short)iHeight };

	if (RenderBorder) AddBorderToBuffer();

	WriteConsoleOutput(this->hHandle, &this->cConsoleBuffer[0], screenSize, { 0,0 }, &screen);
}

void GConsole::ClearConsole()
{
	CHAR_INFO character = CHAR_INFO();
	character.Char.AsciiChar = DEFAULT_CLEAR_CHAR;
	character.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	ClearConsole(character);
}

void GConsole::ClearConsole(char clearCharacter)
{
	CHAR_INFO character = CHAR_INFO();
	character.Char.AsciiChar = clearCharacter;
	character.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

	ClearConsole(character);
}

void GConsole::ClearConsole(CHAR_INFO clearCharacter)
{
	for (int i = 0; i < sTotalCharacters; i++) {
		cConsoleBuffer[i] = clearCharacter;
	}

}

GConsole::GConsole() : iWidth(DEFAULT_WIDTH), iHeight(DEFAULT_HEIGHT), sTotalCharacters(DEFAULT_WIDTH*DEFAULT_HEIGHT)
{
	CreateConsole();
}

GConsole::GConsole(int width, int height) : iWidth(width), iHeight(height), sTotalCharacters(width*height) {
	CreateConsole();
}


GConsole::~GConsole() {
}

void GConsole::sleep(int seconds) {
	int initTime = (int)time(0);
	int currentTime;

	while ((currentTime = (int)time(0)) < (initTime + seconds)) {
		Sleep(1000);
	}
}

void GConsole::DrawStringAtLocation(std::string string, SMALL_RECT bounds)
{
	StringBuilder drawString;
	int lineLength = bounds.Right - bounds.Left;
	
	for (int i = 0; i < (int)string.length(); i+=lineLength) {
		drawString.Add(string.substr(i, lineLength));
	}

	DrawStringAtLocation(drawString.getString(), bounds, GCBSTYLE());
}

void GConsole::DrawStringAtLocation(std::vector<CHAR_INFO> string, SMALL_RECT bounds)
{
	DrawStringAtLocation(string, bounds, GCBSTYLE());
}

void GConsole::DrawStringAtLocation(std::vector<CHAR_INFO> string, SMALL_RECT bounds, GCBSTYLE style)
{
	int width = bounds.Right - bounds.Left;
	int height = bounds.Bottom - bounds.Top;

	CHAR_INFO overflowCharacter;
	overflowCharacter.Attributes = FOREGROUND_RED;
	overflowCharacter.Char.AsciiChar = '-';

	int currentCharacter = bounds.Left + (bounds.Top * this->iWidth);
	int col = 0;

	for (int row = 0; row < height; row++) {
		for (col = 0; col < width; col++, currentCharacter++) {
			if (currentCharacter > (int) cConsoleBuffer.size()) break;

			if ((currentCharacter % iWidth) >= bounds.Left && iWidth - (currentCharacter % iWidth) >= 0) {
				if (col + (row * width) < (int) string.size())
					cConsoleBuffer[currentCharacter] = string[col + (row * width)];
				else
					cConsoleBuffer[currentCharacter] = overflowCharacter;
			}
		}

		currentCharacter += (this->iWidth - col);
	}
}

void GConsole::CreateConsole()
{
	cConsoleBuffer.resize(iWidth*iHeight);

	this->hHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SMALL_RECT screenSize;
	screenSize.Bottom = (short)this->iHeight;
	screenSize.Left = 0;
	screenSize.Right = (short)this->iWidth;
	screenSize.Top = 0;

	SMALL_RECT rect = { 0,0,((SHORT)this->iWidth),((SHORT)this->iHeight) };
	COORD newSize;
	newSize.X = (SHORT)(rect.Right + 1);
	newSize.Y = (SHORT)(rect.Bottom + 1);

	SetConsoleWindowInfo(this->hHandle, TRUE, &rect);
	SetConsoleScreenBufferSize(this->hHandle, newSize);
	SetConsoleActiveScreenBuffer(this->hHandle);

	ClearConsole();
	ToggleCursor();
}

void GConsole::AddBorderToBuffer()
{
	SMALL_RECT borders[4] = {
		{ 0, 0, iWidth, 1 }, //Top
		{ 0, 0, 1, iHeight }, //Left
		{ 1, iHeight-1, iWidth, iHeight }, //Bottom
		{ iWidth-1, 0, iWidth, iHeight } //Right
	};

	StringBuilder borderType[3];
	borderType[0].AddRepeatingCharacters('¯', iWidth);
	borderType[1].AddRepeatingCharacters('|', iHeight);
	borderType[2].AddRepeatingCharacters('_', iWidth);

	DrawStringAtLocation(borderType[0].getString(), borders[0]);
	DrawStringAtLocation(borderType[2].getString(), borders[2]);
	DrawStringAtLocation(borderType[1].getString(), borders[1]);
	DrawStringAtLocation(borderType[1].getString(), borders[3]);

}

void GConsole::ToggleCursor() {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(this->hHandle, &cursorInfo);
	cursorInfo.bVisible = !cursorInfo.bVisible;
	SetConsoleCursorInfo(this->hHandle, &cursorInfo);
}

void GConsole::SetCursorPos(int x, int y) {
	SetConsoleCursorPosition(hHandle, { (short)x, (short)y });
}

void GConsole::SetCursorPos(COORD pos) {
	SetConsoleCursorPosition(hHandle, pos);
}

void GConsole::AddComponent(ConsoleComponent *component)
{
	DrawStringAtLocation(component->string(), component->GetComponentBounds());
}
