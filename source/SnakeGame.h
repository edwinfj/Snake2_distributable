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

	void Init ();              //��ʼ��

	vnBool32 Frame(void);      //����֡

private:
	HWND m_hWindow;            //���ھ��
	HINSTANCE m_hInstance;     //ʵ�����

	vnScreen m_kScreen;        
	vnGame m_kGame;
};

#endif
