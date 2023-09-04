/******************************************************************************
* 描述: 时钟
（1）获取设定区域时间，；
（2）检测闹钟；
******************************************************************************/

#pragma once
#include "alarm.h"
#include <list>

using std::string;
class CClock
{
	CAlarm p_Alarm;
	constexpr static const char* p_chszSettingFile{ "./Settings.ini" };
	constexpr static const char* p_chszLogFile{ "Log.txt" };
	const std::map<string, string> p_mapRegion{ { "北京", "Asia/Shanghai"}, {"东京" , "Asia/Tokyo"},
		{"伦敦" ,"Europe/London"}, {"华盛顿" , "America/New_York"} };
	
public:
	CClock();
	~CClock();
	typedef std::tuple<string, string, string> _ZonedTime;
	//返回储存时间的引用，使用Update_TimeAlarm后更新储存的时间
	const auto& GetTime() {
		return p_vctZonedTime;
	}
	bool Update_TimeAlarm(string& strAlarm, size_t& index);

	struct _LOG
	{
		//"更改时区","更改延迟时间","更改持续时间","新增闹钟","删除闹钟","更改闹钟"
		enum class eTYPE
		{
			REGION, DELAY, DURATION, ADD_ALARM, DELETED_ALARM, CHANGE_ALARM
		} eType{ 0 };
		std::chrono::sys_seconds srtTime;
		string strDetail;
	};
	std::list<_LOG> GetLog(std::bitset<6> type, std::chrono::local_days from, std::chrono::local_days to);
	const std::chrono::sys_seconds* GetFrontLogTime() {
		if (p_lstLog.empty())
		{
			return nullptr;
		}
		return &p_lstLog.front().srtTime;
	}
	static auto to_local(std::chrono::sys_seconds srtTime) {
		return   std::chrono::current_zone()->to_local(srtTime);
	}
	static auto now() {
		return round<std::chrono::seconds>(std::chrono::current_zone()->to_local(std::chrono::system_clock::now()));
	}
	bool ChangeRegion(string strRegion);
	bool ChangeSetting(_LOG::eTYPE eType, int n);
	std::tuple<string, int, int> GetSetting();
	const auto& GetAlert() {
		return p_Alarm.m_vctAlert;
	}
	bool ChangeAlarm(_LOG::eTYPE eType, CAlarm::_ALERT& srtAlert);
	
	std::chrono::sys_seconds UpdateTime();
	bool Stop() {
		return p_Alarm.Stop();
	}
	bool Delay() {
		return p_Alarm.Delay(now());
	}
	bool Save();

private:
	//用于返回地区，日期，时间
	std::vector<_ZonedTime> p_vctZonedTime;
	std::list<_LOG> p_lstLog;
};

