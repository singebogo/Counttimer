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
	enum TYPES { MILLSEC=0, SEC, MIN } m_types;    // 计时器模式
	enum ELAPSE_TYPES { EMILLSEC = 10, ESEC=1000, EMIN=60000 } m_elapTimeTypes;    // 计时器定时时间间隔

public:
	UINT hours;
	UINT minutes;			//分钟
    UINT seconds;			//秒
    UINT milliseconds;		//毫秒

	void InitTp();			// 初始化时间
	UINT_PTR GetId();		// 获取计时器ID
	void SetId(UINT_PTR id);	  // 设置计时器ID
	bool GetRuntag();		// 获取计时器运行标签
	void SetRuntag(bool bRun);	  // 设置计时器运行标签
	TYPES GetTypes();		// 获取计时器运行模式
	void SetType(UINT type);	  // 设置计时器运行模式
	UINT GetType();			// 获取计时器运行当前模式
	UINT GetElapTime();		// 获取计时器运行当前模式时间间隔
	void KeepTime();		// 计时函数
	void Counter();			// 计数器
	CString str();           // 格式化字符串

	// Enum 与 string 之间映射
	// strings 
	map<TYPES, string> typesToString;
	string enumToString(TYPES type);

	map<std::string, TYPES> stringToTypes;
	TYPES StringToEnum(std::string type);

	// 显示屏
	UINT display();

protected:
	void SetElapse();	// 设置模式超时时间间隔

private:	
	bool m_bRun;		// 定时器运行标志
	UINT_PTR m_ID;		// 定时器ID

	UINT m_btype;   // 当前模式
	UINT m_elapse;  // 时间间隔
};

