#include ".\monster.h"
#include <cstdlib>
#include <ctime>

Monster::Monster(int hp, BodyMorphism bm, int rtime)
{
	HealthPoint = hp;
	bodyMorph = bm;
	remainingTime =rtime;
	
	//����//�������ʼ��һ������
	srand((unsigned int)time(NULL));
	do{
		
		x=(int)(rand()%32);
		y=(int)(rand()%24);
	}while(Map::g_Map[x][y]!=0);
	//����//��Ӧλ�����ù�������
	Map::g_Map[x][y]=Map::M_MONSTER;
}

Monster::~Monster(void)
{
}

// ���ù����λ��
void Monster::setPosition(void)
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
	int temp,xx,yy;
	do{
		temp=rand()%5;
		switch(temp){
		case DIR_STAY:	xx=x;yy=y;break;
		case DIR_UP:	yy=y-1;xx=x;break;
		case DIR_DOWN:	yy=y+1;xx=x;break;
		case DIR_LEFT:	xx=x-1;yy=y;break;
		case DIR_RIGHT:	xx=x+1;yy=y;break;
		}
	}while(g_Map[xx][yy]==M_FOOD || g_Map[xx][yy]==M_WALL || g_Map[xx][yy]==M_MONSTER
			|| g_Map[xx][yy]==M_DOOR || xx<0 || xx>=MAP_WIDTH
			|| yy<0 || yy>=MAP_HEIGHT);
	//����Ӧ��map�����ù�������
	x=xx; y=yy;
	g_Map[x][y]=M_MONSTER;
}

// ����λ��
Position Monster::getPosition(void)
{
	Position pos;
	pos.x = x;
	pos.y = y;
	return pos;
}
//��������״̬
BodyMorphism Monster::getBodyMorph(void)
{
	return bodyMorph;
}
//����//��������ֵ
int Monster::getHealthPoint(void)
{
	return HealthPoint;
}
//����//����ʣ�����ʱ��
int Monster::getRemainingTime(void)
{
	return remainingTime;
}
// �ܵ�����������ֵ����
void Monster::gatAttack(BulletType b)
{
	//�ܵ�����������ֵ����
	//���ܵ�ICE�ӵ���������̬�����仯���ƶ�����ɥʧ
	//����//�ڱ���������֮���ֱ���ICE������
		  //remainingTime��bodyMorph����
	switch(b)
	{
	case B_NORMAL_BULLET:
		this->HealthPoint-=1; //����//NORMAL�ӵ�������Ϊ1
		break;
	case B_FIRE_BULLET:
		this->HealthPoint-=3; //����//FIRE�ӵ�������Ϊ3����Ӱ���ƶ�
		break;
	case B_ICE_BULLET:
		this->HealthPoint-=2;
		this->bodyMorph = BODY_FROZEN;
		this->remainingTime = this->getRecoveryTime();
		break;
	}
}

// �жϹ����Ƿ�����
bool Monster::isDead(void)
{
	if(this->HealthPoint <= 0)
		return true;
	else
		return false;
}

// ��������֮ǰ�����ӵ�
//����//�������������˵�������Ѿ�����
void Monster::generateBulletBox(void)
{
	//����rand���Եȿ��ܵط����κ�����
	//��rand%100 == 0�ĸ���Ϊ0.01

	using namespace Map;
	g_Map[x][y]=M_PASSAGE;//�޸ĵ�ͼ��Ϣ

	if(rand()%getProbabilityConstant() == 0)
	{
		switch(rand()%2)
		{
		case 0:
			g_Map[x][y]=M_ICEBOX;
			return;
		case 1:
			g_Map[x][y]=M_FIREBOX;
			return;
		}
	}
}

// action routine
//������״̬���������ƶ����ƶ�
//�ƶ���Ŀ��λ��
/***********  ���� *************
 *   ���Ա�setPosition()����  **
 *******************************
void Monster::MoveTo(int x, int y)
{
	if(!(x>=0 && x <Map::MAP_WIDTH
		&& y>=0 && y<Map::MAP_HEIGHT))
		return;
	if(remainingTime-- > 0)
		return;
	
	if(Map::g_Map[x][y] == Map::M_PASSAGE)
	{
		Map::g_Map[this->x][this->y] = Map::M_PASSAGE;
		Map::g_Map[x][y] = Map::M_MONSTER;
		this->x = x;
		this->y = y;
	}
}
 ***********************************/