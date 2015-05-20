#ifndef _INC_WINDOWS
#include <windows.h>
#endif

// Includes
#include "globals.h"
#include "screen.h"
#include "sound.h"

// Function declarations
VOID registerWnd(WNDCLASSEX *, HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;
	
	registerWnd(&wc, hInstance);

	// disable cursor
	ShowCursor(FALSE);
	// get screenshot
	getImage();

	hwnd = CreateWindowEx(
		WS_EX_TOOLWINDOW | /*WS_EX_LAYERED |WS_EX_TRANSPARENT|*/WS_EX_TOPMOST,
		wndTitle, "",
		WS_POPUP | WS_VISIBLE | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wndRect.right, wndRect.bottom,
		NULL, NULL, hInstance, NULL
		);

	// transparency
	//SetLayeredWindowAttributes(hwnd, 0x00ff0000, 0, LWA_COLORKEY);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//Sleep(1000); // wait 1 sec
			//SendMessage(hwnd, WM_PAINT, 0, 0);
		}
	}
	return msg.wParam;
}

VOID registerWnd(WNDCLASSEX *wcPtr, HINSTANCE hInstance) {
	wcPtr->cbSize = sizeof(WNDCLASSEX);
	wcPtr->style = 0;
	wcPtr->lpfnWndProc = WndProc;
	wcPtr->cbClsExtra = 0;
	wcPtr->cbWndExtra = 0;
	wcPtr->hInstance = hInstance;
	wcPtr->hIcon = NULL;
	wcPtr->hCursor = LoadCursor(NULL, IDC_ARROW);
	wcPtr->hbrBackground = 0;//(HBRUSH)(COLOR_WINDOW+1);
	wcPtr->lpszMenuName = NULL;
	wcPtr->lpszClassName = wndTitle;
	wcPtr->hIconSm = NULL;
	RegisterClassEx(wcPtr);
}

static bool once = true;
// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, wndRect.right, wndRect.bottom, SWP_SHOWWINDOW);
	switch (msg) {
	/*
	case WM_NCHITTEST:
		return HTTRANSPARENT;
		break;
	*/
	case WM_PAINT:
		if (once == true) {
			showFuckedUpScreen(hwnd);
			playNoise();
			Sleep(4000);
			SendMessage(hwnd, WM_SYSCOMMAND, SC_MONITORPOWER, /* turn off ? */ true ? 2 : -1);
			PlaySound(NULL, NULL, SND_NODEFAULT);
			once = false;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_LBUTTONDOWN:
	case WM_DESTROY:
		SendMessage(hwnd, WM_SYSCOMMAND, SC_MONITORPOWER, /* turn off ? */ false ? 2 : -1);
		releaseScreenResources();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}