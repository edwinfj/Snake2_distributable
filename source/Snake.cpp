#include "Snake.h"

Snake::Snake(void)
{
	bulletType = B_NORMAL_BULLET; //普通子弹
	headDirect = DIR_DOWN; //头朝下
	FIRE_left=ICE_left=0;//特殊子弹数量为0

	//初始化蛇的身体
	Body b;
	//临时用值，需要修改
	//方晶//已修改
	b.x = 2;
	b.y = 4;
	for(int i=0;i<6;i++){
		b.y-=1;
		bodies.push_back(b);
	}
}

Snake::~Snake(void)
{
}

//方晶//根据蛇头方向移动，返回蛇尾备用
Body Snake::Move(void)
{
	int head = 0;
	int tail = (int)bodies.size()-1;

	//取得尾部
	Body b = bodies[tail];
	
	//去掉原来的尾巴
	bodies.pop_back();

	//把新的头加到前面
	Body bb;
	switch(headDirect)
	{
	case DIR_DOWN:
		bb.y = bodies[head].y + 1;
		bb.x = bodies[head].x;
		break;
	case DIR_UP:
		bb.y = bodies[head].y - 1;
		bb.x = bodies[head].x;
		break;
	case DIR_RIGHT:
		bb.x = bodies[head].x + 1;
		bb.y = bodies[head].y;
		break;
	case DIR_LEFT:
		bb.x = bodies[head].x -1;
		bb.y = bodies[head].y;
		break;
	}
	bodies.push_front(bb);
	
	//方晶//返回原来的尾巴，如果吃到食物，需要用到
	return b;
}

void Snake::ClearForLoad(void)
{
	bodies.clear();
}
//蛇的尾部增加一个单位长度
void Snake::AddBody(Body b)
{
	bodies.push_back(b);
}

// 返回蛇头
Body Snake::getHead(void)
{
	return bodies[head];
}

// 返回蛇尾
Body Snake::getTail(void)
{
	int tail = (int)bodies.size() - 1;
	return bodies[tail];
}
//方晶//返回蛇身位置//wang
Body Snake::getBodyCord(int i)
{
	if(i<this->getBodyNum())
		return bodies[i];
}
//方晶//返回蛇身数
int Snake::getBodyNum(void)
{
	return (int)(bodies.size());
}

//方晶//重新调用构造函数
void Snake::TotalInit(void)
{
	bulletType = B_NORMAL_BULLET; //普通子弹
	headDirect = DIR_DOWN; //头朝下
	FIRE_left=ICE_left=0;//特殊子弹数量为0

	bodies.clear();
	//初始化蛇的身体
	Body b;
	//临时用值，需要修改
	//方晶//已修改
	b.x = 2;
	b.y = 4;
	for(int i=0;i<6;i++){
		b.y-=1;
		bodies.push_back(b);
	}
}

//方晶//levelstart重设蛇的坐标
void Snake::SnakeInit(void)
{
	int num=this->getBodyNum();
	headDirect=DIR_DOWN;

	for(int i=0;i<num;i++){
		bodies[i].x=2;
		bodies[i].y=3-i;
	}
	while(bodies.size()<6){
		Body b;
		b.x=bodies[bodies.size()-1].x;
		b.y=bodies[bodies.size()-1].y-1;
		bodies.push_back(b);
	}
}
//方晶//返回FIRE剩余弹量
int Snake::getFIREnum(void)
{
	return FIRE_left;
}
//方晶//返回ICE剩余弹量
int Snake::getICEnum(void)
{
	return ICE_left;
}
// 返回蛇头指向
Direction Snake::getHeadDirect(void)
{
	return headDirect;
}

// 设置蛇头指向
void Snake::setHeadDirect(Direction rhs)
{
	switch(headDirect){
	case DIR_UP:
		if(rhs!=DIR_DOWN)
			headDirect = rhs;
		break;
	case DIR_DOWN:
		if(rhs!=DIR_UP)
			headDirect=rhs;
		break;
	case DIR_LEFT:
		if(rhs!=DIR_RIGHT)
			headDirect = rhs;
		break;
	case DIR_RIGHT:
		if(rhs!=DIR_LEFT)
			headDirect = rhs;
		break;
	}
}
void Snake::resetHeadDirect(Direction rhs)
{
	headDirect=rhs;
}
// 减少蛇的长度，去掉尾巴
void Snake::DeleteBody(void)
{
	if(bodies.size() > 0)
		bodies.pop_back();
}

// 判断蛇是否已死亡
bool Snake::isDead(void)
{
	if(bodies.size() < 3)
		return true; //蛇身小于3节，死亡
	for(int i=1;i<(int)(bodies.size());i++){
		if(bodies[head].x==bodies[i].x &&
			bodies[head].y==bodies[i].y)
			return true;//蛇头撞上蛇身，死亡
	}
	return false;
}

// 返回子弹的类型
BulletType Snake::getBulletType(void)
{
	return bulletType;
}

// 设置子弹的类型
void Snake::setBulletType(BulletType rhs)
{
	bulletType = rhs;
}
//方晶//重设蛇头位置
bool Snake::ResetHead(void)
{
	using namespace Map;
	Body b1=bodies[1],b2=bodies[2],b;

	b.x=b1.x-1; b.y=b1.y;
	if(!(b.x==b2.x && b.y==b2.y) && 
		g_Map[b.x][b.y]!=M_WALL &&
		g_Map[b.x][b.y]!=M_MONSTER &&
		g_Map[b.x][b.y]!=M_DOOR){
		bodies.pop_front();
		bodies.push_front(b);
		headDirect=DIR_LEFT;
		return true;
	}
	b.x=b1.x+1; b.y=b1.y;
	if(!(b.x==b2.x && b.y==b2.y) && 
		g_Map[b.x][b.y]!=M_WALL &&
		g_Map[b.x][b.y]!=M_MONSTER &&
		g_Map[b.x][b.y]!=M_DOOR){
		bodies.pop_front();
		bodies.push_front(b);
		headDirect=DIR_RIGHT;
		return true;
	}
	b.x=b1.x; b.y=b1.y-1;
	if(!(b.x==b2.x && b.y==b2.y) && 
		g_Map[b.x][b.y]!=M_WALL &&
		g_Map[b.x][b.y]!=M_MONSTER &&
		g_Map[b.x][b.y]!=M_DOOR){
		bodies.pop_front();
		bodies.push_front(b);
		headDirect=DIR_UP;
		return true;
	}
	b.x=b1.x; b.y=b1.y+1;
	if(!(b.x==b2.x && b.y==b2.y) && 
		g_Map[b.x][b.y]!=M_WALL &&
		g_Map[b.x][b.y]!=M_MONSTER &&
		g_Map[b.x][b.y]!=M_DOOR){
		bodies.pop_front();
		bodies.push_front(b);
		headDirect=DIR_DOWN;
		return true;
	}
	return false;
}

//方晶//设置FIRE子弹的初始数量
void Snake::setFIREnum(void)
{
	FIRE_left+=5;
}
void Snake::setFIREnum(int num)
{
	FIRE_left=num;
}
//方晶//设置ICE子弹的初始数量
void Snake::setICEnum(void)
{
	ICE_left+=8;
}
void Snake::setICEnum(int num)
{
	ICE_left=num;
}
//方晶//减小特殊子弹数量
void Snake::DeleteBullet(void)
{
	switch(bulletType){
	case B_FIRE_BULLET:
		FIRE_left--;
		if(FIRE_left<=0)
			bulletType=B_NORMAL_BULLET;
		break;
	case B_ICE_BULLET:
		ICE_left--;
		if(ICE_left<=0)
			bulletType=B_NORMAL_BULLET;
		break;
	}
}

// 渲染蛇的身体
void Snake::Render(void)
{
	//TODO:
	//将蛇画在画布上
	
}

//// 发射子弹，返回活动子弹对象
//ActiveBullet Snake::Shoot(void)
//{
//	ActiveBullet b(bodies[head].x, bodies[head].y, headDirect, bulletType);
//	b.SetTimer();
//	return ActiveBullet(b);
//}
