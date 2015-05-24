#define UNICODE

#include "vnDataTypes.h"
#include "vnError.h"
#include "Snake.h"
#include "Monster.h"
#include "SmallMonster.h"
#include "BigMonster.h"
#include "BossMonster.h"
#include "Food.h"
#include "vnScreen.h"
#include "vnSurface.h"
#include "vnWindow.h"
#include "vnSound.h"
#include "vnSoundPlayer.h"
#include "MenuItems.h"
#include "AboutDlg.h"
#include "HelpDlg.h"
#include "resource1.h"
#include <gdiplus.h>
#include <vector>
#include <windows.h>
#include <ostream>
#include <fstream>

using namespace Gdiplus;

#pragma once
/* snake game states */
enum vnGameState
{
 vnGameRunning           = 1,
 vnGameLost                 ,
 vnGameSplash               ,
 vnGameMenu                 ,
 vnGameLevelStarting        ,
 vnGameLevelComplete        ,
 vnGameComplete             ,
 vnGameQuit                 ,
 vnGameSmallMenu            ,

 vnGameStateForceDWord   = 0xFFFFFFFF
};
/********** 方晶 ***************
 * 动画载入标志(做Flag数组下标) *
 ********************************/
enum vnAnimationFlag
{
	LevelStart        =0,//每一关开始
	A_Attack            ,//置位时输出攻击动画
	A_OpenTheDoor	    ,//置位时输出开门动画
	A_LevelComplete		,
	A_GameComplete		,
	A_GameLost			,
	A_GameQuit			,
	DoorOpen	        ,//门开了
	Suspend				,//暂停
	LoadGame
};

class vnGame
{
public:
	vnGame(void);
	~vnGame(void);

	//initilization of game
	void Start(HINSTANCE hInstance, HWND hWindow);

	// render routine
	void Render(void);
	//process routine
	vnBool32 Process(vnReal32 fStep);

private:
	//Handles
	HWND m_hWindow;
	HINSTANCE m_hInstance;
	//game information
	vnGameState m_eGameState;
	vnReal32 m_fDelta;
	vnTimer  m_kTimer;

	bool m_bGameFlag[20];//方晶//存储一些标志位
	int m_iFrameSpeed;//方晶//指示当前游戏的帧数
	//int m_iBulletType;//方晶//当前玩家控制子弹类型
	//level information
	vnUInt32 m_iCurrentLevel;


	//游戏构成元素
	Snake snake;
	vector<Monster *> monsters;
	Food food;
	Bitmap *mapBitmap;

	vnSurface * m_Wall;
	vnSurface * m_SnakeHead[5];
	vnSurface * m_SnakeBody;
	vnSurface * m_SnakeTail;
	vnSurface * m_Gate;
	vnSurface * m_Load;
	vnSurface * m_Menu1;
	vnSurface * m_Menu2;
	vnSurface * m_Food;
	vnSurface * m_Monster[3][3];
	vnSurface * m_Icebox;
	vnSurface * m_Firebox;
	
	//vnWrappedMap * m_WrappedMap;*/
	//vnSurface * m_Splash;
	//vnSurface * m_Title;
	

	//声音
	vnSoundPlayer m_kSoundPlayer;
	vnSound  m_kSoundBg1;
	vnSound  m_kSoundBg2;
	vnSound  m_kSoundMenu;
	vnSound  m_kSoundLost;
	vnSound  m_kSoundLvStart;
	vnSound  m_kSoundGong;
	vnSound  m_kSoundFire;
	vnSound  m_kSoundIce;
	vnSound  m_kSoundEat;
	vnSound  m_kSoundLogo;
	vnSound  m_kSoundCollide;
	vnSound  m_kSoundNormal;
	vnSound  m_kSoundHaha;
	vnSound  m_kSoundOpenTheDoor;

	//菜单
	MenuItems m_kMenu;
	MenuItems m_kSmallMenu;

	int m_loopFlag;


#ifdef _DEBUG
	int x, y;
#endif
	
public:
	// process routine
	void ProcessFrame(vnReal32 fStep);
	void ProcessLostGame(vnReal32 fStep);
	void ProcessSplash(vnReal32 fStep);
	void ProcessMenu(vnReal32 fStep);
	void ProcessLevelStarting(vnReal32 fStep);
	void ProcessLevelComplete(vnReal32 fStep);
	void ProcessComplete(vnReal32 fStep);
	void ProcessSmallMenu(vnReal32 fStep);

	//Render routine
	void RenderFrame(void);// 渲染游戏进行中的画面
	void RenderLostGame(void);// 渲染游戏失败后的画面	
	void RenderSplash(void);// 渲染Splash	
	void RenderMenu(void);// 渲染菜单	
	void RenderSmallMenu(void);// 渲染小菜单（游戏进行中的左上角弹出式菜单）	
	void RenderLevelStarting(void);// 渲染新关卡开始的画面	
	void RenderLevelComplete(void);// 渲染关卡结束的画面	
	void RenderGameComplete(void);// 渲染游戏结束的画面	
	void RenderQuit(void);// 渲染离开游戏的画面


	//占位程序
	void dummy(wstring);
};
