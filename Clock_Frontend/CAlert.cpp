// CAlert.cpp: 实现文件
//

#include "pch.h"
#include "Clock.h"
#include "CAlert.h"
#include "afxdialogex.h"


// CAlert 对话框

IMPLEMENT_DYNAMIC(CAlert, CDialogEx)

CAlert::CAlert(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALERT, pParent)
{

}

CAlert::~CAlert()
{
}

void CAlert::Add(size_t index)
{
	if (index != m_lstIndex.back())
	{
		m_List.InsertItem(m_List.GetItemCount(), CString(m_strAlert.c_str()));
		m_lstIndex.push_back(index);
	}
	else
	{
		m_List.SetItemText(m_List.GetItemCount() - 1, 0, CString(m_strAlert.c_str()));
	}
}

void CAlert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDOK, p_Stop);
	DDX_Control(pDX, IDC_DELAY, p_Delay);
}

BOOL CAlert::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	IsModal = true;
	m_List.InsertItem(m_List.GetItemCount(), CString(m_strAlert.c_str()));
	p_Stop.EnableWindow(p_bAlarm);
	p_Delay.EnableWindow(p_bAlarm);
	return true;
}


BEGIN_MESSAGE_MAP(CAlert, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAlert::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAlert::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DELAY, &CAlert::OnBnClickedDelay)
END_MESSAGE_MAP()


// CAlert 消息处理程序


void CAlert::SetAlarm(bool b)
{
	p_bAlarm = b;
	if (IsModal)
	{
		p_Stop.EnableWindow(p_bAlarm);
		p_Delay.EnableWindow(p_bAlarm);
	}
}

void CAlert::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CClockApp::m_srtClock.Stop();
	IsModal = false;
	CDialogEx::OnOK();
}


void CAlert::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (p_bAlarm)
	{
		MessageBox(L"默认停止闹钟");
		CClockApp::m_srtClock.Stop();
	}
	IsModal = false;
	CDialogEx::OnCancel();
}

void CAlert::OnBnClickedDelay()
{
	// TODO: 在此添加控件通知处理程序代码
	CClockApp::m_srtClock.Delay();
	IsModal = false;
	CDialogEx::OnCancel();
}
