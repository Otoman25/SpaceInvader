#include "stdafx.h"
#include "TextPanel.h"


TextPanel::TextPanel(std::string sText, int panelWidth) : ConsoleComponent(1, 1, 0, 0, panelWidth, 1), text(sText), border(false)
{
	BuildPanel();
}

TextPanel::TextPanel(std::string sText, int panelWidth, bool useBorder) : ConsoleComponent(1, 1, 0, 0, panelWidth, 1), text(sText), border(useBorder)
{
	BuildPanel();
}

void TextPanel::BuildPanel() {
	StringBuilder string;
	int totalLines = (int) ceil((float)text.length() / GetWidth());
	SetDimensions(GetWidth(), totalLines);

	if (border) string.AddRepeatingCharacters('-', GetWidth());

	for (int line = 0; line < totalLines; line++) {
		int startIndex = GetWidth() * line;
		int count = GetWidth();

		string.Add(text.substr(startIndex, count), StringBuilder::DefaultColour(), border);
	}

	if (border) string.AddRepeatingCharacters('-', GetWidth());

	componentString = string.getString();
}

TextPanel::~TextPanel()
{
}
