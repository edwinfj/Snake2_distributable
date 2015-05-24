#pragma once
#include "Monster.h"

class BossMonster :
	public Monster
{
public:
	BossMonster(void);
	BossMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int bx,int by);
	~BossMonster(void);

	//Boss�������Գ���
	static const int hp = 10;                                //����ֵ
	static const BodyMorphism initBMorph = BODY_NORMAL;      //������̬
	static const int initRTime = 0;  //RecoveryTime�ĳ�ʼֵ
	// ���ظ��ʳ����������������������ӵ��ĸ���
	int getProbabilityConstant(void);
	// �����ܵ������ӵ������󣬻ظ��ƶ���������Ҫ��ʱ��
	int getRecoveryTime(void);
	//����//�����ƶ��ٶ�
	int getMoveSpeedConstant(void);
	void setPosition(void);
};
