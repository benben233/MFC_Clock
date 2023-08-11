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
	const char* p_chszSettingFile{ "./Settings.ini" };
	const char* p_chszLogFile{ "Log.txt" };
	std::map<string, string> p_mapRegion{ { "北京", "Asia/Shanghai"}, {"东京" , "Asia/Tokyo"},
		{"伦敦" ,"Europe/London"}, {"华盛顿" , "America/New_York"} };


public:
	CClock();
	~CClock();
	typedef std::tuple<string, string, string> _ZonedTime;
	//用于返回地区，日期，时间
	std::vector<_ZonedTime> m_vctZonedTime;

	struct _LOG
	{
		enum class eTYPE
		{
			REGION, DELAY, DURATION, ADD_ALARM, DELETED_ALARM, CHANGE_ALARM
		} eType{ 0 };
		std::chrono::sys_seconds srtTime;
		string strDetail;
	};
	constexpr static const char* m_chszLog[] = { "更改时区","更改延迟时间","更改持续时间","新增闹钟","删除闹钟","更改闹钟" };
	std::list<_LOG> m_lstLog;
	 static auto to_local(std::chrono::sys_seconds srtTime) {
		return   std::chrono::current_zone()->to_local(srtTime);
	}
	bool ChangeRegion(string strRegion);
	bool ChangeSetting(_LOG::eTYPE eType, int n);
	std::tuple<string, int, int> GetSetting();
	
	bool ChangeAlarm(_LOG::eTYPE eType, CAlarm::_ALERT srtAlert);
	bool Update_TimeAlarm(string& strAlarm);
	bool Save();

};

