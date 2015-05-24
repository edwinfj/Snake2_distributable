#define UNICODE

#include <vector>
#include <string>
#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;
using namespace std;

#pragma once

class MenuItems
{
public:
	MenuItems(void);
	~MenuItems(void);
	void addItem(wstring title);       //添加菜单项
	int  getActive(void);              //返回当前选中菜单项
	void onKeyUp(void);                //收到UP键
	void onKeyDown(void);              //收到DOWN键
	void Render(HDC buffer);           //渲染菜单

private:
	vector<wstring> ItemTitle;
	int activePos;

};
