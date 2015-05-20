#pragma once

#ifndef _INC_WINDOWS
#include <windows.h>
#endif

#include "globals.h"

HBITMAP BMPHANDLE = nullptr;
HDC SCREEN_HANDLE = nullptr;
HBITMAP OLDBMPHANDLE = nullptr;
BITMAP IMAGE;
HDC GLOBAL_SCREEN_HANDLE = nullptr;

void getImage(void);
HBITMAP fuckUpPixels(HBITMAP, HDC);
HBITMAP printScreen();

void showFuckedUpScreen(HWND hwnd) {
	PAINTSTRUCT ps;
	GLOBAL_SCREEN_HANDLE = BeginPaint(hwnd, &ps);
	BitBlt(GLOBAL_SCREEN_HANDLE, 0, 0, IMAGE.bmWidth, IMAGE.bmHeight, SCREEN_HANDLE, 0, 0, SRCCOPY);
	EndPaint(hwnd, &ps);
}

void getImage(void) {
	// image
	if (BMPHANDLE != nullptr) free(BMPHANDLE);
	if (SCREEN_HANDLE != nullptr) free(SCREEN_HANDLE);
	if (OLDBMPHANDLE != nullptr) free(OLDBMPHANDLE);

	BMPHANDLE = printScreen();
	BMPHANDLE = fuckUpPixels(BMPHANDLE, SCREEN_HANDLE);
	GetObject((HGDIOBJ)BMPHANDLE, sizeof(BITMAP), (LPVOID)&IMAGE);
	SCREEN_HANDLE = CreateCompatibleDC(GLOBAL_SCREEN_HANDLE);
	OLDBMPHANDLE = (HBITMAP)SelectObject(SCREEN_HANDLE, BMPHANDLE);
}

HBITMAP fuckUpPixels(HBITMAP hBmp, HDC hBmpDC) {
	HBITMAP RetBmp = NULL;
	if (hBmp) {
		HDC BufferDC = CreateCompatibleDC(NULL);	  // DC for Source Bitmap
		if (BufferDC) {
			HBITMAP hTmpBitmap = (HBITMAP)NULL;
			if (hBmpDC)
				if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP)) {
				hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
				SelectObject(hBmpDC, hTmpBitmap);
				}
			HGDIOBJ PreviousBufferObject = SelectObject(BufferDC, hBmp);
			HDC DirectDC = CreateCompatibleDC(NULL); // DC for working
			if (DirectDC) {
				BITMAP bm;
				GetObject(hBmp, sizeof(bm), &bm);
				BITMAPINFO RGB32BitsBITMAPINFO;
				ZeroMemory(&RGB32BitsBITMAPINFO, sizeof(BITMAPINFO));
				RGB32BitsBITMAPINFO.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				RGB32BitsBITMAPINFO.bmiHeader.biWidth = bm.bmWidth;
				RGB32BitsBITMAPINFO.bmiHeader.biHeight = bm.bmHeight;
				RGB32BitsBITMAPINFO.bmiHeader.biPlanes = 1;
				RGB32BitsBITMAPINFO.bmiHeader.biBitCount = 32;
				UINT * ptPixels;
				HBITMAP DirectBitmap = CreateDIBSection(DirectDC,
					(BITMAPINFO *)&RGB32BitsBITMAPINFO,
					DIB_RGB_COLORS,
					(void **)&ptPixels,
					NULL, 0);
				if (DirectBitmap) {
					HGDIOBJ PreviousObject = SelectObject(DirectDC, DirectBitmap);
					BitBlt(DirectDC, 0, 0, bm.bmWidth, bm.bmHeight, BufferDC, 0, 0, SRCCOPY);

					for (int i = ((bm.bmWidth*bm.bmHeight) - 1); i >= 0; i--) {
						int h = i%bm.bmHeight;
						int w = i%bm.bmWidth;
						//ptPixels[i] = (h % (w + 1)) ^ ptPixels[2 * i / 3];
						ptPixels[i] = ((ptPixels[i / 2] ^ 0x00ff0000) & ptPixels[(i + 10) / 2]) | 0x00007700;
					}

					SelectObject(DirectDC, PreviousObject);
					RetBmp = DirectBitmap;
				}
				DeleteDC(DirectDC);
			}
			if (hTmpBitmap) {
				SelectObject(hBmpDC, hBmp);
				DeleteObject(hTmpBitmap);
			}
			SelectObject(BufferDC, PreviousBufferObject);
			DeleteDC(BufferDC);
		}
	}
	return RetBmp;
}

HBITMAP printScreen() {
	HWND hWindow = GetDesktopWindow();
	HDC hdcScreen = GetDC(NULL);
	HBITMAP hbmC;

	GetClientRect(hWindow, &wndRect);

	if ((hbmC = CreateCompatibleBitmap(hdcScreen, wndRect.right, wndRect.bottom)) != NULL) {
		HDC hdcC;
		if ((hdcC = CreateCompatibleDC(hdcScreen)) != NULL) {
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcC, hbmC);
			BitBlt(hdcC, 0, 0, wndRect.right, wndRect.bottom, hdcScreen, 0, 0, SRCCOPY);
			SelectObject(hdcC, hbmOld);
			DeleteDC(hdcC);
		}
	}
	ReleaseDC(hWindow, hdcScreen);
	return hbmC;
}

void releaseScreenResources() {
	SelectObject(SCREEN_HANDLE, OLDBMPHANDLE);
	DeleteDC(SCREEN_HANDLE);
	DeleteObject(BMPHANDLE);
}