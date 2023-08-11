#include "alarm.h"

CAlarm::CAlarm(int nDuration, int nDelay) :m_nDuration{ std::chrono::minutes(nDuration) },
m_nDelay{ m_nDelay = std::chrono::minutes(nDelay) }
{
	std::ifstream f{ p_chszAlarmFile };
	
	f >> nNextID;
	_ALERT alert;

	while (f.good())
	{
		int i;
		std::getline(f, alert.strLabel);
		f >> alert.nID >> std::chrono::parse("%F %T", alert.srtTime)
			>> alert.bEnable >> i;
		alert.srtCycleD = std::chrono::days(i);

		while (f.get() == ' ' && f)
		{
			std::chrono::weekday w;
			f >> std::chrono::parse("%a", w);
			alert.vrtCycleW.push_back(w);
		}
		if (f)
		{
			p_vctAlert.push_back(alert);
		}
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
	for (auto& i : p_vctAlert)
	{
		f << i.strLabel << std::endl << i.nID << ' '
			<< i.srtTime << ' ' << i.bEnable << ' ' << i.srtCycleD.count();
		for (auto& w : i.vrtCycleW)
		{
			f << ' ' << w;
		}
		f << std::endl;
	}

	f.close();
	return true;
}


/******************************************************************************
* 根据时间判断是否触发闹钟
* [out]有闹钟触发返回其指针，已过期闹钟会触发stop，无返回null
******************************************************************************/
CAlarm::_ALERT* CAlarm::IsAlarm(std::chrono::sys_seconds& srtTime)
{
	if (!p_mapAlarm.empty())
	{
		auto b = p_mapAlarm.begin();
		if (srtTime > b->first)
		{
			//如果时间超过下一个闹钟或超过持续时间停止当前闹钟
			if ((std::next(b) != p_mapAlarm.end()) && (srtTime > std::next(b)->first)
				|| (srtTime > (b->first + m_nDuration)))
			{
				Stop();
				return  &p_vctAlert[b->second];
			}
			else
			{
				return &p_vctAlert[b->second];
			}
		}
	}
	return nullptr;
}


/******************************************************************************
* 停止第一个闹钟并更新，有周期的更新响铃时间并重新加入闹钟，无周期Enable改为false
* [out] 是否还有闹钟
******************************************************************************/
bool CAlarm::Stop()
{
	auto b = p_mapAlarm.extract(p_mapAlarm.begin());
	_ALERT& alart = p_vctAlert[b.mapped()];
	if (alart.srtCycleD.count() > 0)
	{
		b.key() = alart.srtTime += alart.srtCycleD;
		p_mapAlarm.insert(std::move(b));
	}
	else if (alart.vrtCycleW.size() > 1)
	{
		b.key() = alart.srtTime += alart.vrtCycleW[1] - alart.vrtCycleW[0];
		std::rotate(alart.vrtCycleW.begin(), alart.vrtCycleW.begin() + 1, alart.vrtCycleW.end());
		p_mapAlarm.insert(std::move(b));
	}
	else
	{
		alart.bEnable = false;
	}
	return !p_mapAlarm.empty();
}

bool CAlarm::Delay(std::chrono::sys_seconds&& srtTime)
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

	p_mapAlarm.insert({ srtAlart.srtTime, p_vctAlert.size() });
	p_vctAlert.push_back(srtAlart);
	return true;
}

bool CAlarm::Change(_ALERT& srtAlart)
{
	for (size_t i = 0; i < p_vctAlert.size(); i++)
	{
		if (p_vctAlert[i].nID == srtAlart.nID)
		{
			if (srtAlart.bEnable && (srtAlart.srtTime != p_vctAlert[i].srtTime))
			{
				auto a = p_mapAlarm.extract(std::find_if(p_mapAlarm.begin(), p_mapAlarm.end(),
					[&i](auto& m) { return m.second == i; }));
				a.key() = srtAlart.srtTime;
				p_mapAlarm.insert(std::move(a));
			}
			p_vctAlert[i] = srtAlart;
			return true;
		}
	}
	return false;
}

bool CAlarm::Delete(short n)
{
	auto iter = std::find_if(p_vctAlert.begin(), p_vctAlert.end(),
		[&n](auto& i) {return i.nID == n; });
	if (iter == p_vctAlert.end())
	{
		return false;
	}
	p_srtHasID[iter->nID] = false;
	p_vctAlert.erase(iter);
	size_t index = iter - p_vctAlert.begin();
	for (auto i = p_mapAlarm.begin(); i != p_mapAlarm.end(); i++)
	{
		if (i->second == index)
		{
			p_mapAlarm.erase(i);
		}
		else if (i->second > index)
		{
			i->second--;
		}
	}
	return true;
}

