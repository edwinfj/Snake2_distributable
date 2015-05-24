#include "vnGame.h"

vnGame::vnGame(void)
{
	m_eGameState = vnGameSplash;
	m_fDelta = 0;
	m_loopFlag = 0;
	
	//�˵���Դ����
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

	//ͼ����Դ����
	
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
	//������룬��ɾ��
}

void vnGame::Start(HINSTANCE hInstance, HWND hWindow)
{
	m_hInstance = hInstance;
	m_hWindow = hWindow;

	m_kSoundPlayer.Init(hWindow);
	m_kSoundBg1.LoadFromFile("sound\\running.wav");//frameȫ����Ч
	m_kSoundBg2.LoadFromFile("sound\\2.wav");//�������������������
	m_kSoundMenu.LoadFromFile("sound\\menu.wav");//�˵�������Ч
	m_kSoundLost.LoadFromFile("sound\\lost.wav");//��Ϸ����GameLost
	m_kSoundLvStart.LoadFromFile("sound\\lvstart.wav");//�����¹ؿ�levelstart
	m_kSoundGong.LoadFromFile("sound\\newgong.wav");//����Ϸlevelstart
	m_kSoundFire.LoadFromFile("sound\\fire.wav");//frame��
	m_kSoundIce.LoadFromFile("sound\\ice.wav");//frame����
	m_kSoundNormal.LoadFromFile("sound\\normal.wav");//Fream��ͨ��
	m_kSoundEat.LoadFromFile("sound\\eat.wav");//Frame��ʳ��
	m_kSoundLogo.LoadFromFile("sound\\logo.wav");//Splash
	m_kSoundCollide.LoadFromFile("sound\\collision.wav");//Frameײǽ
	m_kSoundHaha.LoadFromFile("sound\\haha.wav");//�㲻����֪�����Ǹ����õ�
	m_kSoundOpenTheDoor.LoadFromFile("sound\\dooropen.wav");//frame������Ч
	m_kTimer.Update();
}

// render routine
void vnGame::Render(void)
{
	//��ʼ��Ⱦ
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

	//������Ⱦ���������������Ļ
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

	//fang//running�в�����Ч
	if(!m_loopFlag)
	{
		m_kSoundBg1.Play(vnTrue);
		m_loopFlag = 1;
	}

	//���´����������Ҫ����
	//��ȡ����
	
	//����//�����������Ŷ������ƶ�����ͬһ֡��Ϊ
	if(!m_bGameFlag[A_Attack] && !m_bGameFlag[A_OpenTheDoor])
		fTimer += fStep; 
	
	//����//����0.2s�����Զ����������ı�״̬
		//��ͣʱ�����ı�״̬���ȴ�����
	if((m_bGameFlag[Suspend] || fTimer<0.2f)
		&& !m_bGameFlag[A_Attack]
		&& !m_bGameFlag[A_OpenTheDoor]){
		if(m_fDelta > 0.2f){
			if(!m_bGameFlag[Suspend]){//������ͣ״̬
				if(GetAsyncKeyState(VK_ESCAPE) & 0x80000f){//ESC�˳�
					while(GetAsyncKeyState(VK_ESCAPE) & 0x80000f);//��ֹ����
					m_fDelta=0;
					m_eGameState=vnGameSmallMenu;
				}
				else if(GetAsyncKeyState('C') & 0x80000f){//C�ı��ӵ�
					//while(GetAsyncKeyState('C') & 0x80000f);//��ֹ����
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
				else if(GetAsyncKeyState(VK_SPACE) & 0x80000f){//���ո����ͣ
					while(GetAsyncKeyState(VK_SPACE) & 0x80000f);//��ֹ����
					m_fDelta=0;
					m_bGameFlag[Suspend]=1;
				}
			}
			else if(GetAsyncKeyState(VK_SPACE) & 0x80000f){//��ͣ�ָ�
				while(GetAsyncKeyState(VK_SPACE) & 0x80000f);//��ֹ����
				m_fDelta=0;
				m_bGameFlag[Suspend]=0;
			}
		}
		return;
	}

	//����//����0.2s��ˢ��״̬��������
	//����A���������
	if(m_fDelta>0.2f && !m_bGameFlag[A_Attack]
	   && !m_bGameFlag[A_OpenTheDoor]){
		if(GetAsyncKeyState('A') & 0x80000f){
			//while(GetAsyncKeyState('A') & 0x80000f);//��ֹ����
			m_fDelta=0;
			if(snake.getBodyNum()>3){
				switch(snake.getBulletType()){//���Ź�����Ч
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
				snake.DeleteBody(); //����-1��������ͨ�ӵ���
				m_bGameFlag[A_Attack]=1;
				return;
			}
		}//����ı���ͷ����
		else if(GetAsyncKeyState(VK_UP) & 0x80000f){
			//while(GetAsyncKeyState(VK_UP) & 0x80000f);//��ֹ����
			m_fDelta=0;
			snake.setHeadDirect(DIR_UP);
		}
		else if(GetAsyncKeyState(VK_DOWN) & 0x80000f){
			//while(GetAsyncKeyState(VK_DOWN) & 0x80000f);//��ֹ����
			m_fDelta=0;
			snake.setHeadDirect(DIR_DOWN);
		}
		else if(GetAsyncKeyState(VK_LEFT) & 0x80000f){
			//while(GetAsyncKeyState(VK_LEFT) & 0x80000f);//��ֹ����
			m_fDelta=0;
			snake.setHeadDirect(DIR_LEFT);
		}
		else if(GetAsyncKeyState(VK_RIGHT) & 0x80000f){
			//while(GetAsyncKeyState(VK_RIGHT) & 0x80000f);//��ֹ����
			m_fDelta=0;
			snake.setHeadDirect(DIR_RIGHT);
		}
	}

	using namespace Map; 

	//����//�������״̬���//begin
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
				g_Map[head.x][t]!=M_FOOD && //����ʳ��
				t>=0;
				g_Map[head.x][t]=M_PASSAGE,t--);

			pos.x=head.x; pos.y=t;
			if(g_Map[pos.x][pos.y]==M_FOOD){//ʳ�����
				food.FoodInit();
			}
			if(g_Map[pos.x][pos.y]==M_MONSTER){//����ײ������
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
				g_Map[head.x][t]!=M_FOOD && //����ʳ��
				t<MAP_HEIGHT;
				g_Map[head.x][t]=M_PASSAGE,t++);

			pos.x=head.x; pos.y=t;
			if(g_Map[pos.x][pos.y]==M_FOOD){//ʳ�����
				food.FoodInit();
			}
			if(g_Map[pos.x][pos.y]==M_MONSTER){//����ײ������
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
				g_Map[t][head.y]!=M_FOOD && //����ʳ��
				t>=0;
				g_Map[t][head.y]=M_PASSAGE,t--);

			pos.x=t; pos.y=head.y;
			if(g_Map[pos.x][pos.y]==M_FOOD){//ʳ�����
				food.FoodInit();
			}
			if(g_Map[pos.x][pos.y]==M_MONSTER){//����ײ������
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
				g_Map[t][head.y]!=M_FOOD && //����ʳ��
				t<MAP_WIDTH;
				g_Map[t][head.y]=M_PASSAGE,t++);
			
			pos.x=t; pos.y=head.y;
			if(g_Map[pos.x][pos.y]==M_FOOD){//ʳ�����
				food.FoodInit();
			}
			if(g_Map[pos.x][pos.y]==M_MONSTER){//����ײ������
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
		snake.DeleteBullet(); //�����ӵ�����-1������У�//��ı��ӵ�״̬�����Է��������ж�֮��
		//����//�ж��Ƿ�Ҫ����
		if(monsters.size()==0 && !m_bGameFlag[DoorOpen]){
			m_kSoundOpenTheDoor.Play(vnFalse);//���ſ�����Ч
			m_bGameFlag[A_OpenTheDoor]=true;
			return; //����//����ǣ������붯��
		}
	}

	if(m_bGameFlag[A_OpenTheDoor]){//����//���Ŷ���֮�󣬰��Ŵ�
		m_bGameFlag[A_OpenTheDoor]=false;
		m_bGameFlag[DoorOpen]=true;
	}
	//����//�������״̬���//end

	//����//ͨ��״̬�ı�//begin
	m_iFrameSpeed=m_iFrameSpeed%6+1;
	//if(food.getDeltaTime()>1.0f)
	//	food.FoodInit();	//ʳ��ʱ�䵽���ı�λ��//������ʱ�����
	Body tail=snake.Move(); //���ƶ�
	Monster *p; //�����ƶ�
	for(int i=0;i<(int)monsters.size();i++){
		p=(Monster *)(monsters[i]);
		if(!(m_iFrameSpeed % (p->getMoveSpeedConstant())))
			p->setPosition();
	}
	//����//ͨ��״̬�ı�//end

	//����//ͨ��״̬���//begin
	Body pos=snake.getHead();
	if(snake.isDead())//��ײ���Լ�
	{
		m_eGameState=vnGameLost;
		//wangm_bGameFlag[Suspend]=1;
	}
	if(g_Map[pos.x][pos.y]==M_FOOD){//����//�߳�ʳ��
		m_kSoundEat.Play(vnFalse);//������Ч
		snake.AddBody(tail);
		food.FoodInit();
	}
	if(g_Map[pos.x][pos.y]==M_FIREBOX){//����//�߳Ի�
		m_kSoundEat.Play(vnFalse);//������Ч
		snake.setFIREnum();
		snake.setBulletType(B_FIRE_BULLET);
		g_Map[pos.x][pos.y]=M_PASSAGE;
	}
	if(g_Map[pos.x][pos.y]==M_ICEBOX){//����//�߳Ա���
		m_kSoundEat.Play(vnFalse);//������Ч
		snake.setICEnum();
		snake.setBulletType(B_ICE_BULLET);
		g_Map[pos.x][pos.y]=M_PASSAGE;
	}
	//��ײ��ǽ����ŵ��Ż����
	if(g_Map[pos.x][pos.y]==M_WALL || g_Map[pos.x][pos.y]==M_MONSTER 
		|| (g_Map[pos.x][pos.y]==M_DOOR && !m_bGameFlag[DoorOpen])){
		snake.DeleteBody();//����-1
		if(snake.isDead()){//�ж����Ƿ�����
			m_eGameState=vnGameLost;
			//wangm_bGameFlag[Suspend]=1;
		}
		else if(!snake.ResetHead()){//�ƶ�ͷ��λ��	
			m_eGameState=vnGameLost;
			//wangm_bGameFlag[Suspend]=1;
		}//�߱�����
		else{
			m_kSoundCollide.Play(vnFalse);//���û�����򲥷���Ч
		}
	}
	if(m_bGameFlag[DoorOpen] && g_Map[pos.x][pos.y]==M_DOOR)
		m_eGameState=vnGameLevelComplete;
	//����//ͨ��״̬���//end
				
	fTimer=0;//һ֡������֡�ڼ�ʱ������
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
	}*///Menu�ڲ���������
	m_kSoundBg1.Stop();
	m_fDelta += fStep;
	//������ʱ
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
	/**************** ���� *********************
	 *  �ҵ��뷨�ǣ������ﶯ�������־λְλ+   *
	 *	���õ�ͼ��Ϣ(map[]�����ֹ��������)     *  
	*********************************************/

	//����//������־����
	m_iFrameSpeed=1;
	monsters.clear();//��monsters�������
	using  namespace Map;
	
	if(m_bGameFlag[LoadGame]){//�����ʼ��
		m_bGameFlag[A_Attack]=false;
		m_bGameFlag[A_OpenTheDoor]=false;
		m_bGameFlag[A_GameComplete]=false;
		m_bGameFlag[A_LevelComplete]=false;
		m_bGameFlag[A_GameLost]=false;
		m_bGameFlag[A_GameQuit]=false;
		
		ifstream inputfile("save\\data");
		int t,tx,ty;
		inputfile>>t;//����־λ1000ȥ��
		for(int i=0;i<Map::MAP_WIDTH;i++){    //��ͼ��Ϣ��ʼ��
			for(int j=0;j<Map::MAP_HEIGHT;j++){
				inputfile>>t;
				Map::g_Map[i][j]=t;
			}
		}
		inputfile>>tx>>ty;//food��ʼ��
		food.setPosition(tx,ty);
		Monster* p_mon;
		inputfile>>t;//��������
		for(int i=0;i<t;i++){
			int Health,RemainTime,MoveSpeed,BodyMorph;
			inputfile>>Health>>BodyMorph>>RemainTime>>tx>>ty>>MoveSpeed;
			switch(MoveSpeed){//����MoveSpeed�жϹ�������
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
		inputfile>>t;//��������
		snake.ClearForLoad();//����deque���
		for(int i=0;i<t;i++){//��������������
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
	else if(!m_bGameFlag[LoadGame]){//�������ʼ��
		m_bGameFlag[A_Attack]=false;
		m_bGameFlag[A_OpenTheDoor]=false;
		m_bGameFlag[A_GameComplete]=false;
		m_bGameFlag[A_LevelComplete]=false;
		m_bGameFlag[A_GameLost]=false;
		m_bGameFlag[A_GameQuit]=false;
		m_bGameFlag[Suspend]=false;
		m_bGameFlag[DoorOpen]=false;
		InitMap();
		LoadMap(m_iCurrentLevel);//��ͼ��Ϣ��ʼ��(WALL/ICEBOX/FIREBOX/DOOR)
	
		food.FoodInit();//ʳ���ʼ��
		//�����ʼ��//begin
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
		//�����ʼ��//end
		//����������
		snake.SnakeInit();
	}
	//wang//����ͼ������һ��λͼ�У�ÿ��ˢ��ֱ��ͶӰ
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

	/***  ���� begin ****/
	m_iCurrentLevel++;
	if(m_iCurrentLevel<7)
		m_eGameState=vnGameLevelStarting;
	else
		m_eGameState=vnGameComplete;
	m_bGameFlag[A_LevelComplete]=false;
	m_bGameFlag[DoorOpen]=false;

	/*** ���� end *****/
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
	}*///smallmenu������Ч

	m_fDelta += fStep;
	//������ʱ
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
				for(int i=0;i<Map::MAP_WIDTH;i++){//�洢g_Map[][]��Ϣ
					for(int j=0;j<Map::MAP_HEIGHT;j++){
						outputfile<<Map::g_Map[i][j]<<' ';
					}
				}
				outputfile<<food.getPosition().x<<' ' //food��Ϣ_(x,y)
					      <<food.getPosition().y<<' ';
				Monster* p_mon;                        //monsters��Ϣ_��������_ÿ�������
				vector<Monster*>::iterator iter=monsters.begin();//(ʣ������ֵ������״̬��ʣ�����ʱ�䡢����)
				outputfile<<monsters.size()<<' ';
				for(;iter<monsters.end();iter++){
					p_mon=(Monster*)(*iter);
					outputfile<<p_mon->getHealthPoint()<<' '
							  <<p_mon->getBodyMorph()<<' '
							  <<p_mon->getRemainingTime()<<' '
							  <<p_mon->getPosition().x<<' '
							  <<p_mon->getPosition().y<<' '
							  <<p_mon->getMoveSpeedConstant()<<' ';//�����жϹ�������
				}
				outputfile<<snake.getBodyNum()<<' ';//�洢snake��Ϣ_��������_��������_�ӵ�����_ͷ����_ʣ��FIRE_ʣ��ICE
				for(int i=0;i<snake.getBodyNum();i++){
					outputfile<<snake.getBodyCord(i).x<<' '
							  <<snake.getBodyCord(i).y<<' ';
				}
				outputfile<<snake.getBulletType()<<' '
						  <<snake.getHeadDirect()<<' '
						  <<snake.getFIREnum()<<' '
						  <<snake.getICEnum()<<' '
						  <<m_bGameFlag[Suspend]<<' ' //�洢��ͣ��Ϣ
						  <<m_iCurrentLevel<<' ';   //�洢��ǰ�ؿ�
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

// ��Ⱦ��Ϸ�����еĻ���
void vnGame::RenderFrame(void)
{
#ifdef _DEBUG
	using namespace Map;
	//dummy(L"Running");
	
	//wang
	
	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	imgraphics.DrawImage (mapBitmap,0,0);//��map

	////////////////////////////////////////////
	Point pos(0,0);

	pos.X= (food.getPosition().x)*20;
	pos.Y= (food.getPosition().y)*20;
	imgraphics.DrawImage(m_Food->getImage (),pos.X ,pos.Y ,20,20);//��food
	
	Monster *p_mon;	//����
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

	int i=0,j=0;//����Դ
	for(i=0;i<MAP_WIDTH;++i)
		for(j=0;j<MAP_HEIGHT;++j){
			if(g_Map[i][j]==M_ICEBOX)
				imgraphics.DrawImage(m_Icebox->getImage (),i*20,j*20,20,20);
			else if(g_Map[i][j]==M_FIREBOX)
				imgraphics.DrawImage(m_Firebox->getImage (),i*20,j*20,20,20);
		}



	//����
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
	if(m_bGameFlag[DoorOpen]){//���򿪵���
		SolidBrush  solidBrush(Color::Black );
		imgraphics.FillRectangle(&solidBrush,300,0,40,20);
	}
	//����Ч��
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
		switch(snake.getBulletType ())//�����ӵ����ͣ��ı��ӵ���ɫ
		{
		case 0: pen.SetColor (Color::White);break;
		case 1:	pen.SetColor (Color::Red);break;
		case 2: pen.SetColor (Color::Blue);break;
		}
	imgraphics.DrawLine(&pen,bullet_a,bullet_b);
	vnScreen::GetSingleton()->EndFrame();
	Sleep(200);
	}
	
//����
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

// ��Ⱦ��Ϸʧ�ܺ�Ļ���
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
		m_kSoundLost.Play(vnFalse);//��һ�ν��룬����Lose
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
				m_kSoundHaha.Play(vnFalse);//����
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

// ��ȾSplash
void vnGame::RenderSplash(void)
{
	//����splash��Ч
	m_kSoundLogo.Play(vnFalse);

	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	imgraphics.DrawImage(m_Load->getImage(), 0,0, 640, 480);
	vnScreen::GetSingleton()->EndFrame();

	SolidBrush *semiTransBrush = new SolidBrush(Color(0,0,0,0));
	Sleep(500);

	//splash���浭��
	for(int i=0;i<50;i++)
	{
	
		semiTransBrush->SetColor(Color(i,255,255,255));
		imgraphics.FillRectangle (semiTransBrush,0,0,640,480);
		Sleep(30);
		
	vnScreen::GetSingleton()->EndFrame();
	}
	//wang//��ʼͼƬ��1������ѡ��˵�
	imgraphics.DrawImage(m_Menu1->getImage(), 0,0, 640, 480);
	vnScreen::GetSingleton()->EndFrame();
	Sleep(1000);
	m_eGameState = vnGameMenu;
}

// ��Ⱦ�˵�
void vnGame::RenderMenu(void)
{
	static vnTimer kTimer;
	static vnReal32 fTimer = 0;

	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	kTimer.Update();
	fTimer += kTimer.GetDelta();
	//wang//����ͼƬ��գ�۾�
	if(fTimer < 2.0f)
		imgraphics.DrawImage(m_Menu1->getImage(), 0,0, 640, 480);
	else
	{
		imgraphics.DrawImage(m_Menu2->getImage(), 0,0, 640, 480);
		fTimer = 0;
	}

	
	m_kMenu.Render(buffer);
}

// ��ȾС�˵�����Ϸ�����е����Ͻǵ���ʽ�˵���
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

// ��Ⱦ�¹ؿ���ʼ�Ļ���
void vnGame::RenderLevelStarting(void)
{
#ifdef _DEBUG
	//fang//������Ч
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
	
//wang//��������
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

// ��Ⱦ�ؿ������Ļ���
void vnGame::RenderLevelComplete(void)
{
#ifdef _DEBUG
	dummy(L"LevelComplete");
#endif
}

// ��Ⱦ��Ϸ�����Ļ���
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

// ��Ⱦ�뿪��Ϸ�Ļ���
void vnGame::RenderQuit(void)
{
#ifdef _DEBUG
	//dummy(L"Quit");
	HDC buffer=vnScreen::GetSingleton()->getBuffer();
	Graphics imgraphics(buffer);
	
	imgraphics.DrawImage(m_Load->getImage(), 0,0, 640, 480);
	

	SolidBrush *semiTransBrush = new SolidBrush(Color(0,0,0,0));
	

	//splash���浭��
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