#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <map>
#include <bitset>

class CAlarm
{
	const char* p_chszAlarmFile = "Alarm.txt";
	std::multimap<std::chrono::sys_seconds, size_t> p_mapAlarm;
	size_t nNextID{ 0 };
	std::bitset<512> p_srtHasID{ 0 };
public:
	struct _ALERT
	{
		short nID{ -1 };
		std::string strLabel;
		std::chrono::sys_seconds srtTime;
		//����Ϊ�̶�����գ�ֻѡ��һ��ĳһ��ʱΪ7,�����ڻ�һ�ܶ���ظ�ʱΪ0
		std::chrono::days srtCycleD{ 0 };
		//ѡ�����ڼ��ظ���������˳������
		std::vector<std::chrono::weekday> vrtCycleW;
		bool bEnable{ true };
	};


	std::chrono::minutes m_nDuration;
	std::chrono::minutes m_nDelay;
	CAlarm(int nDuration, int nDelay);

	_ALERT* IsAlarm(std::chrono::sys_seconds& srtTime);
	bool Stop();
	bool Delay(std::chrono::sys_seconds&& srtTime);
	bool Add(_ALERT& srtAlart);
	bool Change(_ALERT& srtAlart);
	bool Delete(short n);
	bool Save();
private:
	std::vector<_ALERT> p_vctAlert;
};

