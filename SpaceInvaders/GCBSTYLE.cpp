/* 
 * File:   GCBSTYLE.cpp
 * Author: George Richards
 * 
 * Created on 23 October 2017, 19:53
 */

#include "stdafx.h"
#include "GCBSTYLE.h"

GCBSTYLE::GCBSTYLE() {
}

GCBSTYLE::GCBSTYLE(const GCBSTYLE& orig) {
    this->colourSetting = orig.colourSetting;
    this->headerSetting = orig.headerSetting;
    this->menuSetting = orig.menuSetting;
    this->textSetting = orig.textSetting;
    this->stringSetting = orig.stringSetting;
}

GCBSTYLE::~GCBSTYLE() {
}

const GCBENUM GCBSTYLE::getMenuSetting(){
    return (GCBENUM) this->menuSetting;
}

const GCBENUM GCBSTYLE::getHeaderSetting(){
    // Whether head will take up full page or just at the top of screen
    return (GCBENUM) this->headerSetting;
}

const GCBENUM GCBSTYLE::getTextSetting(){
    // Alignment of text LEFT, CENTER or RIGHT
    return (GCBENUM) this->textSetting;
}

const GCBENUM GCBSTYLE::getStringSetting(){
    // Whether a displayed string is repeated or printed only once
    return (GCBENUM) this->stringSetting;
}

const WORD GCBSTYLE::getColourSetting(){
    WORD colour;
    if(this->colourSetting == DEFAULT) colour = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
    return colour;
}

void GCBSTYLE::setHeaderSetting(GCBENUM setting){
    this->headerSetting = setting;
}
void GCBSTYLE::setTextSetting(GCBENUM setting){
    this->textSetting = setting;
}
void GCBSTYLE::setStringSetting(GCBENUM setting){
    this->stringSetting = setting;
}

void GCBSTYLE::setMenuSetting(GCBENUM setting){
    this->menuSetting = setting;
}

void GCBSTYLE::setColourSetting(WORD setting){
    this->colourSetting = setting;
}

void GCBSTYLE::resetToDefaults(){
    this->headerSetting = this->DEFAULT_HEADER;
	this->textSetting = this->DEFAULT_TEXT;
    this->stringSetting = this->DEFAULT_STRING;
    this->menuSetting = this->DEFAULT_MENU;
    this->colourSetting = this->DEFAULT_COLOUR;
}