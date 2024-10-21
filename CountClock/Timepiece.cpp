#include "stdafx.h"
#include "Timepiece.h"
#include <iostream>
#include <string>

CTimepiece::CTimepiece(void)
{
	InitTp();
	m_bRun = false;
	m_ID = -1;
	m_btype = MILLSEC;   // 默认为毫秒模式
	SetElapse();

	typesToString[MILLSEC] = "MillSec",
    typesToString[SEC] = "Sec";
	typesToString[MIN] = "Min";

	stringToTypes["MillSec"] = MILLSEC;
	stringToTypes["Sec"] = SEC;
	stringToTypes["Min"] = MIN;
}


CTimepiece::~CTimepiece(void)
{
	InitTp();
	m_ID = -1;
	m_btype = MILLSEC;   // 默认为毫秒模式
	SetElapse();
}


void CTimepiece::InitTp()
{
	// 计数器
	hours = 0;			//小时
	minutes = 0;        //分钟
    seconds = 0;        //秒
    milliseconds = 0;   //毫秒
}

// 获取计时器ID
UINT_PTR CTimepiece::GetId()
{
	return m_ID;
}

// 设置计时器ID
void CTimepiece::SetId(UINT_PTR id)
{
	m_ID = id;
}

// 获取计时器运行标签
bool CTimepiece::GetRuntag()
{
	return m_bRun;
}

// 设置计时器运行标签
void CTimepiece::SetRuntag(bool bRun)
{
	m_bRun = bRun;
}

// 获取计时器运行模式
CTimepiece::TYPES CTimepiece::GetTypes()
{
	return m_types;
}

// 设置计时器运行模式,并重置计时器时间
void CTimepiece::SetType(UINT type)
{
	// 枚举的上限是 大于最大枚举量的 最小的2的幂，减去1；
	m_btype =  type;
	SetElapse();
}

// 获取计时器运行当前模式
UINT CTimepiece::GetType()
{
	return m_btype;
}

// 设置定时器时间间隔
void CTimepiece::SetElapse()
{
	switch(m_btype)
	{
	case MILLSEC:
		{
			m_elapse = EMILLSEC;
			break;
		}
	case MIN:
		{
			m_elapse = EMIN;
			break;
		}
	case SEC:
		{
			m_elapse =  ESEC;
			break;
		}
	default:
		{
			m_elapse = EMILLSEC;
			break;
		}
	}
}

UINT CTimepiece::GetElapTime()
{
	return m_elapse;
}


void CTimepiece::Counter()
{
	if(m_btype == MILLSEC)
	{
		milliseconds += 10;
		if (milliseconds == 1000)
		{
			milliseconds = 0;
			seconds++;
		}
	}
	else if(m_btype == SEC)
	{
		milliseconds = 0;
		seconds++;		
	}
	else if(MIN == m_btype)
	{
		milliseconds = 0;
		seconds = 0;
		minutes ++;		
	}

	if (seconds == 60)
	{
		seconds = 0;
		minutes++;
	}

	if(minutes == 60)
	{
		minutes = 0;
		hours++;
		// 超过24小时 则重置为0
		if(hours == 24)
		{
			hours=0;
		}
	}
}

void CTimepiece::KeepTime()
{
	switch(m_btype)
	{
	case MILLSEC:
	case MIN:
	case SEC:
	default:
		Counter();
	}
}

CString CTimepiece::str()
{
	CString str;
	switch(m_btype)
	{
	case MIN:
		{
			str.Format("%02i : %02i", hours, minutes);
		}
	case MILLSEC:
		{
			str.Format("%02i : %02i : %02i : %002i", hours, minutes, seconds, milliseconds);
		}
	case SEC:
		{
			str.Format("%02i : %02i : %02i", hours, minutes, seconds);
		}
	default:
		{
			str.Format("%02i : %02i : %02i : %002i", hours, minutes, seconds, milliseconds);
		}
	}
	
	return str;
}

string CTimepiece::enumToString(TYPES type)
{
	return typesToString[type];
}

CTimepiece::TYPES CTimepiece::StringToEnum(string type)
{
	return stringToTypes[type];
}

UINT CTimepiece::display()
{
	switch(m_btype)
	{
	case MIN:
		{
			return minutes;
		}
	case MILLSEC:
	case SEC:
	default:
		{
			return seconds;
		}
	}
}

