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
/********** ���� ***************
 * ���������־(��Flag�����±�) *
 ********************************/
enum vnAnimationFlag
{
	LevelStart        =0,//ÿһ�ؿ�ʼ
	A_Attack            ,//��λʱ�����������
	A_OpenTheDoor	    ,//��λʱ������Ŷ���
	A_LevelComplete		,
	A_GameComplete		,
	A_GameLost			,
	A_GameQuit			,
	DoorOpen	        ,//�ſ���
	Suspend				,//��ͣ
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

	bool m_bGameFlag[20];//����//�洢һЩ��־λ
	int m_iFrameSpeed;//����//ָʾ��ǰ��Ϸ��֡��
	//int m_iBulletType;//����//��ǰ��ҿ����ӵ�����
	//level information
	vnUInt32 m_iCurrentLevel;


	//��Ϸ����Ԫ��
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
	

	//����
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

	//�˵�
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
	void RenderFrame(void);// ��Ⱦ��Ϸ�����еĻ���
	void RenderLostGame(void);// ��Ⱦ��Ϸʧ�ܺ�Ļ���	
	void RenderSplash(void);// ��ȾSplash	
	void RenderMenu(void);// ��Ⱦ�˵�	
	void RenderSmallMenu(void);// ��ȾС�˵�����Ϸ�����е����Ͻǵ���ʽ�˵���	
	void RenderLevelStarting(void);// ��Ⱦ�¹ؿ���ʼ�Ļ���	
	void RenderLevelComplete(void);// ��Ⱦ�ؿ������Ļ���	
	void RenderGameComplete(void);// ��Ⱦ��Ϸ�����Ļ���	
	void RenderQuit(void);// ��Ⱦ�뿪��Ϸ�Ļ���


	//ռλ����
	void dummy(wstring);
};
