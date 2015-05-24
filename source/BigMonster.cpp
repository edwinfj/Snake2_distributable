#include "BigMonster.h"

BigMonster::BigMonster(void)
:Monster(hp, initBMorph, initRTime)
{
}

BigMonster::BigMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int bx,int by)
:Monster(Health, BodyMorph, RemainTime)
{
	this->x=bx;
	this->y=by;
	Map::g_Map[x][y]=Map::M_MONSTER;
}

BigMonster::~BigMonster(void)
{
}

// ���ظ��ʳ�������������������ӵ��ĸ���
int BigMonster::getProbabilityConstant(void)
{
	return 2;
}

// �����ܵ������ӵ������󣬻ظ��ƶ���������Ҫ��ʱ��
//����//�ָ�ʱ�䰴��������ͼ��ӵ������й�
int BigMonster::getRecoveryTime(void)
{
	return 4;
}

//����//�����ƶ��ٶȣ�ÿ2֡�ƶ�һ��
int BigMonster::getMoveSpeedConstant(void)
{
	return 2;
}
