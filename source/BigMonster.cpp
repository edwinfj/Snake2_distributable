#include "BigMonster.h"

BigMonster::BigMonster(void)
:Monster(hp, initBMorph, initRTime)
{
}

BigMonster::BigMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int bx,int by)
:Monster(Health, BodyMorph, RemainTime)
{
	this->x=bx;
	this->y=by;
	Map::g_Map[x][y]=Map::M_MONSTER;
}

BigMonster::~BigMonster(void)
{
}

// 返回概率常数，这个常数决定掉子弹的概率
int BigMonster::getProbabilityConstant(void)
{
	return 2;
}

// 设置受到特殊子弹攻击后，回复移动能力所需要的时间
//方晶//恢复时间按与怪物类型及子弹类型有关
int BigMonster::getRecoveryTime(void)
{
	return 4;
}

//方晶//返回移动速度，每2帧移动一次
int BigMonster::getMoveSpeedConstant(void)
{
	return 2;
}
