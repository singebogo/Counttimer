#include "stdafx.h"
#include "Timepiece.h"
#include <iostream>
#include <string>

CTimepiece::CTimepiece(void)
{
	InitTp();
	m_bRun = false;
	m_ID = -1;
	m_btype = MILLSEC;   // Ĭ��Ϊ����ģʽ
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
	m_btype = MILLSEC;   // Ĭ��Ϊ����ģʽ
	SetElapse();
}


void CTimepiece::InitTp()
{
	// ������
	hours = 0;			//Сʱ
	minutes = 0;        //����
    seconds = 0;        //��
    milliseconds = 0;   //����
}

// ��ȡ��ʱ��ID
UINT_PTR CTimepiece::GetId()
{
	return m_ID;
}

// ���ü�ʱ��ID
void CTimepiece::SetId(UINT_PTR id)
{
	m_ID = id;
}

// ��ȡ��ʱ�����б�ǩ
bool CTimepiece::GetRuntag()
{
	return m_bRun;
}

// ���ü�ʱ�����б�ǩ
void CTimepiece::SetRuntag(bool bRun)
{
	m_bRun = bRun;
}

// ��ȡ��ʱ������ģʽ
CTimepiece::TYPES CTimepiece::GetTypes()
{
	return m_types;
}

// ���ü�ʱ������ģʽ,�����ü�ʱ��ʱ��
void CTimepiece::SetType(UINT type)
{
	// ö�ٵ������� �������ö������ ��С��2���ݣ���ȥ1��
	m_btype =  type;
	SetElapse();
}

// ��ȡ��ʱ�����е�ǰģʽ
UINT CTimepiece::GetType()
{
	return m_btype;
}

// ���ö�ʱ��ʱ����
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
		// ����24Сʱ ������Ϊ0
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

