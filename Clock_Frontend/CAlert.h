#pragma once


// CAlert 对话框

class CAlert : public CDialogEx
{
	DECLARE_DYNAMIC(CAlert)

public:
	CAlert(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAlert();
	bool IsModal;
	void Add(size_t index);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	std::list<size_t> m_lstIndex;
	std::string m_strAlert;
	CListCtrl m_List;
	void SetAlarm(bool);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	bool p_bAlarm;
	CButton p_Stop;
	CButton p_Delay;
public:
	afx_msg void OnBnClickedDelay();
};
