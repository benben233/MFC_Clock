#pragma once


// CSettings 对话框

class CSettings : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CSettings)

public:
	CSettings(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettings();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
private:

	CButton p_Region[4];
	inline const static std::string p_chszRegions[] = { "北京", "东京", "伦敦", "华盛顿" };
	std::string p_strRegion, p_strRegionOld;
	CButton p_Apply;
	int p_nDuration, p_nDelay;
	int p_nDurationOld, p_nDelayOld;
public:
	afx_msg void OnEnChangeEdit1();
};
