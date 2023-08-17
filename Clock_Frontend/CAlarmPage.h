#pragma once

#include "Clock.h"
// CAlarmPage 对话框
class CAlarmPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CAlarmPage)
public:
	CAlarmPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAlarmPage();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALARM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnKillActive();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CListCtrl p_AlarmList;
	CListBox p_CycleWSel;
public:
	afx_msg void OnEnChangeLabel();
private:

public:
	afx_msg void OnLbnSelchangeCyclew();

private:
	CButton p_Add;
	CButton p_Change;
	CButton p_Delete;

public:
	afx_msg void OnBnClickedRadio();

	afx_msg void OnEnChangeEdit2();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
private:
	bool Unsaved() {
		p_bChanged = MessageBoxW(L"有尚未保存的内容，是否放弃更改？", L"未保存", MB_YESNO | MB_ICONQUESTION)
			== IDNO;
		return !p_bChanged;
	}

	CString p_Label{ L"" };
	CString p_Date{ COleDateTime::GetCurrentTime().Format(L"%x") };
	CString p_Time{ COleDateTime::GetCurrentTime().Format(L"%X") };
	CString p_CycleD{ L"" };
	CArray<int> p_CycleW;
	BOOL p_Disable{ false };

	bool p_bChanged{ false }, confirm{ false };
	size_t p_nSel = -1;
	void SetChange();
	const std::vector<CAlarm::_ALERT>& p_vctAlert{ CClockApp::m_srtClock.GetAlert() };
	CAlarm::_ALERT p_Alert, p_AlertNew;
public:
	bool Check();
	void clear();
	void Update(size_t index);
	void UpdateList(size_t index);
	void UpdateAlarm(size_t index) {
		if(p_AlarmList)
		{
			UpdateList(index);
			if (index == p_nSel)
			{
				Update(index);
			}
		}
	}
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedChange();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnLvnItemchangingList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnHotTrackList1(NMHDR* pNMHDR, LRESULT* pResult);
};
