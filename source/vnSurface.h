#define UNICODE
#include <windows.h>
#include <gdiplus.h>
#include <string>

using namespace std;
using namespace Gdiplus;

#pragma once

class vnSurface
{
public:
	vnSurface(WCHAR * pic);
	vnSurface(void);
	~vnSurface(void);
private:
	Image * img;
public:

	// 返回图形指针
	Image * getImage(void);
	// 从png文件载入图像
	void LoadFromPNG(WCHAR * filename);
};
