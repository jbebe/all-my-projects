#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

//#define DEBUG_MODE

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

COORD 
	CURSOR			= {0, 0},
	SELECTION[]		= { {0, 0}, {0, 0} };

FILE 
	*DOCUMENT		= NULL;

int	
	WIDTH,					/* 1-80 */
	HEIGHT,					/* 1-60 */
	BUFFER_WIDTH	= 0,	/* 1-80 */
	BUFFER_HEIGHT	= 0,	/* 1-MAXINT */
	INPUT_KEY,				/* 0-255 */
	ACTUAL_VPOS		= 0,	/* 0-MAXINT */
	MAX_VPOS		= 0,	/* 0-MAXINT */
	RUN				= 1,	/* 0,1 */
	INPUT_MOD		= 0,	/* 0,1 */
	UNSAVED			= 0,	/* 0,1 */
	SELECTION_STATE	= 0,	/* 0,1 */
	RAND;					/* 0-9 */

unsigned char
	**BUFFER,
	*CLIPBOARD,
	*FILENAME		= NULL;

#include "system.h"
#include "screen.h"
#include "buffer.h"
#include "text_handling.h"
#include "key_fn.h"
#include "events.h"

int main(int argc, char **args)
{
	RAND = ((int)time(NULL))%10;
	init_console();
	init_buffer();
	init_clipboard();
	if (argc > 1)
	{
		FILENAME = (unsigned char *)malloc(256*sizeof(char));
		strcpy((char *)FILENAME, args[1]);
		file_to_buffer();
	}
	else 
	{
		MAX_VPOS = 1;
	}
	while (RUN)
	{
		redraw_screen();
#ifdef DEBUG_MODE
		printf("%d", INPUT_KEY);
#endif
		INPUT_KEY = _getch();
		process_key();
	}
	DestroyAndExit("Exiting...");
	return 0;
}
