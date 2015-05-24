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

// 返回概率常数，这个常数决定怪物掉子弹的概率
int BossMonster::getProbabilityConstant(void)
{
	return 1;
}

// 设置受到特殊子弹攻击后，回复移动能力所需要的时间
int BossMonster::getRecoveryTime(void)
{
	return 2; //两个单位时间
}

//方晶//返回移动速度，每1帧移动一次
int BossMonster::getMoveSpeedConstant(void)
{
	return 1;
}

//方晶//BOSS移动方式
void BossMonster::setPosition(void)
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
		//BOSS可以躲进墙壁
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
	//将对应的map点设置怪物属性
	x=xx; y=yy;
	if(g_Map[x][y]!=M_WALL)
		g_Map[x][y]=M_MONSTER;
}

