
// ClockDlg.h: 头文件
//

#pragma once
#define WM_ONTRAY WM_USER + 1
#include "CZonedTime.h"
#include "CAlarmDlg.h"
#include "CSettings.h"
// CClockDlg 对话框
class CClockDlg : public CDialogEx
{
// 构造
public:
	CClockDlg(CWnd* pParent = nullptr);	// 标准构造函数
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLOCK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
// 实现
protected:
	
	CMenu s_Tray;
	CPropertySheet s_Tab;
	CZonedTime s_srtZonedTime;
	CSettings s_srtSettings;
	CAlarmDlg al;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	HICON m_hIcon;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnOntray(WPARAM wParam, LPARAM lParam);
public:
	bool ChangeRegion() {
		return s_srtZonedTime.ChangeRegion();
	}
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
