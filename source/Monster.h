#include <cstdlib>
#include <ctime>
#include "common.h"
#include "Map.h"

#pragma once

class Monster
{
public:
	Monster(int hp, BodyMorphism bm, int rtime);
	~Monster(void);
protected:
	int x, y;
	int HealthPoint;         //����ֵ
	BodyMorphism bodyMorph;  //�������ս������
	int remainingTime;       //�������������ս�״̬��Ҫ��ʱ��
public:
	//manipulation routine
	/********* ���� **********
	*  ���ù����λ��         *
	* BOSS���ƶ�ʱ��Ƚ�����  *
	* ���Գ�����map���κ�λ�� *
	**************************/
	virtual void setPosition(void);	
	// ���ܵ�����������ô˺���������ֵ����
	void gatAttack(BulletType b);

	//monster information
	// ����λ�� //wang
	Position getPosition(void);
	// �жϹ����Ƿ�����
	bool isDead(void);
	// ���ع�������״��
	BodyMorphism getBodyMorph(void);
	//����//��������ֵ
	int getHealthPoint(void);
	//����//����ʣ�����ʱ��
	int getRemainingTime(void);

	// action routine
	//�ƶ���Ŀ��λ��
	/* ���� *�����setPosition()����
	void MoveTo(int x, int y); 
	*/													
	// ��������֮ǰ�����ӵ�
	//����//ֱ�Ӹı�map��Ϣ
	void generateBulletBox(void);
	
	// ��������������ӵ��ĸ���
	virtual int getProbabilityConstant(void) = 0;
	// ���ñ������ӵ����к󣬻ظ��ƶ�������Ҫ��ʱ��
	virtual int getRecoveryTime(void) = 0;
	//����//�����ƶ��ٶȣ�ÿ������֡�ƶ�һ��
	//wang/�����жϹ�������
	virtual int getMoveSpeedConstant(void) = 0;
};
