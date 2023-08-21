#pragma once


// CRegion 对话框
class CRegion : public CDialogEx
{
	DECLARE_DYNAMIC(CRegion)

public:
	CRegion(CClock::_ZonedTime& p_strZonedTime, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegion();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	inline static CFont* TimeFont = nullptr;
	CClock::_ZonedTime& p_strZonedTime;
	CString p_strRegion;
	CString p_strDate;
	CString p_strTime;
	
public:
	bool CreatAfter(CRect& pRect, CWnd* pParent);
	bool Update();
	bool ChangeTimeFontSize();
	afx_msg void OnDestroy();
};
