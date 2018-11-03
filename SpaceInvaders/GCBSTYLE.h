/* 
 * File:   GCBSTYLE.h
 * Author: George Richards
 *
 * Created on 23 October 2017, 19:53
 */

#ifndef GCBSTYLE_H
#define GCBSTYLE_H

#include <Windows.h>

enum GCBENUM {
    DEFAULT,
    HEADER_FULL_PAGE,
    HEADER_TOP_PAGE,
    HEADER_BOTTOM,
    TEXT_LEFT, 
    TEXT_CENTER, 
    TEXT_RIGHT, 
    STRING_REPEATING,
    STRING_ONCE,
    MENU_LEFT,
    MENU_RIGHT,
    MENU_CENTER
};

class GCBSTYLE {
public:
    GCBSTYLE();
    GCBSTYLE(const GCBSTYLE& orig);
    virtual ~GCBSTYLE();
    const GCBENUM getHeaderSetting();
    const GCBENUM getTextSetting();
    const GCBENUM getStringSetting();
    const GCBENUM getMenuSetting();
    const WORD getColourSetting();
    void setHeaderSetting(GCBENUM setting);
    void setTextSetting(GCBENUM setting);
    void setStringSetting(GCBENUM setting);
    void setMenuSetting(GCBENUM setting);
    void setColourSetting(WORD setting);
    void resetToDefaults();
private:
	int headerSetting; 
	int textSetting; 
	int stringSetting; 
	int menuSetting; 
	int colourSetting; 

	//Defaults
	const static int DEFAULT_HEADER = HEADER_TOP_PAGE;
	const static int DEFAULT_TEXT = TEXT_LEFT;
	const static int DEFAULT_STRING = STRING_ONCE;
	const static int DEFAULT_MENU = MENU_CENTER;
	const static int DEFAULT_COLOUR = DEFAULT;
};

#endif /* GCBSTYLE_H */

