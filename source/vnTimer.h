/* 'vnTimer.h' */

#ifndef _VNTIMER_H
#define _VNTIMER_H

/* Vino ���������ļ� */
#include "vnDataTypes.h"
/* windows ͷ�ļ� */
#include <windows.h>
/* std c lib */
#include <time.h>


//Vino timer class
class vnTimer
{
protected:
	//Ӳ����ʱ������
	LARGE_INTEGER m_iFrequency;
	LARGE_INTEGER m_iLastQuery;
	LARGE_INTEGER m_iDelta;

	//ʱ������ڱ���
	tm * m_pkTime;

public:
	vnTimer(void);
	~vnTimer(void);

	//���¶�ʱ������
	void Update(void);

	//���ض�ʱ����
	vnReal32 GetDelta(void);
	vnUInt32 GetSeconds(void);
	vnUInt32 GetMinutes(void);
	vnUInt32 GetHours(void);

	//PC�Ϸ�����1990.1.1����ǰʱ�̵�ʱ��
	vnUInt32 GetDay(void);
	vnUInt32 GetMonth(void);
	vnUInt32 GetYear(void);
};

#endif