#pragma once


// CAlarmDlg 对话框

class CAlarmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlarmDlg)

public:
	CAlarmDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAlarmDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Alarm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDtnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult);
//	CTime date;
	afx_msg void OnBnClickedOk();
	CString date;
	afx_msg void OnBnClickedButton2();
};
