#include <deque>
#include<windows.h>
#include "common.h"
#include "Map.h"

using namespace std;
//using namespace Gdiplus;

#pragma once

class Snake
{
public:
	Snake(void);
	~Snake(void);

private:
	deque<Body> bodies;        //存储蛇身体各节的坐标
	BulletType bulletType;     //蛇的子弹类型
	Direction headDirect;      //蛇头的指向

	int FIRE_left, ICE_left;
	const static int head = 0; //head的下标
	
public:
	//snake information
	// 返回蛇头
	Body getHead(void);
	// 返回蛇尾
	Body getTail(void);
	// 返回蛇头指向//wang
	Direction getHeadDirect(void);
	// 判断蛇是否已死亡
	bool isDead(void);
	// 返回子弹的类型//wang
	BulletType getBulletType(void);
	//方晶//返回蛇身数//wang
	int getBodyNum(void);
	//方晶//返回FIRE剩余弹量
	int getFIREnum(void);
	//方晶//返回ICE剩余弹量
	int getICEnum(void);
	//方晶//返回蛇身位置//wang
	Body getBodyCord(int);

	//manipulation routine
	//方晶//清空bodies，用于Load初始化
	void ClearForLoad(void);
	//方晶//重新调用构造函数
	void TotalInit(void);
	//方晶//levelstart重设蛇的坐标
	void SnakeInit(void);
	//方晶//改变蛇头位置。如果被卡死，则返回false
	bool ResetHead(void);
	//方晶//根据蛇头方向移动
	Body Move(void);
	//蛇的尾部增加一个单位长度
	void AddBody(Body);
	// 减少蛇的长度,去掉尾巴
	void DeleteBody(void);
	//方晶//减少特殊子弹数量
	void DeleteBullet(void);
	// 设置蛇头指向
	void setHeadDirect(Direction rhs);
	void resetHeadDirect(Direction rhs);
	// 设置子弹的类型
	void setBulletType(BulletType rhs);
	//方晶//设置FIRE子弹的初始数量
	void setFIREnum(void);
	void setFIREnum(int);
	//方晶//设置ICE子弹的初始数量
	void setICEnum(void);
	void setICEnum(int);
	// 渲染蛇的身体
	void Render(void);
	//// 发射子弹，返回活动子弹对象
	//ActiveBullet Shoot(void);
};
