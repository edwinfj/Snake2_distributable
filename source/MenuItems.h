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
	void addItem(wstring title);       //��Ӳ˵���
	int  getActive(void);              //���ص�ǰѡ�в˵���
	void onKeyUp(void);                //�յ�UP��
	void onKeyDown(void);              //�յ�DOWN��
	void Render(HDC buffer);           //��Ⱦ�˵�

private:
	vector<wstring> ItemTitle;
	int activePos;

};
