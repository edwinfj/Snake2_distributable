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

// ����ʳ���λ��
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
// ��ȡ������λ�ô��ڵ�ʱ��
vnReal32 Food::getDeltaTime(void)
{
	this->delta = timer.GetDelta();
	return this->delta;
}

// �����ĳ�ʼ���������ı�λ��+�����ڲ�������+�ı��ͼ״̬
void Food::FoodInit(void)
{
	using namespace Map;
	//��ԭ����map�ϵ�ʳ��������
	if(x>=0 && g_Map[x][y]==M_FOOD){
		g_Map[x][y]=M_PASSAGE;
	}

	srand(timer.GetSeconds());
	//����//ʳ���ʼλ���������
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

