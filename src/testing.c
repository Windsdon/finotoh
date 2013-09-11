/*
 * testing.c
 *
 *  Created on: 04/09/2013
 *      Author: Windsdon
 */

#include <stdio.h>
#include "finoto/finoto.h"

int main(int argc, char **argv) {
//	setColor(COLOR_YELLOW | COLOR_FOREGROUND | COLOR_BOLD |  COLOR_UNDERLINE);
	setColorStr("\x2 1fs;");
	printf("Testando\n");
	printf("%d\n", COLOR_CHAR);
	return 0;
}
