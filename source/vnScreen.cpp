#include "vnScreen.h"

vnScreen * vnScreen::m_pkSingleton = NULL;

vnScreen::vnScreen(void)
{
	// Initialize GDI+.
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	m_hWindow = NULL;
	m_iFPS = 0;
	assert(!m_pkSingleton);
	m_pkSingleton = this;
}

vnScreen::~vnScreen(void)
{
	DeleteDC(m_bkground);
	DeleteDC(m_buffer);
	DeleteObject(m_bmpbk);
	DeleteObject(m_bmpbuf);
	ReleaseDC(m_hWindow, m_hdc);

	//ending use of gdiplus
	GdiplusShutdown(m_gdiplusToken);
}

vnError32 vnScreen::Init(HWND hWindow)
{
	//避免重复初始化
	if(m_hWindow != NULL)
		return vnErrorInitScreen;

	m_hWindow = hWindow;       //设置窗口句柄
	
	//获得句柄
	m_hdc = GetDC(hWindow);
	m_bkground = CreateCompatibleDC(m_hdc);
	m_buffer=CreateCompatibleDC(m_hdc);
	//得到一个内存空间
	m_bmpbk = CreateCompatibleBitmap(m_hdc, SCR_WIDTH, SCR_HEIGHT);
	m_bmpbuf = CreateCompatibleBitmap(m_hdc, SCR_WIDTH, SCR_HEIGHT);

	//把空间与句柄对应
	SelectObject(m_bkground, m_bmpbk);
	SelectObject(m_buffer, m_bmpbuf);
	return vnError32(vnNoError);
}

vnError32 vnScreen::Clear(vnUInt8 iRed, vnUInt8 iGreen, vnUInt8 iBlue, vnUInt8 iAlpha)
{
	return vnError32(vnNoError);
}

//start rendering
vnError32 vnScreen::StartFrame(void)
{
	//start rendering
	BitBlt(m_buffer, 0, 0, SCR_WIDTH, SCR_HEIGHT, 
		m_bkground, 0, 0, SRCCOPY);

	return vnError32(vnNoError);
}

//end rendering
vnError32 vnScreen::EndFrame(void)
{
	//end rendering
	BitBlt(m_hdc,0,0,SCR_WIDTH,SCR_HEIGHT,m_buffer,0,0,SRCCOPY);

	//calculate frame per second
	m_kTimer.Update ();
	m_iFPS = (vnUInt32) (1 / m_kTimer.GetDelta ());

	return vnNoError;
}

vnInt32 vnScreen::GetFPS(void)
{
	return m_iFPS;
}

vnScreen * vnScreen::GetSingleton(void)
{
	assert (m_pkSingleton);
	return m_pkSingleton;
}
