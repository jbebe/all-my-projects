#ifndef _INC_WINDOWS
#include <windows.h>
#endif

HBITMAP MakePrintScreen()
{
	HWND hWindow = GetDesktopWindow();
	HDC hdcScreen = GetDC(NULL);
	HBITMAP hbmC;
	
	GetClientRect(hWindow,&rect);
	
	if((hbmC = CreateCompatibleBitmap(hdcScreen,rect.right,rect.bottom)) != NULL)
	{
		HDC hdcC;
		if((hdcC = CreateCompatibleDC(hdcScreen)) != NULL)
		{
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcC,hbmC);
			BitBlt(hdcC,0,0,rect.right,rect.bottom,hdcScreen,0,0,SRCCOPY);
			SelectObject(hdcC,hbmOld);
			DeleteDC(hdcC);
		}
	}
	ReleaseDC(hWindow,hdcScreen);
	return hbmC;
}
