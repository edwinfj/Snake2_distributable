#include ".\smallmonster.h"

SmallMonster::SmallMonster(void)
:Monster(hp, initBMorph, initRTime)
{
}

SmallMonster::SmallMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int sx,int sy)
:Monster(Health, BodyMorph, RemainTime)
{
	this->x=sx;
	this->y=sy;
	Map::g_Map[x][y]=Map::M_MONSTER;
}

SmallMonster::~SmallMonster(void)
{
}

// 返回概率常数，这个常数决定掉子弹的概率
int SmallMonster::getProbabilityConstant(void)
{
	return 3;
}

// 设置受到特殊子弹攻击后，回复移动能力所需要的时间
int SmallMonster::getRecoveryTime(void)
{
	return 6;//6个单位时间
}

//方晶//返回移动速度，每3帧移动一次
int SmallMonster::getMoveSpeedConstant(void)
{
	return 3;
}
