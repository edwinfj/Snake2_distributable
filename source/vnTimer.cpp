/* 'vnTimer.cpp' */

#include "vnTimer.h"

vnTimer::vnTimer(void)
{
	//得到硬件式中频率和当前计数
	QueryPerformanceFrequency(&m_iFrequency);
	Update();
}

vnTimer::~vnTimer(void)
{
	m_iFrequency.QuadPart = 0;
	m_iLastQuery.QuadPart = 0;
}

//更新定时器
void vnTimer::Update(void)
{
	LARGE_INTEGER kTempTimer;
	time_t iTempTimeDate;

	//得到当前定时器信息,计算时间差值
	QueryPerformanceCounter(&kTempTimer);
	m_iDelta.QuadPart = kTempTimer.QuadPart - m_iLastQuery.QuadPart;

	//保存当前定时器信息
	m_iLastQuery.QuadPart = kTempTimer.QuadPart;

	//得到当前时间与日期
	time(&iTempTimeDate);
	m_pkTime = localtime(&iTempTimeDate);
}

//上一次更新得到的delta时间
vnReal32 vnTimer::GetDelta(void)
{
	//转换为浮点类型,以秒为单位计算delta
	return (vnReal32)(m_iDelta.QuadPart)/(vnReal32)(m_iFrequency.QuadPart);
}

//得到系统秒数
vnUInt32 vnTimer::GetSeconds(void)
{
	return m_pkTime->tm_sec;
}

//得到系统分数
vnUInt32 vnTimer::GetMinutes(void)
{
	return m_pkTime->tm_min;
}

//得到系统小时数
vnUInt32 vnTimer::GetHours(void)
{
	return m_pkTime->tm_hour;
}

//得到系统天数
vnUInt32 vnTimer::GetDay(void)
{
	return m_pkTime->tm_mday;
}

//得到系统月份
vnUInt32 vnTimer::GetMonth(void)
{
	return m_pkTime->tm_mon;
}

//得到系统年份
vnUInt32 vnTimer::GetYear(void)
{
	return m_pkTime->tm_year;
}

