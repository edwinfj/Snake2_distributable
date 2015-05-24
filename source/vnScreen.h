#define UNICODE

#include <windows.h>
#include <assert.h>
#include "vnDataTypes.h"
#include "vnError.h"
#include "vnTimer.h"
#include <gdiplus.h>
using namespace Gdiplus;


#pragma once

class vnScreen
{
	enum Param
	{
		SCR_WIDTH    = 640,
		SCR_HEIGHT   = 480
	};
public:
	//constructor/destructor
	vnScreen(void);
	~vnScreen(void);

	//screen manipulation routine
	vnError32 Init(HWND hWindow);
	HDC getBuffer(void){return m_buffer;}
	HDC getBkground(void){return m_bkground;}
	HDC getHDC(void){return m_hdc;}

	//render routine
	vnError32 Clear(vnUInt8 iRed, vnUInt8 iGreen, vnUInt8 iBlue, vnUInt8 iAlpha);
	vnError32 StartFrame(void);
	vnError32 EndFrame(void);

	// Maintenance methods
	vnInt32 GetFPS(void);

	//return singleton instance
	static vnScreen* GetSingleton(void);

private:
	vnUInt32           m_iFPS;
	HWND               m_hWindow;
	vnTimer            m_kTimer;

	//gdi相关
	HDC     m_hdc;        //设备句柄
	HDC     m_buffer;     //缓冲区域句柄
	HDC     m_bkground;   //背景的句柄
	HBITMAP m_bmpbk;      //背景区空间
	HBITMAP m_bmpbuf;     //缓冲区空间
	GdiplusStartupInput m_gdiplusStartupInput;   
	ULONG_PTR           m_gdiplusToken;    

protected:
	static vnScreen * m_pkSingleton;
	
};
