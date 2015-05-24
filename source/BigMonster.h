#pragma once
#include "monster.h"

class BigMonster :
	public Monster
{
public:
	BigMonster(void);
	BigMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int bx,int by);
	~BigMonster(void);

	//��������Գ���
	static const int hp = 7;                                //����ֵ
	static const BodyMorphism initBMorph = BODY_NORMAL;     //������̬
	static const int initRTime = 0;    //�ָ�����ʱ��
	// ���ظ��ʳ�������������������ӵ��ĸ���
	int getProbabilityConstant(void);
	// �����ܵ������ӵ������󣬻ظ��ƶ���������Ҫ��ʱ��
	int getRecoveryTime(void);
	//����//�����ƶ��ٶ�
	int getMoveSpeedConstant(void);
};
