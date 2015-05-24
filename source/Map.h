#include "common.h"
#include <iostream>
#include <fstream>
using namespace std;

#pragma once
namespace Map
{
	enum MapConstant
	{
		MAP_WIDTH    = 32,
		MAP_HEIGHT   = 24
	};
	//地图矩阵
	extern int g_Map[MAP_WIDTH][MAP_HEIGHT];
	//方晶//标记怪物的数量
	extern int g_iBigNum,g_iSmallNum,g_iBossNum;
	enum MapType
	{
		M_PASSAGE    = 0,//wang/constant
		M_WALL	     = 1,
		M_FOOD       = 2,//wang
		M_MONSTER    = 3,//wang/constant
		M_FIREBOX    = 4,//wang
		M_DOOR		 = 5,//wang/constant
		M_ICEBOX	 = 6//wang
	};
	void InitMap(void);
	void LoadMap(int);
}

