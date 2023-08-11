#pragma once


// CZonedTime 对话框
#include "CRegion.h"
#include <vector>
#include <string>
class CZonedTime : public CMFCPropertyPage 
{
	DECLARE_DYNAMIC(CZonedTime)

public:
	CZonedTime(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CZonedTime();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZONED_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	bool Update(std::string& str);
	bool ChangeRegion();
	std::vector<CRegion*> m_vctRegions;
};
