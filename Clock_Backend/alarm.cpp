#include "alarm.h"
#include "clock.h"
CAlarm::CAlarm(int nDuration, int nDelay) :m_nDuration{ std::chrono::minutes(nDuration) },
m_nDelay{ std::chrono::minutes(nDelay) }
{
	setlocale(LC_ALL, "");
	std::locale::global(std::locale(setlocale(LC_ALL, NULL)));
	std::ifstream f{ p_chszAlarmFile };
	
	f >> nNextID;
	f.get();
	_ALERT alert;
	
	//f.exceptions(f.failbit);
	int index = 0;
	while (f.good())
	{
		std::getline(f, alert.strLabel);
		int d;
		f >> alert.nID >> std::chrono::parse(" %F %T", alert.srtTime)
			>> alert.bEnable >> d >> alert.CycleW;
		alert.srtCycleD = std::chrono::days(d);
		if (f)
		{
			m_vctAlert.push_back(alert);
			if (alert.bEnable)
			{
				p_mapAlarm.insert({ alert.srtTime, index });
			}
			index++;
		}
		f.get();
		f.peek();
	}
}

bool CAlarm::Save()
{
	std::ofstream f{ p_chszAlarmFile };
	if (!f.is_open())
	{
		return false;
	}
	f << nNextID << std::endl;
	for (auto& i : m_vctAlert)
	{
		f << i.strLabel << std::endl << i.nID << ' '
			<< i.srtTime << ' ' << i.bEnable << ' ' << i.srtCycleD.count()
			<< ' ' << i.CycleW << std::endl;
	}
	f.close();
	return true;
}


std::array<std::string, 5> CAlarm::to_string(const _ALERT& alert)
{
	std::array<std::string, 5>  strAlert;
	strAlert[0] = std::to_string(alert.nID);
	strAlert[1] = alert.strLabel;
	std::ostringstream oss;
	oss << alert.srtTime;
	strAlert[2] = oss.str();
	oss.str("");
	if (alert.CycleW.any())
	{
		for (size_t i = 0; i < std::size(alert.CycleW); i++)
		{
			if (alert.CycleW[i])
			{
				oss << std::chrono::weekday(i);
			}
		}
	}
	else if (alert.srtCycleD.count() > 0)
	{
		oss << "每" << alert.srtCycleD.count() << "天";
	}
	strAlert[3] = oss.str();
	strAlert[4] = alert.bEnable ? "启用" : "停用";
	return strAlert;
}


/******************************************************************************
* 根据时间判断是否触发闹钟
* [out]将更改闹钟index写入
******************************************************************************/
bool CAlarm::IsAlarm(std::chrono::local_seconds& local_now, size_t& index)
{
	if (!p_mapAlarm.empty())
	{
		auto b = p_mapAlarm.begin();
		if (local_now > b->first)
		{
			index = b->second;
			//如果时间超过下一个闹钟或超过持续时间停止当前闹钟
			if ((std::next(b) != p_mapAlarm.end()) && (local_now > std::next(b)->first)
				|| (local_now > b->first + m_nDuration))
			{
				
				Stop();
				return  false;
			}
			else
			{
				return true;
			}
		}
	}
	index = -1;
	return false;
}


/******************************************************************************
* 停止第一个闹钟并更新，有周期的更新响铃时间并重新加入闹钟，无周期Enable改为false
* [out] 是否还有闹钟
******************************************************************************/
bool CAlarm::Stop()
{
	auto b = p_mapAlarm.extract(p_mapAlarm.begin());
	_ALERT& alert = m_vctAlert[b.mapped()];

	if (alert.CycleW.count() > 0)
	{
		std::chrono::local_days ld = floor<std::chrono::days>(CClock::now());
		do
		{
			ld++;
		} while (!alert.CycleW[std::chrono::weekday(ld).c_encoding()]);
		b.key() = alert.srtTime += ld - floor<std::chrono::days>(alert.srtTime);
		p_mapAlarm.insert(std::move(b));
	}
	else if (alert.srtCycleD.count() > 0)
	{
		auto interval = (CClock::now() - alert.srtTime) / alert.srtCycleD;
		b.key() = alert.srtTime += (interval + 1) * alert.srtCycleD;
		p_mapAlarm.insert(std::move(b));
	}
	else
	{
		alert.bEnable = false;
	}
	return !p_mapAlarm.empty();
}

bool CAlarm::Delay(std::chrono::local_seconds&& srtTime)
{
	if (p_mapAlarm.empty())
	{
		return false;
	}
	auto b = p_mapAlarm.extract(p_mapAlarm.begin());
	b.key() = srtTime + m_nDelay;
	p_mapAlarm.insert(std::move(b));
	return true;
}

bool CAlarm::Add(_ALERT& srtAlart)
{
	if (nNextID >= p_srtHasID.size())
	{
		if (p_srtHasID.all())
		{
			return false;
		}
		for (nNextID = 0; nNextID < p_srtHasID.size(); nNextID++)
		{
			if (false == p_srtHasID[nNextID])
			{
				break;
			}
		}
	}
	srtAlart.nID = (short)nNextID;
	p_srtHasID[nNextID++] = true;
	for (; nNextID < p_srtHasID.size(); nNextID++)
	{
		if (false == p_srtHasID[nNextID])
		{
			break;
		}
	}
	if (srtAlart.bEnable)
	{
		p_mapAlarm.insert({ srtAlart.srtTime, m_vctAlert.size() });
	}
	m_vctAlert.push_back(srtAlart);
	return true;
}

bool CAlarm::Change(_ALERT& srtAlart)
{
	for (size_t i = 0; i < m_vctAlert.size(); i++)
	{
		if (m_vctAlert[i].nID == srtAlart.nID)
		{
			if (srtAlart.bEnable)
			{
				auto&& iter = std::find_if(p_mapAlarm.begin(), p_mapAlarm.end(),
					[&i](auto& m) { return m.second == i; });
				if (iter == p_mapAlarm.end())
				{
					p_mapAlarm.insert({ srtAlart.srtTime , i });
				}
				else
				{
					auto a = p_mapAlarm.extract(iter);
					a.key() = srtAlart.srtTime;
					p_mapAlarm.insert(std::move(a));
				}
			}
			m_vctAlert[i] = srtAlart;
			return true;
		}
	}
	return false;
}

bool CAlarm::Delete(short n)
{
	auto iter = std::find_if(m_vctAlert.begin(), m_vctAlert.end(),
		[&n](auto& i) {return i.nID == n; });
	if (iter == m_vctAlert.end())
	{
		return false;
	}
	p_srtHasID[iter->nID] = false;
	iter = m_vctAlert.erase(iter);
	size_t index = iter - m_vctAlert.begin();
	for (auto i = p_mapAlarm.begin(); i != p_mapAlarm.end(); i++)
	{
		if (i->second == index)
		{
			i = p_mapAlarm.erase(i);
		}
		else if (i->second > index)
		{
			i->second--;
		}
	}
	return true;
}

