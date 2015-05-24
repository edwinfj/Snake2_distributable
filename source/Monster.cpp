#include ".\monster.h"
#include <cstdlib>
#include <ctime>

Monster::Monster(int hp, BodyMorphism bm, int rtime)
{
	HealthPoint = hp;
	bodyMorph = bm;
	remainingTime =rtime;
	
	//方晶//给怪物初始化一个坐标
	srand((unsigned int)time(NULL));
	do{
		
		x=(int)(rand()%32);
		y=(int)(rand()%24);
	}while(Map::g_Map[x][y]!=0);
	//方晶//对应位置设置怪物属性
	Map::g_Map[x][y]=Map::M_MONSTER;
}

Monster::~Monster(void)
{
}

// 设置怪物的位置
void Monster::setPosition(void)
{
	if(remainingTime-- > 0)
		return;
	else{     //方晶//若冰冻时间到，改变身体状态
		remainingTime=0;
		bodyMorph=BODY_NORMAL;
	}

	using namespace Map;
	//方晶//将map上的怪物属性清空
	if(g_Map[x][y]==M_MONSTER)
		g_Map[x][y]=M_PASSAGE;
	//方晶//移动怪物，上下左右或者不动
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
	//将对应的map点设置怪物属性
	x=xx; y=yy;
	g_Map[x][y]=M_MONSTER;
}

// 返回位置
Position Monster::getPosition(void)
{
	Position pos;
	pos.x = x;
	pos.y = y;
	return pos;
}
//返回身体状态
BodyMorphism Monster::getBodyMorph(void)
{
	return bodyMorph;
}
//方晶//返回生命值
int Monster::getHealthPoint(void)
{
	return HealthPoint;
}
//方晶//返回剩余冰冻时间
int Monster::getRemainingTime(void)
{
	return remainingTime;
}
// 受到攻击，生命值减少
void Monster::gatAttack(BulletType b)
{
	//受到攻击，生命值减少
	//若受到ICE子弹攻击，形态发生变化，移动能力丧失
	//方晶//在被冰冻后，若之后又被非ICE弹攻击
		  //remainingTime和bodyMorph不变
	switch(b)
	{
	case B_NORMAL_BULLET:
		this->HealthPoint-=1; //方晶//NORMAL子弹攻击力为1
		break;
	case B_FIRE_BULLET:
		this->HealthPoint-=3; //方晶//FIRE子弹攻击力为3，不影响移动
		break;
	case B_ICE_BULLET:
		this->HealthPoint-=2;
		this->bodyMorph = BODY_FROZEN;
		this->remainingTime = this->getRecoveryTime();
		break;
	}
}

// 判断怪物是否死亡
bool Monster::isDead(void)
{
	if(this->HealthPoint <= 0)
		return true;
	else
		return false;
}

// 怪物临死之前掉下子弹
//方晶//调用这个函数，说明怪物已经死亡
void Monster::generateBulletBox(void)
{
	//假设rand可以等可能地返回任何整数
	//则rand%100 == 0的概率为0.01

	using namespace Map;
	g_Map[x][y]=M_PASSAGE;//修改地图信息

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
//检查怪物状态，若不能移动则不移动
//移动到目标位置
/***********  严烈 *************
 *   可以被setPosition()代替  **
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