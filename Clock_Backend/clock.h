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
	const char* p_chszSettingFile{ "./Settings.ini" };
	const char* p_chszLogFile{ "Log.txt" };
	std::map<string, string> p_mapRegion{ { "����", "Asia/Shanghai"}, {"����" , "Asia/Tokyo"},
		{"�׶�" ,"Europe/London"}, {"��ʢ��" , "America/New_York"} };


public:
	CClock();
	~CClock();
	typedef std::tuple<string, string, string> _ZonedTime;
	//���ڷ��ص��������ڣ�ʱ��
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
	constexpr static const char* m_chszLog[] = { "����ʱ��","�����ӳ�ʱ��","���ĳ���ʱ��","��������","ɾ������","��������" };
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

