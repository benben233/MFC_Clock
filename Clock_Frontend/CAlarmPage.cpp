// CAlarmPage.cpp: 实现文件
//

#include "pch.h"
#include "CAlarmPage.h"
#include "afxdialogex.h"


// CAlarmPage 对话框

IMPLEMENT_DYNAMIC(CAlarmPage, CMFCPropertyPage)

CAlarmPage::CAlarmPage(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_ALARM)
{
	p_Alert.srtTime = p_AlertNew.srtTime = CClock::now();
}

CAlarmPage::~CAlarmPage()
{
}

void CAlarmPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, p_AlarmList);
	DDX_Control(pDX, IDC_CYCLEW, p_CycleWSel);
	DDX_Text(pDX, IDC_LABEL, p_Label);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, p_Date);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, p_Time);
	DDX_Control(pDX, IDC_CHANGE, p_Change);
	DDX_Control(pDX, IDC_ADD, p_Add);
	DDX_Control(pDX, IDC_DELETE, p_Delete);
	DDX_Radio(pDX, IDC_RADIO1, p_Disable);
	DDX_Text(pDX, IDC_EDIT2, p_CycleD);
}

BOOL CAlarmPage::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();
	p_AlarmList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	p_AlarmList.InsertColumn(0, L"ID");
	p_AlarmList.InsertColumn(1, L"提醒文字");
	p_AlarmList.InsertColumn(2, L"时间");
	p_AlarmList.InsertColumn(3, L"提醒周期");
	p_AlarmList.InsertColumn(4, L"是否启用");
	for (size_t i = 0; i < p_vctAlert.size(); i++)
	{
		UpdateList(i);
	}
	for (size_t i = 0; i < 5; i++)
	{
		p_AlarmList.SetColumnWidth(i, LVSCW_AUTOSIZE);
	}
	for (size_t i = 0; i < 7; i++)
	{
		p_CycleWSel.InsertString(i, CString(std::format("{:L%a}", std::chrono::weekday(i)).c_str()));
		p_CycleWSel.SetColumnWidth(40);
	}
	
	
	return true;
}

BOOL CAlarmPage::OnKillActive()
{
	if (p_bChanged)
	{
		if (Unsaved())
		{
			if (p_AlarmList.GetSelectedCount())
			{
				p_AlarmList.SetItemState(p_nSel, NULL, LVIS_SELECTED);
			}
			else
			{
				clear();
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	if (p_AlarmList && !p_AlarmList.GetSelectedCount())
	{
		clear();
	}
	return true;
}


BEGIN_MESSAGE_MAP(CAlarmPage, CMFCPropertyPage)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST1, &CAlarmPage::OnLvnItemchangingList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CAlarmPage::OnLvnItemchangedList1)
	ON_EN_CHANGE(IDC_LABEL, &CAlarmPage::OnEnChangeLabel)
	ON_LBN_SELCHANGE(IDC_CYCLEW, &CAlarmPage::OnLbnSelchangeCyclew)
	ON_BN_CLICKED(IDC_CHANGE, &CAlarmPage::OnBnClickedChange)
	ON_BN_CLICKED(IDC_RADIO1, &CAlarmPage::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, &CAlarmPage::OnBnClickedRadio)
	ON_EN_CHANGE(IDC_EDIT2, &CAlarmPage::OnEnChangeEdit2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CAlarmPage::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, &CAlarmPage::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_ADD, &CAlarmPage::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CAlarmPage::OnBnClickedDelete)
	ON_NOTIFY(LVN_HOTTRACK, IDC_LIST1, &CAlarmPage::OnLvnHotTrackList1)
END_MESSAGE_MAP()


// CAlarmPage 消息处理程序
void CAlarmPage::OnLvnItemchangingList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (p_bChanged && (pNMLV->uOldState != pNMLV->uNewState))
	{
		if (!confirm)
		{
			*pResult = !Unsaved();
			confirm = true;
		}
		else
		{
			*pResult = 1;
		}
	}
}


void CAlarmPage::OnLvnHotTrackList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	confirm = false;
	*pResult = 0;
}


void CAlarmPage::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	 //TODO: 在此添加控件通知处理程序代码
	if (pNMLV->uOldState & LVIS_SELECTED )
	{
		p_Change.EnableWindow(false);
		if (!p_AlarmList.GetSelectedCount())
		{
			p_Delete.EnableWindow(false);
			clear();
		}
	}
	if (pNMLV->uNewState & LVIS_SELECTED)
	{
		Update(pNMLV->iItem);
		SetChange();
		p_Delete.EnableWindow();
	}
}



void CAlarmPage::OnEnChangeLabel()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	p_AlertNew.strLabel = CT2A(p_Label).m_psz;
	SetChange();
}


void CAlarmPage::OnLbnSelchangeCyclew()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	p_AlertNew.CycleW = 0;
	int n = p_CycleWSel.GetSelCount();
	int sel[7];
	p_CycleWSel.GetSelItems(n, sel);
	if (1 == n)
	{
		p_AlertNew.srtCycleD = std::chrono::days(7);
		p_CycleD = L'7';
	}
	else
	{
		p_AlertNew.srtCycleD = std::chrono::days(0);
		p_CycleD = L"";
	}
	UpdateData(false);
	for (size_t i = 0; i < n; i++)
	{
		p_AlertNew.CycleW[sel[i]] = true;
	}
	SetChange();
}



void CAlarmPage::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	int d = _ttoi(p_CycleD);
	p_AlertNew.srtCycleD = std::chrono::days(d);
	if (d > 0)
	{
		p_AlertNew.CycleW = 0;
		p_CycleWSel.SelItemRange(false, 0, p_CycleWSel.GetCount());
		if (7 == d)
		{
			int wd = std::chrono::weekday(floor<std::chrono::days>(CClock::now())).c_encoding();
			p_CycleWSel.SetSel(wd);
			p_AlertNew.CycleW[wd] = true;
		}
	}
	SetChange();
}



void CAlarmPage::OnBnClickedRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	p_AlertNew.bEnable = !p_Disable;
	SetChange();
}

void CAlarmPage::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	UpdateData();
	COleDateTime a;

	std::istringstream iss{ CT2A(p_Date +L' ' + p_Time).m_psz};
	iss >> std::chrono::parse("%Y/%m/%d %X", p_AlertNew.srtTime);
	SetChange();	
}

void CAlarmPage::clear()
{
	p_Alert = p_AlertNew = CAlarm::_ALERT();
	p_Label = p_CycleD = L"";
	p_CycleWSel.SelItemRange(false, 0, p_CycleWSel.GetCount());
	p_Disable = false;
	p_Alert.srtTime = p_AlertNew.srtTime = CClock::now();
	std::ostringstream oss;
	oss << p_Alert.srtTime;
	p_Date = p_Time = CString(oss.str().c_str());
	UpdateData(false);
	SetChange();
}
/******************************************************************************
* 更新显示第index行数据
* [in]目标行的index
******************************************************************************/
void CAlarmPage::Update(size_t index)
{
	p_nSel = index;
	p_Alert = p_AlertNew = p_vctAlert[index];
	p_Label = p_AlarmList.GetItemText(index, 1);
	p_Date = p_AlarmList.GetItemText(index, 2);
	p_Time = p_Date;

	p_CycleWSel.SelItemRange(false, 0, p_CycleWSel.GetCount());
	int d = p_Alert.srtCycleD.count();
	p_CycleD = d ? CString(std::to_wstring(d).c_str()) : CString();
	for (size_t i = 0; i < std::size(p_Alert.CycleW); i++)
	{
		if (p_Alert.CycleW[i])
		{
			p_CycleWSel.SetSel(i);
		}
	}
	p_Disable = !p_Alert.bEnable;
	UpdateData(false);
}

/******************************************************************************
* 根据后台数据更新列表第index行
* [in]目标闹钟的index
******************************************************************************/
void CAlarmPage::UpdateList(size_t index)
{
	auto vct = CAlarm::to_string(p_vctAlert[index]);
	if (index >= p_AlarmList.GetItemCount())
	{
		p_AlarmList.InsertItem(index, CString(vct[0].c_str()));
	}
	else
	{
		p_AlarmList.SetItemText(index, 0, CString(vct[0].c_str()));
	}
	for (size_t n = 1; n < 5; n++)
	{
		p_AlarmList.SetItemText(index, n, CString(vct[n].c_str()));
	}
}

bool CAlarmPage::Check()
{
//#undef DEBUG
#ifndef DEBUG
	if (p_AlertNew.srtTime <= CClock::now() && p_AlertNew.bEnable)
	{
		MessageBox(L"设置闹钟时间不能小于当前时间", L"时间错误", MB_ICONEXCLAMATION);
		return false;
	}
#define DEGUG
#endif // !DEBUG
	return true;

}


void CAlarmPage::OnBnClickedAdd()
{
	if (!Check())
	{
		return;
	}
	CClockApp::m_srtClock.ChangeAlarm(CClock::_LOG::eTYPE::ADD_ALARM, p_AlertNew);
	// TODO: 在此添加控件通知处理程序代码
	p_bChanged = false;
	UpdateList(p_AlarmList.GetItemCount());
	p_AlertNew.nID = p_Alert.nID;
}


void CAlarmPage::OnBnClickedChange()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!Check())
	{
		return;
	}
	CClockApp::m_srtClock.ChangeAlarm(CClock::_LOG::eTYPE::CHANGE_ALARM, p_AlertNew);
	p_bChanged = false;
	UpdateList(p_nSel);
	p_Alert = p_AlertNew;
	SetChange();
}

void CAlarmPage::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (p_bChanged && !Unsaved())
	{
		return;
	}
	CClockApp::m_srtClock.ChangeAlarm(CClock::_LOG::eTYPE::DELETED_ALARM, p_AlertNew);
	p_bChanged = false;
	p_AlarmList.DeleteItem(p_nSel);
	clear();
}

void CAlarmPage::SetChange()
{
	p_bChanged = (p_AlertNew.bEnable != p_Alert.bEnable)
		|| (p_AlertNew.nID != p_Alert.nID)
		|| (p_AlertNew.srtCycleD != p_Alert.srtCycleD)
		|| (p_AlertNew.srtTime != p_Alert.srtTime)
		|| (p_AlertNew.strLabel != p_Alert.strLabel)
		|| (p_AlertNew.CycleW != p_Alert.CycleW);

	p_Change.EnableWindow(p_bChanged ? p_AlarmList.GetSelectedCount() : false);
}

