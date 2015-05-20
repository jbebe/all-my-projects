#ifdef _WIN32
	
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	
	enum WIN_CONSOLE_COLOR {
		CONSOLE_BLACK = 0,
		CONSOLE_DARKBLUE, 
		CONSOLE_DARKGREEN, 
		CONSOLE_DARKCYAN, 
		CONSOLE_DARKRED, 
		CONSOLE_DARKMAGENTA, 
		CONSOLE_DARKYELLOW,
		CONSOLE_GREY, 
		CONSOLE_DARKGREY,
		CONSOLE_BLUE, 
		CONSOLE_GREEN, 
		CONSOLE_CYAN, 
		CONSOLE_RED, 
		CONSOLE_MAGENTA, 
		CONSOLE_YELLOW,
		CONSOLE_WHITE
	};

	enum WIN_CURSOR_STYLE {
		CURSOR_STYLE_NONE = 0, 
		CURSOR_STYLE_BLOCK = 100, 
		CURSOR_STYLE_NORMAL = 20
	};

	static HANDLE __hStdOut = NULL;

	void __check_console_handle(void)
	{
		if (__hStdOut == NULL)
		{
			__hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		}
	}

	int SetConsoleColor(
		enum WIN_CONSOLE_COLOR foreground, 
		enum WIN_CONSOLE_COLOR background
	){
		__check_console_handle();
		return (int)SetConsoleTextAttribute(
			__hStdOut, 
			(background<<4)|foreground
		);
	}

	int SetConsoleCoord(int x, int y)
	{
		COORD xy = {x, y};
		__check_console_handle();
		return (int)SetConsoleCursorPosition(__hStdOut, xy);
	}
	
	int ClearConsoleScreen(void)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD startcrd = {0, 0};
		__check_console_handle();
		if (GetConsoleScreenBufferInfo(__hStdOut, &csbi))
		{
			DWORD dwConSize = 
				(csbi.srWindow.Right+1)*(csbi.srWindow.Bottom+1);
			FillConsoleOutputCharacter(
				__hStdOut, ' ', 
				dwConSize, 
				startcrd, 
				NULL
			);
			FillConsoleOutputAttribute(
				__hStdOut, 
				csbi.wAttributes, 
				dwConSize, 
				startcrd, 
				NULL
			);
			SetConsoleCursorPosition(__hStdOut, startcrd);
			return 1;
		}
		return 0;
	}

	void SetCursorStyle(enum WIN_CURSOR_STYLE style)
	{
		CONSOLE_CURSOR_INFO CursorInfo;
		__check_console_handle();
		CursorInfo.dwSize = (DWORD)style;
		CursorInfo.bVisible = (BOOL)(style != CURSOR_STYLE_NONE);
		SetConsoleCursorInfo (__hStdOut, &CursorInfo);
	}
	/*
	void __test_console(void)
	{
		int i = 65;
		__check_console_handle();
		SetConsoleCoord(35, 10);
		for (; i < 81; ++i)
		{
			SetConsoleColor(
				(enum WIN_CONSOLE_COLOR)(i-65), 
				(enum WIN_CONSOLE_COLOR)(80-i)
			);
			WriteConsole(__hStdOut, &i, 1, NULL, NULL);
		}
		ClearConsoleScreen();
		SetConsoleCoord(40, 10);
		SetCursorStyle(CURSOR_STYLE_BLOCK);
	}
	*/
	#endif

#if defined(unix) || defined(__unix__) || defined(__unix)
	#ifndef _INC_STDIO
	#include <stdio.h>
	#endif
	
	enum LINUX_CONSOLE_COLOR {
		CONSOLE_BLACK = 0,
		CONSOLE_DARKRED, 
		CONSOLE_DARKGREEN, 
		CONSOLE_DARKYELLOW, 
		CONSOLE_DARKBLUE, 
		CONSOLE_DARKMAGENTA, 
		CONSOLE_DARKCYAN, 
		CONSOLE_GREY, 
		CONSOLE_DARKGREY, 
		CONSOLE_RED, 
		CONSOLE_GREEN, 
		CONSOLE_YELLOW, 
		CONSOLE_BLUE, 
		CONSOLE_MAGENTA, 
		CONSOLE_CYAN, 
		CONSOLE_WHITE
	};
	
	enum LINUX_CURSOR_STYLE {
		CURSOR_STYLE_NONE = 0, 
		CURSOR_STYLE_BLOCK = 1
	};
	
	void SetConsoleColor(
		enum LINUX_CONSOLE_COLOR foreground, 
		enum LINUX_CONSOLE_COLOR background
	){
		if (foreground > 7)
		{
			printf("\x1b[3%d;9%dm", foreground-8, foreground-8);
		}
		else
		{
			printf("\x1b[3%dm", foreground);
		}
		if (background > 7)
		{
			printf("\x1b[4%d;10%dm", background-8, background-8);
		}
		else
		{
			printf("\x1b[4%dm", background);
		}
	}
	
	void SetConsoleCoord(int x, int y)
	{
		printf("\033[%d;%dH", y, x);
	}
	
	void ClearConsoleScreen(void)
	{
		printf("\033[2J");
	}
	
	void SetCursorStyle(enum LINUX_CURSOR_STYLE style)
	{
		printf("\033[?25%c", style == CURSOR_STYLE_NONE ? 'l' : 'h');
	}
	/*
	void __test_console(void)
	{
		int i = 0;
		for (; i < 16; ++i)
		{
			SetConsoleColor(
				(enum LINUX_CONSOLE_COLOR)i, 
				(enum LINUX_CONSOLE_COLOR)(15-i)
			);
			putchar(i+'A');
		}
		SetConsoleCoord(30,5);
	}
	*/
#endif
