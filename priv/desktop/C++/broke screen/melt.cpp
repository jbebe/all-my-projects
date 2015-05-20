#ifndef _INC_WINDOWS
#include <windows.h>
#endif

const char Title[] = "_";
RECT rect;
HBITMAP BMPHANDLE = nullptr;
HDC SCREEN_HANDLE = nullptr;
HBITMAP OLDBMPHANDLE = nullptr;
BITMAP IMAGE;
HDC GLOBAL_SCREEN_HANDLE = nullptr;

#include "pixel_manip.h"
#include "printscreen.h"

void getImage(void)
{
	// image
	if (BMPHANDLE		!=	nullptr) free (BMPHANDLE);
	if (SCREEN_HANDLE	!=	nullptr) free (SCREEN_HANDLE);
	if (OLDBMPHANDLE	!=	nullptr) free (OLDBMPHANDLE);

	BMPHANDLE = MakePrintScreen();
	BMPHANDLE = ManipPixels(BMPHANDLE, SCREEN_HANDLE);
	GetObject((HGDIOBJ)BMPHANDLE,sizeof(BITMAP),(LPVOID)&IMAGE);
	SCREEN_HANDLE = CreateCompatibleDC(GLOBAL_SCREEN_HANDLE);
	OLDBMPHANDLE = (HBITMAP)SelectObject(SCREEN_HANDLE, BMPHANDLE);
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, rect.right, rect.bottom, SWP_SHOWWINDOW);
	switch(msg)
	{
	case WM_NCHITTEST:
		return HTTRANSPARENT;
		break;
	case WM_PAINT:
		
		PAINTSTRUCT ps;		 
		GLOBAL_SCREEN_HANDLE = BeginPaint(hwnd,&ps); 
		BitBlt(GLOBAL_SCREEN_HANDLE, 0, 0, IMAGE.bmWidth, IMAGE.bmHeight, SCREEN_HANDLE, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		
		break;
	
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	
	case WM_LBUTTONDOWN:
	case WM_DESTROY:
		// image
		SelectObject(SCREEN_HANDLE,OLDBMPHANDLE);
		DeleteDC(SCREEN_HANDLE);
		DeleteObject(BMPHANDLE);

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = NULL;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = 0;//(HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName	 = NULL;
	wc.lpszClassName = Title;
	wc.hIconSm		 = NULL;
	RegisterClassEx(&wc);


	//ShowCursor(FALSE);

	getImage();

	hwnd = CreateWindowEx(
		WS_EX_TOOLWINDOW|WS_EX_LAYERED|WS_EX_TRANSPARENT|WS_EX_TOPMOST,
		Title, "",
		WS_POPUP|WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		rect.right, rect.bottom,
		NULL, NULL, hInstance, NULL
		);
	
	SetLayeredWindowAttributes(hwnd, 0x00ff0000, 0, LWA_COLORKEY);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	PeekMessage( &Msg, NULL, 0, 0, PM_NOREMOVE);
	
	while (Msg.message != WM_QUIT) 
	{
		if (PeekMessage( &Msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
		else 
		{
			/* run ... */
			Sleep(1000/15);
		}
	}
	return Msg.wParam;
}