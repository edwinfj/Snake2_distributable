#include "Food.h"
#include <cstdlib>

Food::Food(void)
{
	x=-1;
	y=-1;
}

Food::~Food(void)
{
}

// 设置食物的位置
void Food::setPosition(int fx, int fy)
{
	using namespace Map;
	this->delta=0;
	this->x=fx;
	this->y=fy;
	g_Map[this->x][this->y]=M_FOOD;
	this->timer.Update();
}

Position Food::getPosition(void) 
{
	Position b;
	b.x=this->x;
	b.y=this->y;
	return b;
}
// 获取在所在位置存在的时间
vnReal32 Food::getDeltaTime(void)
{
	this->delta = timer.GetDelta();
	return this->delta;
}

// 真正的初始化函数，改变位置+重启内部计数器+改变地图状态
void Food::FoodInit(void)
{
	using namespace Map;
	//将原来的map上的食物标记清零
	if(x>=0 && g_Map[x][y]==M_FOOD){
		g_Map[x][y]=M_PASSAGE;
	}

	srand(timer.GetSeconds());
	//方晶//食物初始位置随机生成
	int f_x,f_y;
	do{
		f_x=(int)(rand()%32);
		f_y=(int)(rand()%24);
	}while(g_Map[f_x][f_y]!=M_PASSAGE);
	
	this->delta=0;
	this->x=f_x; this->y=f_y; 
	g_Map[this->x][this->y]=M_FOOD;
	this->timer.Update();
}

