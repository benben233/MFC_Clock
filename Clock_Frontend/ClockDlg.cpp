
// ClockDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Clock.h"
#include "ClockDlg.h"
#include "CAlarmDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClockDlg 对话框



CClockDlg::CClockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLOCK_DIALOG, pParent), al(this)

{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()	
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClockDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_ONTRAY, &CClockDlg::OnOntray)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CClockDlg 消息处理程序

BOOL CClockDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(0, 1000, nullptr);
	SetTimer(1, 60000, nullptr);

	s_Tray.LoadMenuW(IDR_MENU1);
	s_Tab.AddPage(&s_srtZonedTime);
	s_Tab.AddPage(&s_srtSettings);

	EnableDynamicLayout();
	s_Tab.Create(this, WS_CHILD | WS_VISIBLE   , WS_EX_CONTROLPARENT);
	

	//al.Create(IDD_Alarm);
	//al.ShowWindow(SW_SHOW);
	//a.Create(IDD_ABOUTBOX, &m_tab);
	//a.ShowWindow(SW_SHOW);

	/*b.Create(IDD_ZONED_TIME, &m_tab);
	b.ShowWindow(SW_SHOW);*/
	
	//s_Tab.ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	
	//al.DoModal();
	//s_Tab.ModifyStyle(0, WS_TABSTOP);
	CRect rcSheet,x,t;
	GetWindowRect(rcSheet);
	//a.GetWindowRect(x);

	//s_Tab.GetWindowRect(t);
	
	//ScreenToClient(&t);
	//s_Tab.SetWindowPos(NULL, rcSheet.left , rcSheet.top , 0, 0,
	//	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	/*a.SetWindowPos(NULL, x.left, x.top, rcSheet.Width()-120, rcSheet.Height()-120,
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);*/
		//在初始化里写更改对话框图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, FALSE);
	//在OnInitDialog方法中调用
	NOTIFYICONDATA  data;
	data.cbSize = sizeof(NOTIFYICONDATA);//结构体的大小
	data.hWnd = this->m_hWnd;//接收托盘消息的窗口句柄 this是当前dialog
	data.uID = IDR_MAINFRAME;//定义的托盘图标ID
	data.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;//设置属性，下面的三个属性是否有效
	lstrcpyn(data.szTip, _T("单击右键显示菜单"), sizeof(_T("单击右键显示菜单")));//图标上的提示字符串
	data.uCallbackMessage = WM_ONTRAY;//自定义的消息，

	data.hIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));//显示在系统托盘上的图标
	Shell_NotifyIcon(NIM_ADD, &data);// 向任务栏的状态栏发送添加托盘图标的消息

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (SC_CLOSE == nID)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
	
}



void CClockDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}




void CClockDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	string s;
	s_srtZonedTime.Update(s);
	CDialogEx::OnTimer(nIDEvent);
	if (1 == nIDEvent)
	{
		CClockApp::m_srtClock.Save();
	}
}


afx_msg LRESULT CClockDlg::OnOntray(WPARAM wParam, LPARAM lParam)
{
	
	if (WM_LBUTTONUP == lParam)
	{
		ShowWindow(SW_SHOW);
	}
	else if (WM_RBUTTONUP == lParam)
	{
		CMenu* pPopup = s_Tray.GetSubMenu(0);
		POINT point;
		GetCursorPos(&point);	
		auto w = AfxGetApp()->m_pMainWnd;
		auto x= pPopup->TrackPopupMenu(TPM_RETURNCMD, point.x, point.y, AfxGetApp()->m_pMainWnd, TPM_LEFTALIGN);
		//pPopup->DestroyMenu();
		x+=1;
	}
	if(WM_MOUSEMOVE == lParam)
	{
		return 0;
	/*	CMenu* pPopup = s_Tray.GetSubMenu(0);
		POINT point;
		GetCursorPos(&point);
		pPopup->TrackPopupMenu(TPM_RETURNCMD, point.x, point.y, AfxGetApp()->m_pMainWnd, TPM_LEFTALIGN);*/
	}
	return 1;
}


void CClockDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
	CMenu* pPopup = s_Tray.GetSubMenu(0);
	POINT point;
	GetCursorPos(&point);
	auto w = AfxGetApp()->m_pMainWnd;
	auto x = pPopup->TrackPopupMenu(TPM_RETURNCMD, point.x, point.y, AfxGetApp()->m_pMainWnd, TPM_LEFTALIGN);

}


void CClockDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMenu* pPopup = s_Tray.GetSubMenu(0);
	int x = 0;
	GetCursorPos(&point);
	x = pPopup->TrackPopupMenu(TPM_RETURNCMD, point.x, point.y, AfxGetApp()->m_pMainWnd, TPM_LEFTALIGN);
	auto e= GetLastError();
	//CDialogEx::OnRButtonDown(nFlags, point);
	
}
