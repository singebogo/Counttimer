#pragma once
#include <iostream> 
#include <map> 
#include <string>
using namespace std; 

class CTimepiece
{
public:
	CTimepiece(void);
	~CTimepiece(void);

public:
	enum TYPES { MILLSEC=0, SEC, MIN } m_types;    // ��ʱ��ģʽ
	enum ELAPSE_TYPES { EMILLSEC = 10, ESEC=1000, EMIN=60000 } m_elapTimeTypes;    // ��ʱ����ʱʱ����

public:
	UINT hours;
	UINT minutes;			//����
    UINT seconds;			//��
    UINT milliseconds;		//����

	void InitTp();			// ��ʼ��ʱ��
	UINT_PTR GetId();		// ��ȡ��ʱ��ID
	void SetId(UINT_PTR id);	  // ���ü�ʱ��ID
	bool GetRuntag();		// ��ȡ��ʱ�����б�ǩ
	void SetRuntag(bool bRun);	  // ���ü�ʱ�����б�ǩ
	TYPES GetTypes();		// ��ȡ��ʱ������ģʽ
	void SetType(UINT type);	  // ���ü�ʱ������ģʽ
	UINT GetType();			// ��ȡ��ʱ�����е�ǰģʽ
	UINT GetElapTime();		// ��ȡ��ʱ�����е�ǰģʽʱ����
	void KeepTime();		// ��ʱ����
	void Counter();			// ������
	CString str();           // ��ʽ���ַ���

	// Enum �� string ֮��ӳ��
	// strings 
	map<TYPES, string> typesToString;
	string enumToString(TYPES type);

	map<std::string, TYPES> stringToTypes;
	TYPES StringToEnum(std::string type);

	// ��ʾ��
	UINT display();

protected:
	void SetElapse();	// ����ģʽ��ʱʱ����

private:	
	bool m_bRun;		// ��ʱ�����б�־
	UINT_PTR m_ID;		// ��ʱ��ID

	UINT m_btype;   // ��ǰģʽ
	UINT m_elapse;  // ʱ����
};

