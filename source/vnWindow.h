#include <windows.h>

#pragma once

extern bool	fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default
extern HWND g_hWnd;     //È«¾Ö´°¿Ú¾ä±ú
extern bool g_keys[256];  //Array Used For The Keyboard Routine
extern bool g_WindowActive; // Window Active Flag Set To TRUE By Default

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam);
BOOL CreateSnakeGame(HINSTANCE hInstance, char* title,
	int width, int height, int bits, bool fullscreenflag);
