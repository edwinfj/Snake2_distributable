/* 'vnTimer.h' */

#ifndef _VNTIMER_H
#define _VNTIMER_H

/* Vino 基本类型文件 */
#include "vnDataTypes.h"
/* windows 头文件 */
#include <windows.h>
/* std c lib */
#include <time.h>


//Vino timer class
class vnTimer
{
protected:
	//硬件定时器变量
	LARGE_INTEGER m_iFrequency;
	LARGE_INTEGER m_iLastQuery;
	LARGE_INTEGER m_iDelta;

	//时间和日期变量
	tm * m_pkTime;

public:
	vnTimer(void);
	~vnTimer(void);

	//更新定时器变量
	void Update(void);

	//返回定时变量
	vnReal32 GetDelta(void);
	vnUInt32 GetSeconds(void);
	vnUInt32 GetMinutes(void);
	vnUInt32 GetHours(void);

	//PC上返回自1990.1.1到当前时刻的时间
	vnUInt32 GetDay(void);
	vnUInt32 GetMonth(void);
	vnUInt32 GetYear(void);
};

#endif