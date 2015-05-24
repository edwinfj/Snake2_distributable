#include "vnGame.h"

vnGame::vnGame(void)
{
	m_eGameState = vnGameSplash;
	m_fDelta = 0;
	m_loopFlag = 0;
	
	//菜单资源设置
	m_kMenu.addItem(L"   Play");
	m_kMenu.addItem(L"   Load");
	m_kMenu.addItem(L"   Help");
	m_kMenu.addItem(L"   About");
	m_kMenu.addItem(L"   Exit");

	m_kSmallMenu.addItem (L"Continue");
	m_kSmallMenu.addItem (L"Restart");
	m_kSmallMenu.addItem (L"  Save");
	m_kSmallMenu.addItem (L"  Help");
	m_kSmallMenu.addItem (L"MainMenu");

	//图像资源加载
	
	m_Load  = new vnSurface(L"image\\splash.png");
	m_Wall  = new vnSurface(L"image\\wall5.png");
	m_Gate  = new vnSurface(L"image\\gate0.png");
	m_Menu1 = new vnSurface(L"image\\menu1.png");
	m_Menu2 = new vnSurface(L"image\\menu2.png");
	m_Food  = new vnSurface(L"image\\food.png");
	m_Monster[2][0]  = new vnSurface(L"image\\smallmonnorm.png");
	m_Monster[2][1]  = new vnSurface(L"image\\smallmonice.png");
	m_Monster[2][2]  = new vnSurface(L"image\\smallmonfire.png");

	m_Monster[1][0]  = new vnSurface(L"image\\bigmonnorm.png");
	m_Monster[1][1]  = new vnSurface(L"image\\bigmonice.png");
	m_Monster[1][2]  = new vnSurface(L"image\\bigmonfire.png");
	m_Monster[0][0]  = new vnSurface(L"image\\bossmonnorm.png");
	m_Monster[0][1]  = new vnSurface(L"image\\bossmonice.png");
	m_Monster[0][2]  = new vnSurface(L"image\\bossmonfire.png");
	
	m_Icebox =new vnSurface(L"image\\icebox.png");
	m_Firebox =new vnSurface(L"image\\firebox.png");
//	m_SnakeHead[0]= new vnSurface;
    m_SnakeHead[1]= new vnSurface(L"image\\SnakeHeadUp.png");
   	m_SnakeHead[2]= new vnSurface(L"image\\SnakeHeadDown.png");
	m_SnakeHead[3]= new vnSurface(L"image\\SnakeHeadLeft.png");
    m_SnakeHead[4]= new vnSurface(L"image\\SnakeHeadRight.png");
	m_SnakeBody= new vnSurface(L"image\\snakebody.png");
	m_SnakeTail= new vnSurface(L"image\\snaketail.png");

}

vnGame::~vnGame(void)
{
	delete m_Load ;
	delete m_Wall;
	delete m_Gate ; 
	delete m_Menu1;
	delete m_Menu2 ;
	delete m_Food ;
	for(int i=1;i<5;i++)
		delete m_SnakeHead[i];
	delete m_SnakeTail;
	//测验代码，可删除
}

void vnGame::Start(HINSTANCE hInstance, HWND hWindow)
{
	m_hInstance = hInstance;
	m_hWindow = hWindow;

	m_kSoundPlayer.Init(hWindow);
	m_kSoundBg1.LoadFromFile("sound\\running.wav");//frame全程音效
	m_kSoundBg2.LoadFromFile("sound\\2.wav");//请无视这个难听的声音
	m_kSoundMenu.LoadFromFile("sound\\menu.wav");//菜单控制音效
	m_kSoundLost.LoadFromFile("sound\\lost.wav");//游戏结束GameLost
	m_kSoundLvStart.LoadFromFile("sound\\lvstart.wav");//载入新关卡levelstart
	m_kSoundGong.LoadFromFile("sound\\newgong.wav");//新游戏levelstart
	m_kSoundFire.LoadFromFile("sound\\fire.wav");//frame火弹
	m_kSoundIce.LoadFromFile("sound\\ice.wav");//frame冰弹
	m_kSoundNormal.LoadFromFile("sound\\normal.wav");//Fream普通弹
	m_kSoundEat.LoadFromFile("sound\\eat.wav");//Frame吃食物
	m_kSoundLogo.LoadFromFile("sound\\logo.wav");//Splash
	m_kSoundCollide.LoadFromFile("sound\\collision.wav");//Frame撞墙
	m_kSoundHaha.LoadFromFile("sound\\haha.wav");//你不会想知道它是干嘛用的
	m_kSoundOpenTheDoor.LoadFromFile("sound\\dooropen.wav");//frame开门音效
	m_kTimer.Update();
}

// render routine
void vnGame::Render(void)
{
	//开始渲染
	vnScreen::GetSingleton()->StartFrame();
	/* Process appropriate state */
	switch (m_eGameState)
	{
	case vnGameRunning:
		RenderFrame ();
		break;
	case vnGameLost:
		RenderLostGame ();
		break;
	case vnGameSplash:
		RenderSplash ();
		break;
	case vnGameMenu:
		RenderMenu ();
		break;
	case vnGameSmallMenu:
		RenderSmallMenu();
		break;
	case vnGameLevelStarting:
		RenderLevelStarting ();
		break;
	case vnGameLevelComplete:
		RenderLevelComplete ();
		break;
	case vnGameComplete:
		RenderGameComplete ();
		break;
	case vnGameQuit:
		RenderQuit();
		break;
	}

	//结束渲染，将缓冲输出到屏幕
	vnScreen::GetSingleton()->EndFrame();
}

//process routine
vnBool32 vnGame::Process(vnReal32 fStep)
{
	m_kTimer.Update();
	fStep = m_kTimer.GetDelta();
	/* Process appropriate state */
	switch (m_eGameState)
	{
	case vnGameRunning:
		ProcessFrame (fStep);
		break;
	case vnGameLost:
		ProcessLostGame (fStep);
		break;
	case vnGameSplash:
		ProcessSplash (fStep);
		break;
	case vnGameMenu:
		ProcessMenu (fStep);
		break;
	case vnGameSmallMenu:
		ProcessSmallMenu(fStep);
		break;
	case vnGameLevelStarting:
		ProcessLevelStarting (fStep);
		break;
	case vnGameLevelComplete:
		ProcessLevelComplete (fStep);
		break;
	case vnGameComplete:
		ProcessComplete (fStep);
		break;
	case vnGameQuit:
		return vnFalse;
		break;
	}
	return vnBool32(vnTrue);
}

void vnGame::ProcessFrame(vnReal32 fStep)
{
	static vnTimer kTimer;
	static vnReal32 fTimer = 0;
	
	m_fDelta += fStep;

	kTimer.Update();

	//fang//running中播放音效
	if(!m_loopFlag)
	{
		m_kSoundBg1.Play(vnTrue);
		m_loopFlag = 1;
	}

	//以下代码请根据需要更改
	//获取键盘
	
	//方晶//攻击动画或开门动画和移动属于同一帧行为
	if(!m_bGameFlag[A_Attack] && !m_bGameFlag[A_OpenTheDoor])
		fTimer += fStep; 
	
	//方晶//不到0.2s，可以读键，但不改变状态
		//暂停时，不改变状态，等待按键
	if((m_bGameFlag[Suspend] || fTimer<0.2f)
		&& !m_bGameFlag[A_Attack]
		&& !m_bGameFlag[A_OpenTheDoor]){
		if(m_fDelta > 0.2f){
			if(!m_bGameFlag[Suspend]){//不在暂停状态
				if(GetAsyncKeyState(VK_ESCAPE) & 0x80000f){//ESC退出
					while(GetAsyncKeyState(VK_ESCAPE) & 0x80000f);//防止连按
					m_fDelta=0;
					m_eGameState=vnGameSmallMenu;
				}
				else if(GetAsyncKeyState('C') & 0x80000f){//C改变子弹
					//while(GetAsyncKeyState('C') & 0x80000f);//防止连按
					m_fDelta=0;
					switch(snake.getBulletType()){
					case B_FIRE_BULLET:
						if(snake.getICEnum()>0){
							snake.setBulletType(B_ICE_BULLET);
							break;
						}
						else{
							snake.setBulletType(B_NORMAL_BULLET);
							break;
						}
					case B_ICE_BULLET:
						snake.setBulletType(B_NORMAL_BULLET);
						break;
					case B_NORMAL_BULLET:
						if(snake.getFIREnum()>0){
							snake.setBulletType(B_FIRE_BULLET);
							break;
						}
						else if(snake.getICEnum()>0){
							snake.setBulletType(B_ICE_BULLET);
							break;
						}
						else{
							snake.setBulletType(B_NORMAL_BULLET);
							break;
						}
					}
				}
				else if(GetAsyncKeyState(VK_SPACE) & 0x80000f){//按空格键暂停
					while(GetAsyncKeyState(VK_SPACE) & 0x80000f);//防止连按
					m_fDelta=0;
					m_bGameFlag[Suspend]=1;
				}
			}
			else if(GetAsyncKeyState(VK_SPACE) & 0x80000f){//暂停恢复
				while(GetAsyncKeyState(VK_SPACE) & 0x80000f);//防止连按
				m_fDelta=0;
				m_bGameFlag[Suspend]=0;
			}
		}
		return;
	}

	//方晶//大于0.2s，刷新状态，允许攻击
	//按下A，输出动画
	if(m_fDelta>0.2f && !m_bGameFlag[A_Attack]
	   && !m_bGameFlag[A_OpenTheDoor]){
		if(GetAsyncKeyState('A') & 0x80000f){
			//while(GetAsyncKeyState('A') & 0x80000f);//防止连按
			m_fDelta=0;
			if(snake.getBodyNum()>3){
				switch(snake.getBulletType()){//播放攻击音效
				case B_FIRE_BULLET:
					m_kSoundFire.Play(vnFalse);
					break;
				case B_ICE_BULLET:
					m_kSoundIce.Play(vnFalse);
					break;
				case B_NORMAL_BULLET:
					m_kSoundNormal.Play(vnFalse);
					break;
				}
				snake.DeleteBody(); //蛇身-1（包括普通子弹）
				m_bGameFlag[A_Attack]=1;
				return;
			}
		}//下面改变蛇头方向
		else if(GetAsyncKeyState(VK_UP) & 0x80000f){
			//while(GetAsyncKeyState(VK_UP) & 0x80000f);//防止连按
			m_fDelta=0;
			snake.setHeadDirect(DIR_UP);
		}
		else if(GetAsyncKeyState(VK_DOWN) & 0x80000f){
			//while(GetAsyncKeyState(VK_DOWN) & 0x80000f);//防止连按
			m_fDelta=0;
			snake.setHeadDirect(DIR_DOWN);
		}
		else if(GetAsyncKeyState(VK_LEFT) & 0x80000f){
			//while(GetAsyncKeyState(VK_LEFT) & 0x80000f);//防止连按
			m_fDelta=0;
			snake.setHeadDirect(DIR_LEFT);
		}
		else if(GetAsyncKeyState(VK_RIGHT) & 0x80000f){
			//while(GetAsyncKeyState(VK_RIGHT) & 0x80000f);//防止连按
			m_fDelta=0;
			snake.setHeadDirect(DIR_RIGHT);
		}
	}

	using namespace Map; 

	//方晶//攻击后的状态检测//begin
	if(m_bGameFlag[A_Attack]){
		m_bGameFlag[A_Attack]=0;

		Body head=snake.getHead();
		Direction direct=snake.getHeadDirect();	
		int t;
		Position pos,m_pos;

		switch(direct){
		case DIR_UP:
			for(t=head.y-1;
				g_Map[head.x][t]!=M_WALL && 
				g_Map[head.x][t]!=M_MONSTER &&
				g_Map[head.x][t]!=M_DOOR &&
				g_Map[head.x][t]!=M_FOOD && //打上食物
				t>=0;
				g_Map[head.x][t]=M_PASSAGE,t--);

			pos.x=head.x; pos.y=t;
			if(g_Map[pos.x][pos.y]==M_FOOD){//食物更新
				food.FoodInit();
			}
			if(g_Map[pos.x][pos.y]==M_MONSTER){//向上撞击怪物
				Monster* p;
				for(vector<Monster*>::iterator iter=monsters.begin();
					iter<monsters.end();iter++){
					p=(Monster*)(*iter);
					m_pos=p->getPosition();
					if(m_pos.x==pos.x && m_pos.y==pos.y){
						p->gatAttack(snake.getBulletType());
						if(p->isDead()){
							p->generateBulletBox();
							delete p;
							monsters.erase(iter);
						}
					}
				}
			}
			break;
		case DIR_DOWN:
			for(t=head.y+1;
				g_Map[head.x][t]!=M_WALL && 
				g_Map[head.x][t]!=M_MONSTER &&
				g_Map[head.x][t]!=M_DOOR &&
				g_Map[head.x][t]!=M_FOOD && //打上食物
				t<MAP_HEIGHT;
				g_Map[head.x][t]=M_PASSAGE,t++);

			pos.x=head.x; pos.y=t;
			if(g_Map[pos.x][pos.y]==M_FOOD){//食物更新
				food.FoodInit();
			}
			if(g_Map[pos.x][pos.y]==M_MONSTER){//向下撞击怪物
				Monster* p;
				for(vector<Monster*>::iterator iter=monsters.begin();
					iter<monsters.end();iter++){
					p=(Monster*)(*iter);
					m_pos=p->getPosition();
					if(m_pos.x==pos.x && m_pos.y==pos.y){
						p->gatAttack(snake.getBulletType());
						if(p->isDead()){
							p->generateBulletBox();
							delete p;
							monsters.erase(iter);
						}
					}
				}
			}
			break;
		case DIR_LEFT:
			for(t=head.x-1;
				g_Map[t][head.y]!=M_WALL && 
				g_Map[t][head.y]!=M_MONSTER &&
				g_Map[t][head.y]!=M_DOOR &&
				g_Map[t][head.y]!=M_FOOD && //打上食物
				t>=0;
				g_Map[t][head.y]=M_PASSAGE,t--);

			pos.x=t; pos.y=head.y;
			if(g_Map[pos.x][pos.y]==M_FOOD){//食物更新
				food.FoodInit();
			}
			if(g_Map[pos.x][pos.y]==M_MONSTER){//向左撞击怪物
				Monster* p;
				for(vector<Monster*>::iterator iter=monsters.begin();
					iter<monsters.end();iter++){
					p=(Monster*)(*iter);
					m_pos=p->getPosition();
					if(m_pos.x==pos.x && m_pos.y==pos.y){
						p->gatAttack(snake.getBulletType());
						if(p->isDead()){
							p->generateBulletBox();
							delete p;
							monsters.erase(iter);
						}
					}
				}
			}
			break;
		case DIR_RIGHT:
			for(t=head.x+1;
				g_Map[t][head.y]!=M_WALL && 
				g_Map[t][head.y]!=M_MONSTER &&
				g_Map[t][head.y]!=M_DOOR &&
				g_Map[t][head.y]!=M_FOOD && //打上食物
				t<MAP_WIDTH;
				g_Map[t][head.y]=M_PASSAGE,t++);
			
			pos.x=t; pos.y=head.y;
			if(g_Map[pos.x][pos.y]==M_FOOD){//食物更新
				food.FoodInit();
			}
			if(g_Map[pos.x][pos.y]==M_MONSTER){//向右撞击怪物
				Monster* p;
				for(vector<Monster*>::iterator iter=monsters.begin();
					iter<monsters.end();iter++){
					p=(Monster*)(*iter);
					m_pos=p->getPosition();
					if(m_pos.x==pos.x && m_pos.y==pos.y){
						p->gatAttack(snake.getBulletType());
						if(p->isDead()){
							p->generateBulletBox();
							delete p;
							monsters.erase(iter);
						}
					}
				}
			}
			break;
		}
		snake.DeleteBullet(); //特殊子弹数量-1（如果有）//会改变子弹状态，所以放在所有判断之后
		//方晶//判断是否要开门
		if(monsters.size()==0 && !m_bGameFlag[DoorOpen]){
			m_kSoundOpenTheDoor.Play(vnFalse);//播放开门音效
			m_bGameFlag[A_OpenTheDoor]=true;
			return; //方晶//如果是，先载入动画
		}
	}

	if(m_bGameFlag[A_OpenTheDoor]){//方晶//开门动画之后，把门打开
		m_bGameFlag[A_OpenTheDoor]=false;
		m_bGameFlag[DoorOpen]=true;
	}
	//方晶//攻击后的状态检测//end

	//方晶//通用状态改变//begin
	m_iFrameSpeed=m_iFrameSpeed%6+1;
	//if(food.getDeltaTime()>1.0f)
	//	food.FoodInit();	//食物时间到，改变位置//不按照时间更新
	Body tail=snake.Move(); //蛇移动
	Monster *p; //怪物移动
	for(int i=0;i<(int)monsters.size();i++){
		p=(Monster *)(monsters[i]);
		if(!(m_iFrameSpeed % (p->getMoveSpeedConstant())))
			p->setPosition();
	}
	//方晶//通用状态改变//end

	//方晶//通用状态检测//begin
	Body pos=snake.getHead();
	if(snake.isDead())//蛇撞上自己
	{
		m_eGameState=vnGameLost;
		//wangm_bGameFlag[Suspend]=1;
	}
	if(g_Map[pos.x][pos.y]==M_FOOD){//方晶//蛇吃食物
		m_kSoundEat.Play(vnFalse);//播放音效
		snake.AddBody(tail);
		food.FoodInit();
	}
	if(g_Map[pos.x][pos.y]==M_FIREBOX){//方晶//蛇吃火弹
		m_kSoundEat.Play(vnFalse);//播放音效
		snake.setFIREnum();
		snake.setBulletType(B_FIRE_BULLET);
		g_Map[pos.x][pos.y]=M_PASSAGE;
	}
	if(g_Map[pos.x][pos.y]==M_ICEBOX){//方晶//蛇吃冰弹
		m_kSoundEat.Play(vnFalse);//播放音效
		snake.setICEnum();
		snake.setBulletType(B_ICE_BULLET);
		g_Map[pos.x][pos.y]=M_PASSAGE;
	}
	//蛇撞上墙或关着的门或怪物
	if(g_Map[pos.x][pos.y]==M_WALL || g_Map[pos.x][pos.y]==M_MONSTER 
		|| (g_Map[pos.x][pos.y]==M_DOOR && !m_bGameFlag[DoorOpen])){
		snake.DeleteBody();//身体-1
		if(snake.isDead()){//判断蛇是否死亡
			m_eGameState=vnGameLost;
			//wangm_bGameFlag[Suspend]=1;
		}
		else if(!snake.ResetHead()){//移动头的位置	
			m_eGameState=vnGameLost;
			//wangm_bGameFlag[Suspend]=1;
		}//蛇被卡死
		else{
			m_kSoundCollide.Play(vnFalse);//如果没死，则播放音效
		}
	}
	if(m_bGameFlag[DoorOpen] && g_Map[pos.x][pos.y]==M_DOOR)
		m_eGameState=vnGameLevelComplete;
	//方晶//通用状态检测//end
				
	fTimer=0;//一帧结束，帧内计时器重启
}

void vnGame::ProcessLostGame(vnReal32 fStep)
{
}

void vnGame::ProcessSplash(vnReal32 fStep)
{
}

void vnGame::ProcessMenu(vnReal32 fStep)
{
	/*if(!m_loopFlag)
	{
		m_kSoundBg1.Play(vnTrue);
		m_loopFlag = 1;
	}*///Menu内部不放音乐
	m_kSoundBg1.Stop();
	m_fDelta += fStep;
	//键盘延时
	if(m_fDelta > 0.2f)
	{
		if(GetAsyncKeyState(VK_UP) & 0x80000f)
		{
			m_kMenu.onKeyUp();
			m_kSoundMenu.Play(vnFalse);
		}
		if(GetAsyncKeyState(VK_DOWN) & 0x80000f)
		{
			m_kMenu.onKeyDown();
			m_kSoundMenu.Play(vnFalse);
		}
		if(GetAsyncKeyState(VK_RETURN) & 0x80000f)
		{
			switch(m_kMenu.getActive())
			{
			case 0: //Play
				m_loopFlag = 0;
				m_iCurrentLevel = 1;
				m_bGameFlag[LoadGame]=false;
				//m_kSoundBg1.Stop();
				snake.TotalInit();
				m_eGameState = vnGameLevelStarting;
				break;
			case 1: //Load
			if(true){
				ifstream inputfile("save\\data");
				int t;
				inputfile>>t;
				inputfile.close();
				if(t==1000){
					//m_kSoundBg1.Stop();
					m_loopFlag = 0;
					m_bGameFlag[LoadGame]=true;
					m_eGameState = vnGameLevelStarting;
				}
				break;
			}
			case 2: //Help
				DialogBox (m_hInstance, MAKEINTRESOURCE(IDD_HELP), m_hWindow, HelpDlgProc);
				break;
			case 3: //About 
				DialogBox (m_hInstance, MAKEINTRESOURCE(IDD_ABOUT), m_hWindow, AboutDlgProc);
				break;
			case 4: //Exit
				m_loopFlag = 0;
				//m_kSoundBg1.Stop();
				m_eGameState = vnGameQuit;
				break;
			}
		}
		m_fDelta = 0;
	}
}

void vnGame::ProcessLevelStarting(vnReal32 fStep)
{                     
	/**************** 方晶 *********************
	 *  我的想法是，在这里动画载入标志位职位+   *
	 *	设置地图信息(map[]、三种怪物的数量)     *  
	*********************************************/

	//方晶//动画标志清零
	m_iFrameSpeed=1;
	monsters.clear();//将monsters容器清空
	using  namespace Map;
	
	if(m_bGameFlag[LoadGame]){//载入初始化
		m_bGameFlag[A_Attack]=false;
		m_bGameFlag[A_OpenTheDoor]=false;
		m_bGameFlag[A_GameComplete]=false;
		m_bGameFlag[A_LevelComplete]=false;
		m_bGameFlag[A_GameLost]=false;
		m_bGameFlag[A_GameQuit]=false;
		
		ifstream inputfile("save\\data");
		int t,tx,ty;
		inputfile>>t;//将标志位1000去除
		for(int i=0;i<Map::MAP_WIDTH;i++){    //地图信息初始化
			for(int j=0;j<Map::MAP_HEIGHT;j++){
				inputfile>>t;
				Map::g_Map[i][j]=t;
			}
		}
		inputfile>>tx>>ty;//food初始化
		food.setPosition(tx,ty);
		Monster* p_mon;
		inputfile>>t;//怪物数量
		for(int i=0;i<t;i++){
			int Health,RemainTime,MoveSpeed,BodyMorph;
			inputfile>>Health>>BodyMorph>>RemainTime>>tx>>ty>>MoveSpeed;
			switch(MoveSpeed){//根据MoveSpeed判断怪物类型
			case 1:
				p_mon=(Monster*)(new BossMonster(Health, (BodyMorphism)BodyMorph, RemainTime,tx,ty));
				monsters.push_back(p_mon);
				break;
			case 2:
				p_mon=(Monster*)(new BigMonster(Health, (BodyMorphism)BodyMorph, RemainTime,tx,ty));
				monsters.push_back(p_mon);
				break;
			case 3:
				p_mon=(Monster*)(new SmallMonster(Health, (BodyMorphism)BodyMorph, RemainTime,tx,ty));
				monsters.push_back(p_mon);
				break;
			}
		}
		inputfile>>t;//蛇身数量
		snake.ClearForLoad();//蛇身deque清空
		for(int i=0;i<t;i++){//设置蛇身体坐标
			Body b;
			inputfile>>b.x>>b.y;
			snake.AddBody(b);
		}
		int bullet,direct,fire_num,ice_num;
		inputfile>>bullet>>direct>>fire_num>>ice_num;
		snake.setBulletType((BulletType)bullet);
		snake.setHeadDirect((Direction)direct);
		snake.setFIREnum(fire_num);
		snake.setICEnum(ice_num);
		inputfile>>m_bGameFlag[Suspend]
				 >>m_iCurrentLevel;
		inputfile.close();
		if(monsters.size()==0)
			m_bGameFlag[DoorOpen]=true;
		else
			m_bGameFlag[DoorOpen]=false;
	}
	else if(!m_bGameFlag[LoadGame]){//非载入初始化
		m_bGameFlag[A_Attack]=false;
		m_bGameFlag[A_OpenTheDoor]=false;
		m_bGameFlag[A_GameComplete]=false;
		m_bGameFlag[A_LevelComplete]=false;
		m_bGameFlag[A_GameLost]=false;
		m_bGameFlag[A_GameQuit]=false;
		m_bGameFlag[Suspend]=false;
		m_bGameFlag[DoorOpen]=false;
		InitMap();
		LoadMap(m_iCurrentLevel);//地图信息初始化(WALL/ICEBOX/FIREBOX/DOOR)
	
		food.FoodInit();//食物初始化
		//怪物初始化//begin
		Monster *pMonster;
		for(int i=0;i<Map::g_iBossNum;i++){
			pMonster=(Monster*)(new BossMonster);
			monsters.push_back(pMonster);
		}
		for(int i=0;i<Map::g_iBigNum;i++){
			pMonster=(Monster*)(new BigMonster);
			monsters.push_back(pMonster);
		}
		for(int i=0;i<Map::g_iSmallNum;i++){
			pMonster=(Monster*)(new SmallMonster);
			monsters.push_back(pMonster);
		}
		//怪物初始化//end
		//蛇重设坐标
		snake.SnakeInit();
	}
	//wang//将地图保存在一张位图中，每次刷屏直接投影
	mapBitmap  =new Bitmap(640,480);
	Graphics *g=Graphics::FromImage(mapBitmap);
	/*SolidBrush  brush(Color::AntiqueWhite);
	
	g->FillRectangle (&brush,0,0,640,480);*/
	
	for(int j=0;j<MAP_WIDTH;j++)
	{
		for (int i=0;i<MAP_HEIGHT;i++)
		{
			if(g_Map[j][i]==M_WALL)
				g->DrawImage (m_Wall->getImage (),j*20,i*20,20,20);
		}
	}
	g->DrawImage (m_Gate->getImage (),300,0,20,20);
	g->DrawImage (m_Gate->getImage (),320,0,20,20);
	
	m_loopFlag = 0;
	m_eGameState = vnGameRunning;
	m_bGameFlag[LevelStart]=true;
	m_bGameFlag[LoadGame]=false;
	m_fDelta = 0;

}

void vnGame::ProcessLevelComplete(vnReal32 fStep)
{

	/***  方晶 begin ****/
	m_iCurrentLevel++;
	if(m_iCurrentLevel<7)
		m_eGameState=vnGameLevelStarting;
	else
		m_eGameState=vnGameComplete;
	m_bGameFlag[A_LevelComplete]=false;
	m_bGameFlag[DoorOpen]=false;

	/*** 方晶 end *****/
}

void vnGame::ProcessComplete(vnReal32 fStep)
{
	m_eGameState=vnGameMenu;
}

void vnGame::ProcessSmallMenu(vnReal32 fStep)
{
	/*if(!m_loopFlag)
	{
		m_kSoundBg1.Play(vnTrue);
		m_loopFlag = 1;
	}*///smallmenu不放音效

	m_fDelta += fStep;
	//键盘延时
	if(m_fDelta > 0.2f)
	{
		if(GetAsyncKeyState(VK_UP) & 0x80000f)
		{
			m_kSmallMenu.onKeyUp();
			m_kSoundMenu.Play(vnFalse);
		}
		if(GetAsyncKeyState(VK_DOWN) & 0x80000f)
		{
			m_kSmallMenu.onKeyDown();
			m_kSoundMenu.Play(vnFalse);
		}
		if(GetAsyncKeyState(VK_RETURN) & 0x80000f)
		{
			switch(m_kSmallMenu.getActive())
			{
			case 0: //Continue
				if(m_eGameState = vnGameRunning)
				m_eGameState = vnGameRunning;
				break;
			case 1: //Restart
				m_eGameState = vnGameLevelStarting;
				break;
			case 2: //Save
			if(true){
				ofstream outputfile("save\\data");
				outputfile<<1000<<' ';
				for(int i=0;i<Map::MAP_WIDTH;i++){//存储g_Map[][]信息
					for(int j=0;j<Map::MAP_HEIGHT;j++){
						outputfile<<Map::g_Map[i][j]<<' ';
					}
				}
				outputfile<<food.getPosition().x<<' ' //food信息_(x,y)
					      <<food.getPosition().y<<' ';
				Monster* p_mon;                        //monsters信息_怪物数量_每个怪物的
				vector<Monster*>::iterator iter=monsters.begin();//(剩余生命值、身体状态、剩余冰冻时间、坐标)
				outputfile<<monsters.size()<<' ';
				for(;iter<monsters.end();iter++){
					p_mon=(Monster*)(*iter);
					outputfile<<p_mon->getHealthPoint()<<' '
							  <<p_mon->getBodyMorph()<<' '
							  <<p_mon->getRemainingTime()<<' '
							  <<p_mon->getPosition().x<<' '
							  <<p_mon->getPosition().y<<' '
							  <<p_mon->getMoveSpeedConstant()<<' ';//用于判断怪物类型
				}
				outputfile<<snake.getBodyNum()<<' ';//存储snake信息_蛇身数量_蛇身坐标_子弹类型_头方向_剩余FIRE_剩余ICE
				for(int i=0;i<snake.getBodyNum();i++){
					outputfile<<snake.getBodyCord(i).x<<' '
							  <<snake.getBodyCord(i).y<<' ';
				}
				outputfile<<snake.getBulletType()<<' '
						  <<snake.getHeadDirect()<<' '
						  <<snake.getFIREnum()<<' '
						  <<snake.getICEnum()<<' '
						  <<m_bGameFlag[Suspend]<<' ' //存储暂停信息
						  <<m_iCurrentLevel<<' ';   //存储当前关卡
				outputfile.close();
				break;
			}
			case 3: //Help
				DialogBox (m_hInstance, MAKEINTRESOURCE(IDD_HELP), m_hWindow, HelpDlgProc);
				break;
			case 4: //Exit
				
				m_eGameState = vnGameMenu;
				break;
			}
		}
		m_fDelta = 0;
	}
}

// 渲染游戏进行中的画面
void vnGame::RenderFrame(void)
{
#ifdef _DEBUG
	using namespace Map;
	//dummy(L"Running");
	
	//wang
	
	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	imgraphics.DrawImage (mapBitmap,0,0);//画map

	////////////////////////////////////////////
	Point pos(0,0);

	pos.X= (food.getPosition().x)*20;
	pos.Y= (food.getPosition().y)*20;
	imgraphics.DrawImage(m_Food->getImage (),pos.X ,pos.Y ,20,20);//画food
	
	Monster *p_mon;	//画怪
	if(monsters.size()>0)
	{
		vector<Monster*>::iterator m_iter=monsters.begin(),m_end=monsters.end();
		//p_mon=(monsters.front ());
		while(m_iter<m_end){
			p_mon=(Monster*)(*m_iter);
			m_iter++;
			int mon_type=(int)p_mon->getMoveSpeedConstant()-1;
			//int mon_state=
			pos.X =p_mon->getPosition().x*20 ;
			pos.Y =p_mon->getPosition().y*20 ;
			if(g_Map[pos.X/20][pos.Y/20]==M_MONSTER)
				imgraphics.DrawImage(m_Monster[mon_type][(int)p_mon->getBodyMorph()]->getImage (),pos.X ,pos.Y ,20,20);
		}
	}

	int i=0,j=0;//画弹源
	for(i=0;i<MAP_WIDTH;++i)
		for(j=0;j<MAP_HEIGHT;++j){
			if(g_Map[i][j]==M_ICEBOX)
				imgraphics.DrawImage(m_Icebox->getImage (),i*20,j*20,20,20);
			else if(g_Map[i][j]==M_FIREBOX)
				imgraphics.DrawImage(m_Firebox->getImage (),i*20,j*20,20,20);
		}



	//画蛇
	int bodylength=snake.getBodyNum();
	PointF bodypos(0.0f,0.0f);

	bodypos.X =snake.getHead().x*20;
	bodypos.Y =snake.getHead().y*20;
	if(g_Map[(int)(bodypos.X/20)][(int)(bodypos.Y/20)]==M_PASSAGE)
		imgraphics.DrawImage(m_SnakeHead[(int)snake.getHeadDirect()]->getImage (),bodypos.X ,bodypos.Y,20.0f,20.0f);
	
	bodypos.X =snake.getTail().x*20;
	bodypos.Y =snake.getTail().y*20;
	if(g_Map[(int)(bodypos.X/20)][(int)(bodypos.Y/20)]==M_PASSAGE)
		imgraphics.DrawImage(m_SnakeTail->getImage (),bodypos.X ,bodypos.Y,20.0f,20.0f);

	for (int i=1 ;i<bodylength-1;i++)
	{
		bodypos.X =snake.getBodyCord(i).x*20;
		bodypos.Y =snake.getBodyCord(i).y*20;
		if(g_Map[(int)(bodypos.X/20)][(int)(bodypos.Y/20)]==M_PASSAGE)
			imgraphics.DrawImage(m_SnakeBody->getImage (),bodypos.X ,bodypos.Y,20.0f,20.0f );
	}
	if(m_bGameFlag[DoorOpen]){//画打开的门
		SolidBrush  solidBrush(Color::Black );
		imgraphics.FillRectangle(&solidBrush,300,0,40,20);
	}
	//攻击效果
	if(m_bGameFlag[A_Attack])
	{
		Point bullet_a(0,0);
		Point bullet_b(0,0);
		Body snakehead=snake.getHead ();
		int i,j;
		switch(snake.getHeadDirect ())
		{
		case DIR_UP :
			bullet_a.X =snakehead .x *20+10;
			bullet_a.Y =snakehead .y *20;
			 i=snakehead .x ;
			for(j=snakehead.y -1;j>0;j--)
				if(g_Map[i][j]==M_MONSTER ||
					g_Map[i][j]==M_DOOR || 
					g_Map[i][j]==M_WALL ||
					g_Map[i][j]==M_FOOD) 
					break;
			bullet_b.X =i*20+10;
			bullet_b.Y =(j+1)*20;
			break;
		case DIR_DOWN :
			bullet_a.X =snakehead .x *20+10;
			bullet_a.Y =(snakehead .y+1) *20;
			i=snakehead .x ;
			for(j=snakehead.y +1;j<MAP_HEIGHT;j++)
				if(g_Map[i][j]==M_MONSTER ||
					g_Map[i][j]==M_DOOR || 
					g_Map[i][j]==M_WALL ||
					g_Map[i][j]==M_FOOD) 
					break;
			bullet_b.X =i*20+10;
			bullet_b.Y =j*20;
			break;
		case DIR_LEFT :
			bullet_a.X =snakehead .x *20;
			bullet_a.Y =snakehead .y *20+10;
			j=snakehead.y ;
			for(i=snakehead.x -1;i>0;i--)
				if(g_Map[i][j]==M_MONSTER ||
					g_Map[i][j]==M_DOOR || 
					g_Map[i][j]==M_WALL ||
					g_Map[i][j]==M_FOOD) 
					break;
			bullet_b.X =(i+1)*20;
			bullet_b.Y =j*20+10;
			break;
		case DIR_RIGHT :	
			bullet_a.X =(snakehead .x+1) *20;
			bullet_a.Y =snakehead .y *20+10;
			j=snakehead.y;
			for(i=snakehead.x+1;i<MAP_WIDTH;i++)
				if(g_Map[i][j]==M_MONSTER ||
					g_Map[i][j]==M_DOOR || 
					g_Map[i][j]==M_WALL ||
					g_Map[i][j]==M_FOOD) 
					break;
			bullet_b.X =i*20;
			bullet_b.Y =j*20+10;
			break;
		}
		Pen pen(Color::White ,3);
		switch(snake.getBulletType ())//根据子弹类型，改变子弹颜色
		{
		case 0: pen.SetColor (Color::White);break;
		case 1:	pen.SetColor (Color::Red);break;
		case 2: pen.SetColor (Color::Blue);break;
		}
	imgraphics.DrawLine(&pen,bullet_a,bullet_b);
	vnScreen::GetSingleton()->EndFrame();
	Sleep(200);
	}
	
//开门
	if(m_bGameFlag[A_OpenTheDoor])
	{
		PointF gatel_pos(300.0f,0);
		PointF gater_pos(320.0f,0);
		
		
		for(int i=0; i<20;i++)
		{
			SolidBrush  solidBrush(Color::Black );
			imgraphics.FillRectangle(&solidBrush,300,0,40,20);
			gatel_pos.X --;
			gater_pos.X ++;
			imgraphics.DrawImage (m_Gate->getImage (),gatel_pos);
			imgraphics.DrawImage (m_Gate->getImage (),gater_pos);
			imgraphics.DrawImage (m_Wall->getImage (),280,0,20,20);
			imgraphics.DrawImage (m_Wall->getImage (),340,0,20,20);
			vnScreen::GetSingleton()->EndFrame();
			Sleep(100);
		}		
	}
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 20, FontStyleRegular, UnitPixel);
	PointF      pointF(25.0f, 25.0f);
	SolidBrush  solidBrush(Color(255, 0, 0, 255));
	wchar_t str[40];
	if(snake.getBodyNum ()>3)
	{
		switch(snake.getBulletType())
		{
		case B_NORMAL_BULLET :wsprintf(str,L"NORMAL BULLET"); break;
		case B_FIRE_BULLET   :wsprintf(str,L"FIRE BULLET");break;
		case B_ICE_BULLET    :wsprintf(str,L"ICE BULLET");break;
	
		}
	}else wsprintf(str,L"NOBULLET");
	
	imgraphics.DrawString(str, -1, &font, pointF, &solidBrush);
#endif
}

// 渲染游戏失败后的画面
void vnGame::RenderLostGame(void)
{
	static vnTimer kTimer;
	static vnReal32 fTimer = 0;
	static float y_words=480.0;
	static bool flag=false;
	kTimer.Update();
	fTimer += kTimer.GetDelta();


	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);

	//imgraphics.DrawImage (tempBitmap,0,0);
	//imgraphics.DrawImage (mapBitmap,0,0);
	RenderFrame();	
	if(!flag){
		m_kSoundLost.Play(vnFalse);//第一次进入，播放Lose
		flag=true;
	}

	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 75, FontStyleRegular, UnitPixel);
	PointF      pointF(130.0f, 480.0f);
	SolidBrush  solidBrush(Color::Gray);
	wchar_t str[14];

	if(fTimer<3.0f){
		if (y_words>200.0){
			if(y_words==240)
				m_kSoundHaha.Play(vnFalse);//哈哈
			y_words-=5;
		}
		wsprintf(str,L"You Lose...");			
		pointF.Y=y_words;
		imgraphics.DrawString(str,12, &font, pointF, &solidBrush);	
	}
	else{
		flag=false;
		m_eGameState = vnGameSmallMenu;
	}
#ifndef _DEBUG
	dummy(L"GameLost");
#endif
}

// 渲染Splash
void vnGame::RenderSplash(void)
{
	//播放splash音效
	m_kSoundLogo.Play(vnFalse);

	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	imgraphics.DrawImage(m_Load->getImage(), 0,0, 640, 480);
	vnScreen::GetSingleton()->EndFrame();

	SolidBrush *semiTransBrush = new SolidBrush(Color(0,0,0,0));
	Sleep(500);

	//splash画面淡出
	for(int i=0;i<50;i++)
	{
	
		semiTransBrush->SetColor(Color(i,255,255,255));
		imgraphics.FillRectangle (semiTransBrush,0,0,640,480);
		Sleep(30);
		
	vnScreen::GetSingleton()->EndFrame();
	}
	//wang//开始图片，1秒后进入选择菜单
	imgraphics.DrawImage(m_Menu1->getImage(), 0,0, 640, 480);
	vnScreen::GetSingleton()->EndFrame();
	Sleep(1000);
	m_eGameState = vnGameMenu;
}

// 渲染菜单
void vnGame::RenderMenu(void)
{
	static vnTimer kTimer;
	static vnReal32 fTimer = 0;

	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	kTimer.Update();
	fTimer += kTimer.GetDelta();
	//wang//背景图片：眨眼睛
	if(fTimer < 2.0f)
		imgraphics.DrawImage(m_Menu1->getImage(), 0,0, 640, 480);
	else
	{
		imgraphics.DrawImage(m_Menu2->getImage(), 0,0, 640, 480);
		fTimer = 0;
	}

	
	m_kMenu.Render(buffer);
}

// 渲染小菜单（游戏进行中的左上角弹出式菜单）
void vnGame::RenderSmallMenu(void)
{
#ifdef _DEBUG
	//dummy(L"SmallMenu");
	static vnTimer kTimer;
	static vnReal32 fTimer = 0;

	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	kTimer.Update();
	fTimer += kTimer.GetDelta();
	

	RenderFrame();
	
	m_kSmallMenu.Render(buffer);
#endif
}

// 渲染新关卡开始的画面
void vnGame::RenderLevelStarting(void)
{
#ifdef _DEBUG
	//fang//播放音效
	if(m_iCurrentLevel == 1)
		m_kSoundGong.Play(vnFalse);
	else
		m_kSoundLvStart.Play(vnFalse);
	
	//wang

	static int i=0;
	static float j=0.0;
	static vnTimer kTimer;
	static vnReal32 fTimer = 0;
	kTimer.Update();
	fTimer += kTimer.GetDelta();

	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
//wang//设置字体
	FontFamily  fontFamily(L"Tahoma");
		Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
		PointF      pointF(200.0f, 280.0f);
		SolidBrush  solidBrush(Color(200, 0, 0, 0));
		
		SolidBrush semiTransBrush(Color(180,255,255,255));
		wchar_t str[14];

		imgraphics.DrawImage(m_Menu1->getImage(), 0,0, 640, 480);
		imgraphics.FillRectangle (&semiTransBrush,0,0,640,480);
		wsprintf(str,L"LOADING......");
		imgraphics.DrawString(str,14, &font, pointF, &solidBrush);
	for(int i=0;i<50;i++)
	{
		
		
		semiTransBrush.SetColor (Color(100,255,0,0));
			imgraphics.FillRectangle (&semiTransBrush,200,310,4*i,10);
		
		vnScreen::GetSingleton()->EndFrame();
		Sleep(10);
	} 
	Sleep(100);		
	//dummy(L"LevelStarting");
#endif
}

// 渲染关卡结束的画面
void vnGame::RenderLevelComplete(void)
{
#ifdef _DEBUG
	dummy(L"LevelComplete");
#endif
}

// 渲染游戏结束的画面
void vnGame::RenderGameComplete(void)
{
	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	SolidBrush semiTransBrush(Color(180,255,255,255));
		

		imgraphics.DrawImage(m_Menu1->getImage(), 0,0, 640, 480);
		imgraphics.FillRectangle (&semiTransBrush,0,0,640,480);
#ifdef _DEBUG
	dummy(L"CONGRATULATIONS!");
#endif
}

// 渲染离开游戏的画面
void vnGame::RenderQuit(void)
{
#ifdef _DEBUG
	//dummy(L"Quit");
	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	imgraphics.DrawImage(m_Load->getImage(), 0,0, 640, 480);
	

	SolidBrush *semiTransBrush = new SolidBrush(Color(0,0,0,0));
	

	//splash画面淡出
	for(int i=0;i<50;i++)
	{
	
		semiTransBrush->SetColor(Color(i,255,255,255));
		imgraphics.FillRectangle (semiTransBrush,0,0,640,480);

		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
		PointF      pointF(10.0f, 10.0f);
		SolidBrush  solidBrush(Color(255, 0, 0, 255));
		wchar_t str[40];
		wsprintf(str,L"THANK YOU");
		imgraphics.DrawString(str, -1, &font, pointF, &solidBrush);
		Sleep(30);
		
	vnScreen::GetSingleton()->EndFrame();
	}
#endif
}

void vnGame::dummy(wstring phase)
{
	static int i=0;
	i++;
	

	HDC buffer = vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	SetBkMode(buffer,TRANSPARENT);
	SetTextColor(buffer,RGB(255,0,0));

	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	PointF      pointF(10.0f, 10.0f);
	SolidBrush  solidBrush(Color(255, 0, 0, 255));
	wchar_t str[40];
	wsprintf(str,L"%s", phase.c_str());
	imgraphics.DrawString(str, -1, &font, pointF, &solidBrush);
}