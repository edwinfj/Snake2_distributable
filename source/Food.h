#include "vnTimer.h"
#include "Map.h"
#include<gdiplus.h>

#pragma once
using namespace Gdiplus;
class Food
{
public:
	Food(void);//α��ʼ���������ڽ���vnGame����ʱ����
	~Food(void);
private:
	int x, y;             // position
	vnReal32 delta;       //ʳ��Ӳ�����ʼ���ڵ�ʱ��
	vnTimer timer;        //���ü�ʱ��
public:
	//����//�����ĳ�ʼ������
	void FoodInit(void);
	// ����ʳ���λ��
	void setPosition(int x, int y);

	Position getPosition(void);
	// ��ȡ������λ�ô��ڵ�ʱ��
	vnReal32 getDeltaTime(void);
};
