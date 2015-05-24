#include "vnTimer.h"
#include "Map.h"
#include<gdiplus.h>

#pragma once
using namespace Gdiplus;
class Food
{
public:
	Food(void);//伪初始化函数，在建立vnGame对象时调用
	~Food(void);
private:
	int x, y;             // position
	vnReal32 delta;       //食物从产生开始存在的时间
	vnTimer timer;        //内置计时器
public:
	//方晶//真正的初始化函数
	void FoodInit(void);
	// 设置食物的位置
	void setPosition(int x, int y);

	Position getPosition(void);
	// 获取在所在位置存在的时间
	vnReal32 getDeltaTime(void);
};
