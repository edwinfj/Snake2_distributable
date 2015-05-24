#include ".\smallmonster.h"

SmallMonster::SmallMonster(void)
:Monster(hp, initBMorph, initRTime)
{
}

SmallMonster::SmallMonster(int Health,BodyMorphism BodyMorph,int RemainTime,int sx,int sy)
:Monster(Health, BodyMorph, RemainTime)
{
	this->x=sx;
	this->y=sy;
	Map::g_Map[x][y]=Map::M_MONSTER;
}

SmallMonster::~SmallMonster(void)
{
}

// ���ظ��ʳ�������������������ӵ��ĸ���
int SmallMonster::getProbabilityConstant(void)
{
	return 3;
}

// �����ܵ������ӵ������󣬻ظ��ƶ���������Ҫ��ʱ��
int SmallMonster::getRecoveryTime(void)
{
	return 6;//6����λʱ��
}

//����//�����ƶ��ٶȣ�ÿ3֡�ƶ�һ��
int SmallMonster::getMoveSpeedConstant(void)
{
	return 3;
}
