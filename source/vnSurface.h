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

	// ����ͼ��ָ��
	Image * getImage(void);
	// ��png�ļ�����ͼ��
	void LoadFromPNG(WCHAR * filename);
};
