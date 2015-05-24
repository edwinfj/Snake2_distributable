#include "BossMonster.h"

BossMonster::BossMonster(void)
:Monster(hp, initBMorph, initRTime)
{
}

BossMonster::BossMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int bx,int by)
:Monster(Health, BodyMorph, RemainTime)
{
	this->x=bx;
	this->y=by;
	Map::g_Map[x][y]=Map::M_MONSTER;
}

BossMonster::~BossMonster(void)
{
}

// ���ظ��ʳ����������������������ӵ��ĸ���
int BossMonster::getProbabilityConstant(void)
{
	return 1;
}

// �����ܵ������ӵ������󣬻ظ��ƶ���������Ҫ��ʱ��
int BossMonster::getRecoveryTime(void)
{
	return 2; //������λʱ��
}

//����//�����ƶ��ٶȣ�ÿ1֡�ƶ�һ��
int BossMonster::getMoveSpeedConstant(void)
{
	return 1;
}

//����//BOSS�ƶ���ʽ
void BossMonster::setPosition(void)
{
	if(remainingTime-- > 0)
		return;
	else{     //����//������ʱ�䵽���ı�����״̬
		remainingTime=0;
		bodyMorph=BODY_NORMAL;
	}

	using namespace Map;
	//����//��map�ϵĹ����������
	if(g_Map[x][y]==M_MONSTER)
		g_Map[x][y]=M_PASSAGE;
	//����//�ƶ�����������һ��߲���
		//BOSS���Զ��ǽ��
	int temp,xx,yy;
	do{
		srand((unsigned int)time(NULL));
		temp=rand()%5;
		switch(temp){
		case DIR_STAY:	xx=x;yy=y;break;
		case DIR_UP:	xx=x;yy=y-1;break;
		case DIR_DOWN:	xx=x;yy=y+1;break;
		case DIR_LEFT:	xx=x-1;yy=y;break;
		case DIR_RIGHT:	xx=x+1;yy=y;break;
		}
	}while(g_Map[xx][yy]==M_FOOD || g_Map[xx][yy]==M_MONSTER	|| g_Map[xx][yy]==M_DOOR
			|| xx<0 || xx>=MAP_WIDTH
			|| yy<0 || yy>=MAP_HEIGHT);
	//����Ӧ��map�����ù�������
	x=xx; y=yy;
	if(g_Map[x][y]!=M_WALL)
		g_Map[x][y]=M_MONSTER;
}

