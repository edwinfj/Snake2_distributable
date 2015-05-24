#include "SnakeGame.h"
#include "vnWindow.h"


HINSTANCE g_hInstance = NULL;
bool g_WindowActive = true; // Window Active Flag Set To TRUE By Default

 /* "WinMain Vs. main" */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
                    LPSTR lpCmdLine, int nShowCmd)
{
	//创建窗口
	if(!CreateSnakeGame(hInstance, "Snake", 640, 480, 16, false))
		return -1;

	//initialize game
	SnakeGame kGame(hInstance, g_hWnd);
	kGame.Init();

	MSG msg;
	//消息循环
	while(true)
	{
	   if(PeekMessage( &msg, NULL, 0,0 ,PM_REMOVE))
	   {
		   if(msg.message==WM_QUIT)
				break;
		   TranslateMessage(&msg);
		   DispatchMessage(&msg);
	   }
	   else
	   {
		   if(false == kGame.Frame())
			   break;
	   }
	}

	return 0;
}


