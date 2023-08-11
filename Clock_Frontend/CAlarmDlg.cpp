// CAlarmDlg.cpp: 实现文件
//

#include "pch.h"
#include "Clock.h"
#include "CAlarmDlg.h"
#include "afxdialogex.h"


// CAlarmDlg 对话框

IMPLEMENT_DYNAMIC(CAlarmDlg, CDialogEx)

CAlarmDlg::CAlarmDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Alarm, pParent)
	, date(_T(""))
{

}

CAlarmDlg::~CAlarmDlg()
{
}

void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, date);

}


BEGIN_MESSAGE_MAP(CAlarmDlg, CDialogEx)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, &CAlarmDlg::OnDtnDatetimechangeDatetimepicker2)
	ON_BN_CLICKED(IDOK, &CAlarmDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CAlarmDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAlarmDlg 消息处理程序


void CAlarmDlg::OnDtnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CAlarmDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	UpdateData();
	MessageBox(L"16");
}


void CAlarmDlg::OnBnClickedButton2()
{

	MessageBox(L"16");
	// TODO: 在此添加控件通知处理程序代码
}
