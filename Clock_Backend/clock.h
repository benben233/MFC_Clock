/******************************************************************************
* ����: ʱ��
��1����ȡ�趨����ʱ�䣬��
��2��������ӣ�
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
	const std::map<string, string> p_mapRegion{ { "����", "Asia/Shanghai"}, {"����" , "Asia/Tokyo"},
		{"�׶�" ,"Europe/London"}, {"��ʢ��" , "America/New_York"} };
	
public:
	CClock();
	~CClock();
	typedef std::tuple<string, string, string> _ZonedTime;
	//���ش���ʱ������ã�ʹ��Update_TimeAlarm����´����ʱ��
	const auto& GetTime() {
		return p_vctZonedTime;
	}
	bool Update_TimeAlarm(string& strAlarm, size_t& index);

	struct _LOG
	{
		//"����ʱ��","�����ӳ�ʱ��","���ĳ���ʱ��","��������","ɾ������","��������"
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
	//���ڷ��ص��������ڣ�ʱ��
	std::vector<_ZonedTime> p_vctZonedTime;
	std::list<_LOG> p_lstLog;
};

