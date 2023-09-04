#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <map>
#include <bitset>
#include <array>
class CAlarm
{
	const char* p_chszAlarmFile = "Alarm.txt";
	std::multimap<std::chrono::local_seconds, size_t> p_mapAlarm;
	size_t nNextID{ 0 };
	std::bitset<512> p_srtHasID{ 0 };
public:
	struct _ALERT
	{
		short nID{ -1 };
		std::string strLabel;
		std::chrono::local_seconds srtTime;
		//周期为固定间隔日，只选择一周某一天时为7,无周期或一周多次重复时为0
		std::chrono::days srtCycleD{ 0 };
		//选择星期几重复，根据c_encoding周日为0
		std::bitset<7> CycleW;
		bool bEnable{ true };
	};
	std::vector<_ALERT> m_vctAlert;

	std::chrono::minutes m_nDuration;
	std::chrono::minutes m_nDelay;
	CAlarm(int nDuration, int nDelay);

	bool IsAlarm(std::chrono::local_seconds& srtTime, size_t& index);
	bool Stop();
	bool Delay(std::chrono::local_seconds&& srtTime);
	bool Add(_ALERT& srtAlart);
	bool Change(_ALERT& srtAlart);
	bool Delete(short n);
	bool Save();
	static std::array<std::string, 5> to_string(const _ALERT&);
	
};

