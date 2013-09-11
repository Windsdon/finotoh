/*
 * finoto.h
 *
 *  Created on: 04/09/2013
 *      Author: Windsdon
 *
 *
 * Funções de utilidade.
 */

#ifndef FINOTO_H_
#define FINOTO_H_

#include <stdarg.h> //variable number of arguments
#include <string.h>

/////////CONSTANTS//////////////

//colors

#define COLOR_BOLD         0x100
#define COLOR_UNDERLINE    0x200

#define COLOR_FOREGROUND   0x010
#define COLOR_BACKGROUND   0x020

#define COLOR_BLACK        0x001
#define COLOR_RED          0x002
#define COLOR_GREEN        0x003
#define COLOR_YELLOW       0x004
#define COLOR_BLUE         0x005
#define COLOR_MAGENTA      0x006
#define COLOR_CYAN         0x007
#define COLOR_WHITE        0x008

#define COLOR_SET_MASK     0x00F
#define COLOR_DESTINY_MASK 0x0F0
#define COLOR_SPECIAL_MASK 0xF00

#define COLOR_CHAR 2
#define COLOR_TERMINATOR ';'

#define COLOR_BOLD_CHAR 's'
#define COLOR_UNDERLINE_CHAR 'u'
#define COLOR_BACKGROUND_CHAR 'b'
#define COLOR_FOREGROUND_CHAR 'f'


const char validColorCharacters[] = { '0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'b', 'f', 'u' }; //nyi

const char *colorEscape = "\x1b[";

//end of colors

/////////CORE FUNCTIONS PROTOTYPE/////////

void printColor(char *format, ...); //prints with colors. Same syntax as printf
int getColorCharachterLength(char *str, int startingPos); //get the length of
int getTrueLength(char *str); //get the length of the characters that will be printed
void setColorStr(char *colorStr); //set color by translating the color string. Must start with COLOR_CHAR
void setColor(unsigned int colorVal); //set color by the raw color code
void moveCursor(int x, int y);

////////IMPLEMENTATION////////////////////

void setColorStr(char *colorStr) {
	int i;
	int colorVal = 0;

	if(!colorStr[0] == COLOR_CHAR){
		return;
	}

	for(i = 1; colorStr[i] && colorStr[i] != COLOR_TERMINATOR; i++){
		int val;
		switch(colorStr[i]){
		case COLOR_BACKGROUND_CHAR:
			colorVal |= COLOR_BACKGROUND;
			break;
		case COLOR_FOREGROUND_CHAR:
			colorVal |= COLOR_FOREGROUND;
			break;
		case COLOR_BOLD_CHAR:
			colorVal |= COLOR_BOLD;
			break;
		case COLOR_UNDERLINE_CHAR:
			colorVal |= COLOR_UNDERLINE;
			break;
		default:
			val = colorStr[i] - '0';
			if(val < 0 || val > 8){
				break;
			}
			colorVal |= val;
		}
	}

	setColor(colorVal);
}

void setColor(unsigned int colorVal) {
	char color[15];
	char addEnd;

	if(!colorVal){ //color reset
		puts("\x1b[0m");
		return;
	}

	strcpy(color, colorEscape);

	addEnd = 1;
	switch (colorVal & COLOR_SPECIAL_MASK) {
	case COLOR_BOLD:
		strcat(color, "1");
		break;
	case COLOR_UNDERLINE:
		strcat(color, "4");
		break;
	case COLOR_UNDERLINE | COLOR_BOLD:
		strcat(color, "1;4");
		break;
	default:
		addEnd = 0;
	}
	if (colorVal & COLOR_SET_MASK) {
		char colorChar[] = {(colorVal & COLOR_SET_MASK) + '0' - 1, 0}; //:P
		if ((colorVal & COLOR_DESTINY_MASK) == COLOR_BACKGROUND) {
			if (addEnd) {
				strcat(color, ";");
			}
			strcat(color, "4");
		} else {
			if (addEnd) {
				strcat(color, ";");
			}
			strcat(color, "3");
		}

		strcat(color, colorChar);

	}

	strcat(color, "m"); //finish color sequence

	puts(color);
}

void printColor(char *format, ...) {
	//va_list arguments;

	/* Separar usando os identificadores como divisores */

}

int getTrueLength(char *str) {
	int l = 0;
	register unsigned int i;

	for (i = 0; str[i]; i++) {
		if (str[i] == COLOR_CHAR) {
			i += getColorCharachterLength(str, i);
			continue;
		}
		l++;
	}

	return l;
}

int getColorCharachterLength(char *str, int startingPos) {
	register unsigned int i;

	if (str[startingPos] != COLOR_CHAR) {
		return 0;
	}

	for (i = 0; str[i] && str[i] != COLOR_TERMINATOR; i++)
		;

	return i + 1; //include the terminator!
}

void moveCursor(int x, int y){

}

#endif /* FINOTO_H_ */
