#include "clock.h"
#include <windows.h>

using namespace std::chrono;
using namespace std;

std::string GetLastErrorAsString()
{
	//Get the error message ID, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) {
		return std::string(); //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}

/******************************************************************************
* 创建时钟类，读取设置文件，闹钟，日志
******************************************************************************/
CClock::CClock() :p_Alarm{ GetPrivateProfileIntA("Alarm", "duration", 1, p_chszSettingFile),
	GetPrivateProfileIntA("Alarm", "delay", 1, p_chszSettingFile) }
{
	
	char chszRegion[64];
	GetPrivateProfileStringA("Clock", "regions", "北京", chszRegion, 64, p_chszSettingFile);
	string er = GetLastErrorAsString();

	istringstream iss{ chszRegion };

	while (iss >> chszRegion)
	{
		p_vctZonedTime.push_back({ chszRegion, "", "" });
	}
	UpdateTime();
	ifstream f{ p_chszLogFile };
	int type;
	_LOG log;
	while (f.good())
	{
		f >> type >> parse(" %F %T", log.srtTime);
		f.get();
		getline(f, log.strDetail);
		log.eType = _LOG::eTYPE{ type };
		if (f) 
		{
			p_lstLog.push_back(log);
		}		
	}
}

CClock::~CClock()
{
	if (!Save())
	{
		throw exception("无法保存");
	}
}


/******************************************************************************
* 保存设置，闹钟，日志
******************************************************************************/
bool CClock::Save()
{
	string s;
	for (auto& i : p_vctZonedTime)
	{
		s += get<0>(i) + ' ';
	}
	
	WritePrivateProfileStringA("Clock", "regions", s.c_str(), p_chszSettingFile);
	s = std::to_string(p_Alarm.m_nDuration.count());
	WritePrivateProfileStringA("Alarm", "duration", s.c_str(), p_chszSettingFile);
	s = std::to_string(p_Alarm.m_nDelay.count());
	WritePrivateProfileStringA("Alarm", "delay", s.c_str(), p_chszSettingFile);

	ofstream f{ p_chszLogFile };
	if (!(f.is_open() && p_Alarm.Save()))
	{
		return false;
	}
	for (_LOG l : p_lstLog)
	{
		f << (int)l.eType << ' ' << l.srtTime << ' ' << l.strDetail << endl;
	}
	f.close();
	return true;
}


/******************************************************************************
* 更改闹钟延时，持续设置
******************************************************************************/
bool CClock::ChangeSetting(_LOG::eTYPE eType, int n)
{
	sys_seconds&& now = round<seconds>(system_clock::now());
	switch (eType)
	{
	case _LOG::eTYPE::DURATION:
		p_Alarm.m_nDuration = chrono::minutes(n);
		p_lstLog.push_back(_LOG(eType, now, "闹钟持续时间改为" + to_string(n) + "分钟"));
		break;
	case _LOG::eTYPE::DELAY:
		p_Alarm.m_nDelay = chrono::minutes(n);
		p_lstLog.push_back(_LOG(eType, now, "闹钟延迟时间改为" + to_string(n) + "分钟"));
		break;

	default:
		return false;
		break;
	}
	return true;
}

/******************************************************************************
* 返回时区，持续时间，延迟时间的设置
******************************************************************************/
tuple<string, int, int> CClock::GetSetting()
{
	string s;
	for (auto& i : p_vctZonedTime)
	{
		s += get<0>(i) + ' ';
	}
	return make_tuple(s, p_Alarm.m_nDuration.count(), p_Alarm.m_nDelay.count());
}

/******************************************************************************
* 更改闹钟
******************************************************************************/
bool CClock::ChangeAlarm(_LOG::eTYPE eType, CAlarm::_ALERT& srtAlert)
{
	sys_seconds&& now = round<seconds>(system_clock::now());
	bool b;
	switch (eType)
	{
	case CClock::_LOG::eTYPE::ADD_ALARM:
		b = p_Alarm.Add(srtAlert);
		break;
	case CClock::_LOG::eTYPE::DELETED_ALARM:
		b = p_Alarm.Delete(srtAlert.nID);
		break;
	case CClock::_LOG::eTYPE::CHANGE_ALARM:
		b = p_Alarm.Change(srtAlert);
		break;
	default:
		return false;
		break;
	}
	if (b)
	{
		p_lstLog.push_back(_LOG(eType, now, "ID为" + to_string(srtAlert.nID)));
	}
	return b;
}


std::list<CClock::_LOG> CClock::GetLog(std::bitset<6> type, std::chrono::local_days from, std::chrono::local_days to)
{
	to++;
	sys_seconds s_from = current_zone()->to_sys(from), s_to = current_zone()->to_sys(to);

	std::list<CClock::_LOG> vctLog;
	if (type.none())
	{
		type.flip();
	}
	for (auto& i : p_lstLog)
	{
		if (type[int(i.eType)] && s_from <= i.srtTime && s_to >= i.srtTime)
		{
			vctLog.push_back(i);
		}
	}
	return vctLog;
}

/******************************************************************************
* 更改时区设置
******************************************************************************/
bool CClock::ChangeRegion(string strRegion)
{
	p_vctZonedTime.clear();
	istringstream iss(strRegion);
	string region;
	while (iss >> region)
	{
		if (!p_mapRegion.contains(region))
		{
			return false;
		}
		p_vctZonedTime.push_back({ region, "", "" });
	}
	p_lstLog.push_back(_LOG(_LOG::eTYPE::REGION, round<seconds>(system_clock::now()), "显示时区改为" + strRegion));
	return true;
}

/******************************************************************************
* 更新所有m_vctZonedTime内的时间并检测闹钟
* [out]返回是触发闹钟的index,
* [out]将目前闹钟状态写入strAlarm
* [out]将更改闹钟index写入
******************************************************************************/
bool CClock::Update_TimeAlarm(string& strAlarm, size_t& index)
{
	local_seconds&& local_now = current_zone()->to_local(UpdateTime());
	bool b = p_Alarm.IsAlarm(local_now, index);
	if (index != -1)
	{
		auto& a = p_Alarm.m_vctAlert[index];
		strAlarm = "闹钟" + to_string(a.nID) + " " + a.strLabel
			+ (b ? " 已触发" : " 已错过");
	}
	return b;
}

sys_seconds CClock::UpdateTime()
{
	sys_seconds&& now = round<seconds>(system_clock::now());

	for (auto& [region, date, time] : p_vctZonedTime)
	{
		local_seconds zt = locate_zone(p_mapRegion.find(region)->second)->to_local(now);
		date = format("{:L%x %A}", zt);
		time = format("{:L%X}", zt);
	}
	return now;
}

