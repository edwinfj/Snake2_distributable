#pragma once
#include "Monster.h"

class SmallMonster :
	public Monster
{
public:
	SmallMonster(void);
	SmallMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int sx,int sy);
	~SmallMonster(void);
	// ���ظ��ʳ�������������������ӵ��ĸ���
	int getProbabilityConstant(void);
	// �����ܵ������ӵ������󣬻ظ��ƶ���������Ҫ��ʱ��
	int getRecoveryTime(void);
	//����//�����ƶ��ٶ�
	int getMoveSpeedConstant(void);

	//С�������Գ���
	static const int hp = 4;                              //����ֵ
	static const BodyMorphism initBMorph = BODY_NORMAL;   //������̬
	static const int initRTime = 0;   //Recovery Time�ĳ�ʼֵ
};
