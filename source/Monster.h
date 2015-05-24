#include <cstdlib>
#include <ctime>
#include "common.h"
#include "Map.h"

#pragma once

class Monster
{
public:
	Monster(int hp, BodyMorphism bm, int rtime);
	~Monster(void);
protected:
	int x, y;
	int HealthPoint;         //生命值
	BodyMorphism bodyMorph;  //正常，烧焦或冰冻
	int remainingTime;       //距离解除冰冻或烧焦状态需要的时间
public:
	//manipulation routine
	/********* 方晶 **********
	*  设置怪物的位置         *
	* BOSS在移动时会比较特殊  *
	* 可以出现在map的任何位置 *
	**************************/
	virtual void setPosition(void);	
	// 若受到攻击，则调用此函数，生命值减少
	void gatAttack(BulletType b);

	//monster information
	// 返回位置 //wang
	Position getPosition(void);
	// 判断怪物是否死亡
	bool isDead(void);
	// 返回怪物身体状体
	BodyMorphism getBodyMorph(void);
	//方晶//返回生命值
	int getHealthPoint(void);
	//方晶//返回剩余冰冻时间
	int getRemainingTime(void);

	// action routine
	//移动到目标位置
	/* 严烈 *这个用setPosition()代替
	void MoveTo(int x, int y); 
	*/													
	// 怪物临死之前掉下子弹
	//方晶//直接改变map信息
	void generateBulletBox(void);
	
	// 这个常数决定掉子弹的概率
	virtual int getProbabilityConstant(void) = 0;
	// 设置被特殊子弹击中后，回复移动能力需要的时间
	virtual int getRecoveryTime(void) = 0;
	//方晶//返回移动速度，每隔多少帧移动一次
	//wang/用于判断怪物类型
	virtual int getMoveSpeedConstant(void) = 0;
};
