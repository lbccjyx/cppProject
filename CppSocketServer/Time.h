#ifndef _TIME_H_
#define _TIME_H_
#pragma once

#include <ctime>
#include <chrono>
class CTime
{
public:
	CTime()
		: m_sNow(new tm)
		, m_timePoint(  std::chrono::high_resolution_clock::now() )
		, m_i64Now(time(nullptr))
	{
		localtime_s(m_sNow, &m_i64Now);
	}
	~CTime() {}

	int GetCurWeekDay()
	{
		if (!m_sNow)
			return 0;
		if (!m_sNow->tm_wday)
			return 7;
		return m_sNow->tm_wday;
	}

	int GetCurMonth()
	{
		if (!m_sNow)
			return 0;
		return m_sNow->tm_mon + 1;
	}

	int GetCurMonDay()
	{
		if (!m_sNow)
			return 0;
		return m_sNow->tm_mday + 1;
	}

	unsigned int GetCurYYMMDDHHMM()
	{
		if (!m_sNow)
			return 0;
		int nYear	= m_sNow->tm_year % 100;
		int nMonth	= m_sNow->tm_mon + 1;
		int nMonDay = m_sNow->tm_mday;
		int nHour	= m_sNow->tm_hour;
		int nMin	= m_sNow->tm_min;
		return nYear * 100000000 + nMonth * 1000000 + nMonDay * 10000 + nHour * 100 + nMin;
	}

	unsigned int GetCurHHMMSS()
	{
		if (!m_sNow)
			return 0;
		return m_sNow->tm_hour * 10000 + m_sNow->tm_min * 100 + m_sNow->tm_sec;
	}

	int GetCurHHMM()
	{
		if (!m_sNow)
			return 0;
		return m_sNow->tm_hour * 100 + m_sNow->tm_min;
	}

	const std::chrono::seconds GetTimePoint() const
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_timePoint);
	}

	void Update()
	{
		m_i64Now = time(nullptr);
		localtime_s(m_sNow, &m_i64Now);
		m_timePoint = std::chrono::high_resolution_clock::now();
	}

protected:
private:
	time_t m_i64Now = 0;
	tm*	   m_sNow	= nullptr;

	std::chrono::high_resolution_clock::time_point m_timePoint;
};

CTime* cAtime = new CTime();
#define Time (*cAtime)
#define CurWeekDay Time.GetCurWeekDay()	 //days since Monday - [1, 7]
#define CurMonth Time.GetCurMonth()		 //days since Monday - [1, 12]
#define CurMonDay Time.GetCurMonDay()	 //days since Monday - [1, 31]
#define CurYYMMDDHHMM Time.GetCurYYMMDDHHMM()
#define CurHHMMSS Time.GetCurHHMMSS()
#define CurHHMM Time.GetCurHHMM()
#endif	// !_TIME_H_
