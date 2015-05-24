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
	deque<Body> bodies;        //�洢��������ڵ�����
	BulletType bulletType;     //�ߵ��ӵ�����
	Direction headDirect;      //��ͷ��ָ��

	int FIRE_left, ICE_left;
	const static int head = 0; //head���±�
	
public:
	//snake information
	// ������ͷ
	Body getHead(void);
	// ������β
	Body getTail(void);
	// ������ͷָ��//wang
	Direction getHeadDirect(void);
	// �ж����Ƿ�������
	bool isDead(void);
	// �����ӵ�������//wang
	BulletType getBulletType(void);
	//����//����������//wang
	int getBodyNum(void);
	//����//����FIREʣ�൯��
	int getFIREnum(void);
	//����//����ICEʣ�൯��
	int getICEnum(void);
	//����//��������λ��//wang
	Body getBodyCord(int);

	//manipulation routine
	//����//���bodies������Load��ʼ��
	void ClearForLoad(void);
	//����//���µ��ù��캯��
	void TotalInit(void);
	//����//levelstart�����ߵ�����
	void SnakeInit(void);
	//����//�ı���ͷλ�á�������������򷵻�false
	bool ResetHead(void);
	//����//������ͷ�����ƶ�
	Body Move(void);
	//�ߵ�β������һ����λ����
	void AddBody(Body);
	// �����ߵĳ���,ȥ��β��
	void DeleteBody(void);
	//����//���������ӵ�����
	void DeleteBullet(void);
	// ������ͷָ��
	void setHeadDirect(Direction rhs);
	void resetHeadDirect(Direction rhs);
	// �����ӵ�������
	void setBulletType(BulletType rhs);
	//����//����FIRE�ӵ��ĳ�ʼ����
	void setFIREnum(void);
	void setFIREnum(int);
	//����//����ICE�ӵ��ĳ�ʼ����
	void setICEnum(void);
	void setICEnum(int);
	// ��Ⱦ�ߵ�����
	void Render(void);
	//// �����ӵ������ػ�ӵ�����
	//ActiveBullet Shoot(void);
};
