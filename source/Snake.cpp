#include "Snake.h"

Snake::Snake(void)
{
	bulletType = B_NORMAL_BULLET; //��ͨ�ӵ�
	headDirect = DIR_DOWN; //ͷ����
	FIRE_left=ICE_left=0;//�����ӵ�����Ϊ0

	//��ʼ���ߵ�����
	Body b;
	//��ʱ��ֵ����Ҫ�޸�
	//����//���޸�
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

//����//������ͷ�����ƶ���������β����
Body Snake::Move(void)
{
	int head = 0;
	int tail = (int)bodies.size()-1;

	//ȡ��β��
	Body b = bodies[tail];
	
	//ȥ��ԭ����β��
	bodies.pop_back();

	//���µ�ͷ�ӵ�ǰ��
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
	
	//����//����ԭ����β�ͣ�����Ե�ʳ���Ҫ�õ�
	return b;
}

void Snake::ClearForLoad(void)
{
	bodies.clear();
}
//�ߵ�β������һ����λ����
void Snake::AddBody(Body b)
{
	bodies.push_back(b);
}

// ������ͷ
Body Snake::getHead(void)
{
	return bodies[head];
}

// ������β
Body Snake::getTail(void)
{
	int tail = (int)bodies.size() - 1;
	return bodies[tail];
}
//����//��������λ��//wang
Body Snake::getBodyCord(int i)
{
	if(i<this->getBodyNum())
		return bodies[i];
}
//����//����������
int Snake::getBodyNum(void)
{
	return (int)(bodies.size());
}

//����//���µ��ù��캯��
void Snake::TotalInit(void)
{
	bulletType = B_NORMAL_BULLET; //��ͨ�ӵ�
	headDirect = DIR_DOWN; //ͷ����
	FIRE_left=ICE_left=0;//�����ӵ�����Ϊ0

	bodies.clear();
	//��ʼ���ߵ�����
	Body b;
	//��ʱ��ֵ����Ҫ�޸�
	//����//���޸�
	b.x = 2;
	b.y = 4;
	for(int i=0;i<6;i++){
		b.y-=1;
		bodies.push_back(b);
	}
}

//����//levelstart�����ߵ�����
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
//����//����FIREʣ�൯��
int Snake::getFIREnum(void)
{
	return FIRE_left;
}
//����//����ICEʣ�൯��
int Snake::getICEnum(void)
{
	return ICE_left;
}
// ������ͷָ��
Direction Snake::getHeadDirect(void)
{
	return headDirect;
}

// ������ͷָ��
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
// �����ߵĳ��ȣ�ȥ��β��
void Snake::DeleteBody(void)
{
	if(bodies.size() > 0)
		bodies.pop_back();
}

// �ж����Ƿ�������
bool Snake::isDead(void)
{
	if(bodies.size() < 3)
		return true; //����С��3�ڣ�����
	for(int i=1;i<(int)(bodies.size());i++){
		if(bodies[head].x==bodies[i].x &&
			bodies[head].y==bodies[i].y)
			return true;//��ͷײ����������
	}
	return false;
}

// �����ӵ�������
BulletType Snake::getBulletType(void)
{
	return bulletType;
}

// �����ӵ�������
void Snake::setBulletType(BulletType rhs)
{
	bulletType = rhs;
}
//����//������ͷλ��
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

//����//����FIRE�ӵ��ĳ�ʼ����
void Snake::setFIREnum(void)
{
	FIRE_left+=5;
}
void Snake::setFIREnum(int num)
{
	FIRE_left=num;
}
//����//����ICE�ӵ��ĳ�ʼ����
void Snake::setICEnum(void)
{
	ICE_left+=8;
}
void Snake::setICEnum(int num)
{
	ICE_left=num;
}
//����//��С�����ӵ�����
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

// ��Ⱦ�ߵ�����
void Snake::Render(void)
{
	//TODO:
	//���߻��ڻ�����
	
}

//// �����ӵ������ػ�ӵ�����
//ActiveBullet Snake::Shoot(void)
//{
//	ActiveBullet b(bodies[head].x, bodies[head].y, headDirect, bulletType);
//	b.SetTimer();
//	return ActiveBullet(b);
//}
