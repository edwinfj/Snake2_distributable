#pragma once
#include "Monster.h"

class SmallMonster :
	public Monster
{
public:
	SmallMonster(void);
	SmallMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int sx,int sy);
	~SmallMonster(void);
	// 返回概率常数，这个常数决定掉子弹的概率
	int getProbabilityConstant(void);
	// 设置受到特殊子弹攻击后，回复移动能力所需要的时间
	int getRecoveryTime(void);
	//方晶//返回移动速度
	int getMoveSpeedConstant(void);

	//小怪物属性常数
	static const int hp = 4;                              //生命值
	static const BodyMorphism initBMorph = BODY_NORMAL;   //表现形态
	static const int initRTime = 0;   //Recovery Time的初始值
};
