#ifndef _INC_WINDOWS
#include <windows.h>
#endif

#include <math.h>
#include <stdlib.h>

HBITMAP ManipPixels(HBITMAP hBmp, HDC hBmpDC){
	HBITMAP RetBmp=NULL;
	if (hBmp){
		HDC BufferDC=CreateCompatibleDC(NULL);	  // DC for Source Bitmap
		if (BufferDC)
		{
			HBITMAP hTmpBitmap = (HBITMAP) NULL;
			if (hBmpDC)
				if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP))
				{
					hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
					SelectObject(hBmpDC, hTmpBitmap);
				}
				HGDIOBJ PreviousBufferObject=SelectObject(BufferDC,hBmp);
				HDC DirectDC=CreateCompatibleDC(NULL); // DC for working
				if (DirectDC)
				{
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
					if (DirectBitmap)
					{
						HGDIOBJ PreviousObject=SelectObject(DirectDC, DirectBitmap);
						BitBlt(DirectDC,0,0,bm.bmWidth,bm.bmHeight,BufferDC,0,0,SRCCOPY);

						int h, w;
						
						for (int i = ( (bm.bmWidth*bm.bmHeight)-1 ); i >= 0; i--)
						{
							h = i%bm.bmHeight;
							w = i%bm.bmWidth;

							if (h*h > 9*w*w || w > 7*bm.bmWidth/8)
							{
								ptPixels[i] = 0x00000000;
							}
							else
							{
								ptPixels[i] = 0x000000ff;
							}
						}

						SelectObject(DirectDC,PreviousObject);
						RetBmp=DirectBitmap;
					}
					DeleteDC(DirectDC);
				}			 
				if (hTmpBitmap)
				{
					SelectObject(hBmpDC, hBmp);
					DeleteObject(hTmpBitmap);
				}
				SelectObject(BufferDC,PreviousBufferObject);
				DeleteDC(BufferDC);
		}
	}
	return RetBmp;
}
