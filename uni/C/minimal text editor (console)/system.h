HANDLE hOut;

enum console_color {
	black,
	darkblue, darkgreen, darkcyan, darkred, darkmagenta, darkyellow,
	grey, darkgrey,
	blue, green, cyan, red, magenta, yellow,
	white
};

void init_console()
{
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	CONSOLE_CURSOR_INFO cursor_info;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	/* get screen width/height */
	GetConsoleScreenBufferInfo (hOut, &buffer_info);
	WIDTH = buffer_info.srWindow.Right;
	HEIGHT = buffer_info.srWindow.Bottom;

	/* set cursor size to block */
	cursor_info.dwSize = 100;
	/* cursor_info.bVisible = FALSE; */
	SetConsoleCursorInfo(hOut, &cursor_info);
}

void set_crd(int x, int y)
{
	COORD xy = {x, y};
	SetConsoleCursorPosition(hOut, xy);
}

void set_color(enum console_color fg, enum console_color bg)
{
	SetConsoleTextAttribute(hOut, (bg<<4)|fg);
}

void set_text(unsigned char *string, int length)
{
	WriteConsole(hOut, string, length, NULL, NULL);
}

void set_char(char c)
{
	WriteConsole(hOut, &c, 1, NULL, NULL);
}

void DestroyAndExit(char *problem)
{
	int i;
	free(FILENAME);
	for (i = 0; i < BUFFER_HEIGHT; ++i)
	{
		free(BUFFER[i]);
	}
	free(BUFFER);
	free(CLIPBOARD);
	if (FILENAME != NULL)
	{
		fclose(DOCUMENT);
	}
	set_crd(0,HEIGHT-1);
	printf("\n%s\n", problem);
	set_color(grey, black);
	exit(0);
}
