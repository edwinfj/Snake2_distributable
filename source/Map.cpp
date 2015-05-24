#include "Map.h"

namespace Map
{
	int g_Map[MAP_WIDTH][MAP_HEIGHT];
	int g_iBigNum,g_iSmallNum,g_iBossNum;
void InitMap(void){
	for(int i=0; i<Map::MAP_WIDTH; i++)
		for(int j=0; j<Map::MAP_HEIGHT; j++)
			Map::g_Map[i][j] = Map::M_PASSAGE;
}

void LoadMap(int LevelNum){
	//生成地图路径
	string s("map\\");
	s += '0'+LevelNum;
	s += ".map";
	fstream fs(s.c_str());
		for(int j=0; j<Map::MAP_HEIGHT; j++)
		for(int i=0; i<Map::MAP_WIDTH; i++){
			fs >> Map::g_Map[i][j];
		}
	//方晶//设置怪物初始数量
	switch(LevelNum){
	case 1: 
		Map::g_iBossNum=0; Map::g_iSmallNum=3;
		Map::g_iBigNum=0;  break;
	case 2: 
		Map::g_iBossNum=0; Map::g_iSmallNum=5;
		Map::g_iBigNum=0;  break;
	case 3: 
		Map::g_iBossNum=0; Map::g_iSmallNum=3;
		Map::g_iBigNum=2;  break;
	case 4: 
		Map::g_iBossNum=0; Map::g_iSmallNum=3;
		Map::g_iBigNum=3;  break;
	case 5: 
		Map::g_iBossNum=0; Map::g_iSmallNum=2;
		Map::g_iBigNum=5;  break;
	case 6: 
		Map::g_iBossNum=1; Map::g_iSmallNum=3;
		Map::g_iBigNum=3;  break;
	}
}
}

