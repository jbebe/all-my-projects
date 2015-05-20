#include <Windows.h>
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow){
	POINT cur;
	
	RECT rc;
	
	double	pi2 = 6.28318530718,
			WIDTH4 = 0.0,
			HEIGHT4 = 0.0;
	
	unsigned short	x = 0, 
					y = 0, 
					xcounter = 0,
					ycounter = 0,
					freq = 1000/60;
	
	GetWindowRect(GetDesktopWindow(), &rc);
	
	WIDTH4 = rc.right/4.0;
	HEIGHT4 = rc.bottom/4.0;
	
	while (1){
		x = (int)(WIDTH4*(cos(xcounter/200.0*pi2)+1)+WIDTH4);
		y = (int)(HEIGHT4*(sin(ycounter/100.0*pi2)+1)+HEIGHT4);
		
		SetCursorPos(x,y);
		
		xcounter += 5;
		ycounter += 5;
		
		if (xcounter==200) xcounter = 0;
		if (ycounter==100) ycounter = 0;
		
		Sleep(freq);
	}
	return 0;
}