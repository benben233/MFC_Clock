// CSettings.cpp: 实现文件
//

#include "pch.h"
#include "Clock.h"
#include "ClockDlg.h"
#include "CSettings.h"
#include "afxdialogex.h"

// CSettings 对话框

IMPLEMENT_DYNAMIC(CSettings, CMFCPropertyPage)

CSettings::CSettings(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_SETTINGS)
{
	std::tie(p_strRegionOld, p_nDurationOld, p_nDelayOld) =
		std::tie(p_strRegion, p_nDuration, p_nDelay) = CClockApp::m_srtClock.GetSetting();
}

CSettings::~CSettings()
{
}

void CSettings::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK1, p_Region[0]);
	DDX_Control(pDX, IDC_CHECK2, p_Region[1]);
	DDX_Control(pDX, IDC_CHECK3, p_Region[2]);
	DDX_Control(pDX, IDC_CHECK4, p_Region[3]);
	DDX_Control(pDX, IDC_BUTTON1, p_Apply);
	DDX_Text(pDX, IDC_EDIT1, p_nDuration);
	DDX_Text(pDX, IDC_EDIT2, p_nDelay);
}

BOOL CSettings::OnSetActive()
{
	p_Apply.EnableWindow(FALSE);
	p_strRegion = p_strRegionOld;
	for (size_t i = 0; i < std::size(p_Region); i++)
	{
		if (p_strRegion.find(p_chszRegions[i]) != std::string::npos)
		{
			p_Region[i].SetCheck(true);
		}
		else
		{
			p_Region[i].SetCheck(false);
		}
	}
	return true;
}

BOOL CSettings::OnKillActive()
{
	if (p_Apply.IsWindowEnabled())
	{
		CDialogEx dlg(IDD_UNSAVED, this);
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: 在此放置处理何时用
			//  “确定”来关闭对话框的代码
			return true;
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: 在此放置处理何时用
			//  “取消”来关闭对话框的代码
			return false;
		}
		else if (nResponse == -1)
		{
			TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
			TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
		}
	}
	return true;
}



BEGIN_MESSAGE_MAP(CSettings, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_CHECK1, &CSettings::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CSettings::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK3, &CSettings::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK4, &CSettings::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSettings::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CSettings::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CSettings::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CSettings 消息处理程序


void CSettings::OnBnClickedCheck1()
{
	p_strRegion.clear();
	for (size_t i = 0; i < std::size(p_Region); i++)
	{
		if (p_Region[i].GetCheck())
		{
			p_strRegion += p_chszRegions[i] + ' ';
		}
	}
	if (p_strRegion == p_strRegionOld)
	{
		p_Apply.EnableWindow(false);
	}
	else
	{
		p_Apply.EnableWindow();
	}
}


void CSettings::OnBnClickedButton1()
{
	if (p_strRegion != p_strRegionOld
		&& CClockApp::m_srtClock.ChangeRegion(p_strRegion)
		&& ((CClockDlg*)GetParent()->GetParent())->ChangeRegion())
	{
		p_strRegionOld = p_strRegion;
	}
	if (p_nDelay != p_nDelayOld
		&& CClockApp::m_srtClock.ChangeSetting(CClock::_LOG::eTYPE::DELAY, p_nDelay))
	{
		p_nDelayOld = p_nDelay;
	}
	if (p_nDuration != p_nDurationOld
		&& CClockApp::m_srtClock.ChangeSetting(CClock::_LOG::eTYPE::DURATION, p_nDuration))
	{
		p_nDurationOld = p_nDuration;
	}
	if (p_strRegionOld == p_strRegion && p_nDelayOld == p_nDelay && p_nDurationOld == p_nDuration)
	{
		p_Apply.EnableWindow(false);
	}
}


void CSettings::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (GetDlgItem(IDC_EDIT1)->SendMessage(WM_GETTEXTLENGTH) && GetDlgItem(IDC_EDIT2)->SendMessage(WM_GETTEXTLENGTH))
	{
		UpdateData();
		if (p_nDuration == p_nDurationOld && p_nDelay == p_nDelayOld)
		{
			p_Apply.EnableWindow(false);
		}
		else
		{
			p_Apply.EnableWindow();
		}
	}
}

