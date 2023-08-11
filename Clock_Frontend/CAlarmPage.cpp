// CAlarmPage.cpp: 实现文件
//

#include "pch.h"
#include "CAlarmPage.h"
#include "Clock.h"
#include "afxdialogex.h"


// CAlarmPage 对话框

IMPLEMENT_DYNAMIC(CAlarmPage, CMFCPropertyPage)

CAlarmPage::CAlarmPage(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_ALARM)
{

}

CAlarmPage::~CAlarmPage()
{
}

void CAlarmPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlarmPage, CMFCPropertyPage)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CAlarmPage::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CAlarmPage 消息处理程序


void CAlarmPage::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
