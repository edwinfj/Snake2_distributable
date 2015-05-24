#include "vnWindow.h"
#include "vnGame.h"
#include "vnScreen.h"

#ifndef _SNAKEWINDOW_H
#define _SNAKEWINDOW_H

class SnakeGame
{
public:
	SnakeGame(HINSTANCE hInstance, HWND hWindow);
	~SnakeGame(void);

	void Init ();              //初始化

	vnBool32 Frame(void);      //处理帧

private:
	HWND m_hWindow;            //窗口句柄
	HINSTANCE m_hInstance;     //实例句柄

	vnScreen m_kScreen;        
	vnGame m_kGame;
};

#endif
