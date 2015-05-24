#pragma once
#include "Monster.h"

class BossMonster :
	public Monster
{
public:
	BossMonster(void);
	BossMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int bx,int by);
	~BossMonster(void);

	//Boss怪物属性常数
	static const int hp = 10;                                //生命值
	static const BodyMorphism initBMorph = BODY_NORMAL;      //表现形态
	static const int initRTime = 0;  //RecoveryTime的初始值
	// 返回概率常数，这个常数决定怪物掉子弹的概率
	int getProbabilityConstant(void);
	// 设置受到特殊子弹攻击后，回复移动能力所需要的时间
	int getRecoveryTime(void);
	//方晶//返回移动速度
	int getMoveSpeedConstant(void);
	void setPosition(void);
};
