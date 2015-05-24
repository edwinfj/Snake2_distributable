/* 'vnTimer.cpp' */

#include "vnTimer.h"

vnTimer::vnTimer(void)
{
	//�õ�Ӳ��ʽ��Ƶ�ʺ͵�ǰ����
	QueryPerformanceFrequency(&m_iFrequency);
	Update();
}

vnTimer::~vnTimer(void)
{
	m_iFrequency.QuadPart = 0;
	m_iLastQuery.QuadPart = 0;
}

//���¶�ʱ��
void vnTimer::Update(void)
{
	LARGE_INTEGER kTempTimer;
	time_t iTempTimeDate;

	//�õ���ǰ��ʱ����Ϣ,����ʱ���ֵ
	QueryPerformanceCounter(&kTempTimer);
	m_iDelta.QuadPart = kTempTimer.QuadPart - m_iLastQuery.QuadPart;

	//���浱ǰ��ʱ����Ϣ
	m_iLastQuery.QuadPart = kTempTimer.QuadPart;

	//�õ���ǰʱ��������
	time(&iTempTimeDate);
	m_pkTime = localtime(&iTempTimeDate);
}

//��һ�θ��µõ���deltaʱ��
vnReal32 vnTimer::GetDelta(void)
{
	//ת��Ϊ��������,����Ϊ��λ����delta
	return (vnReal32)(m_iDelta.QuadPart)/(vnReal32)(m_iFrequency.QuadPart);
}

//�õ�ϵͳ����
vnUInt32 vnTimer::GetSeconds(void)
{
	return m_pkTime->tm_sec;
}

//�õ�ϵͳ����
vnUInt32 vnTimer::GetMinutes(void)
{
	return m_pkTime->tm_min;
}

//�õ�ϵͳСʱ��
vnUInt32 vnTimer::GetHours(void)
{
	return m_pkTime->tm_hour;
}

//�õ�ϵͳ����
vnUInt32 vnTimer::GetDay(void)
{
	return m_pkTime->tm_mday;
}

//�õ�ϵͳ�·�
vnUInt32 vnTimer::GetMonth(void)
{
	return m_pkTime->tm_mon;
}

//�õ�ϵͳ���
vnUInt32 vnTimer::GetYear(void)
{
	return m_pkTime->tm_year;
}

