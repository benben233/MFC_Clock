#pragma once

#include "Clock.h"
// CLog 对话框

class CLog : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CLog)

public:
	CLog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
private:
	CListBox p_TypeSel;
	constexpr static size_t p_TypeNum = std::size(CClock::m_chszLog);
public:
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CListCtrl p_LogList;
protected:

private:
	CString p_strFrom;
	CString p_strTo;
	std::chrono::local_days From, To;
	std::bitset<std::size(CClock::m_chszLog)> Type;
	void Search();
public:
	std::list<CClock::_LOG> m_lstLog;
	void clear();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton3();
};
