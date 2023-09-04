// CZonedTime.cpp: 实现文件
//

#include "pch.h"
#include "Clock.h"
#include "CZonedTime.h"
#include "afxdialogex.h"


// CZonedTime 对话框

IMPLEMENT_DYNAMIC(CZonedTime, CMFCPropertyPage)

CZonedTime::CZonedTime(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_ZONED_TIME)
{
}

CZonedTime::~CZonedTime()
{
	for (auto& i : m_vctRegions)
	{
		delete i;
	}
}

void CZonedTime::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}

BOOL CZonedTime::OnInitDialog()
{
	if (!ChangeRegion())
	{
		throw std::exception("无法创建时区");
	}
	return TRUE;
}


BEGIN_MESSAGE_MAP(CZonedTime, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CZonedTime::OnBnClickedButton1)
END_MESSAGE_MAP()


// CZonedTime 消息处理程序

void CZonedTime::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CAlarm::_ALERT a;
	CClockApp::m_srtClock.ChangeAlarm(CClock::_LOG::eTYPE::ADD_ALARM, a);
}

bool CZonedTime::Update()
{
	bool b = false;
	for (auto& i : m_vctRegions)
	{
		b |= !i->Update();
	}
	return !b;
}

bool CZonedTime::ChangeRegion()
{
	for (auto& i : m_vctRegions)
	{
		delete i;
	}
	m_vctRegions.clear();

	auto&& vct = CClockApp::m_srtClock.GetTime();
	CRect rect;
	for (size_t i = 0; i < vct.size(); i++)
	{
		CRegion* p = new CRegion(vct[i], this);
		p->CreatAfter(rect, this);
		if (0 == i)
		{
			int s = vct.size() - 1;
			rect.InflateRect(SIZE(120 - s * 40, 30 - s * 10));
			rect.MoveToX(rect.left - s * rect.Width() / 2);
			p->MoveWindow(rect);
		}
		p->ChangeTimeFontSize();
		m_vctRegions.emplace_back(p);
	}
	return true;
}
