// CLog.cpp: 实现文件
//

#include "pch.h"
#include "CLog.h"

#include "afxdialogex.h"


// CLog 对话框

IMPLEMENT_DYNAMIC(CLog, CMFCPropertyPage)

CLog::CLog(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_LOG)
{

}

CLog::~CLog()
{
}

void CLog::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, p_TypeSel);
	DDX_Control(pDX, IDC_LIST2, p_LogList);
}

BOOL CLog::OnInitDialog()
{
	for (auto& i : CClock::m_chszLog)
	{
		p_TypeSel.AddString(CString(i));
	}
	p_LogList.InsertColumn(0, L"操作类型");
	p_LogList.InsertColumn(1, L"操作时间");
	p_LogList.InsertColumn(2, L"详情");
	auto log = CClockApp::m_srtClock.m_lstLog.begin();
	for (size_t i = 0; i < CClockApp::m_srtClock.m_lstLog.size(); i++)
	{
		p_LogList.InsertItem(i, CString(CClock::m_chszLog[int(log->eType)]));
		std::ostringstream oss;
		oss << CClock::to_local(log->srtTime);
		p_LogList.SetItemText(i, 1, CString(oss.str().c_str()));
		p_LogList.SetItemText(i, 2, CString(log->strDetail.c_str()));
	}
	return true;
}


BEGIN_MESSAGE_MAP(CLog, CMFCPropertyPage)
	ON_LBN_SELCHANGE(IDC_LIST1, &CLog::OnLbnSelchangeList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CLog::OnLvnItemchangedList2)
//	ON_MESSAGE(a, &CLog::OnA)
END_MESSAGE_MAP()


// CLog 消息处理程序


void CLog::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CLog::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


//afx_msg LRESULT CLog::OnA(WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}
