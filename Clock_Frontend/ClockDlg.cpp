
// ClockDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Clock.h"
#include "ClockDlg.h"
#include "CAlert.h"
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
	: CDialogEx(IDD_CLOCK_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClockDlg::~CClockDlg()
{
	Shell_NotifyIcon(NIM_DELETE, &s_TrayIcon);
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
	ON_MESSAGE(WM_ONTRAY, &CClockDlg::OnOntray)
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
	s_Tab.AddPage(&s_srtAlarmPage);
	s_Tab.AddPage(&s_srtLog);
	s_Tab.AddPage(&s_srtSettings);
	EnableDynamicLayout();
	s_Tab.Create(this, WS_CHILD | WS_VISIBLE   , WS_EX_CONTROLPARENT);
	
	//在初始化里写更改对话框图标
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, FALSE);
	//在OnInitDialog方法中调用
	
	s_TrayIcon.cbSize = sizeof(NOTIFYICONDATA);//结构体的大小
	s_TrayIcon.hWnd = this->m_hWnd;//接收托盘消息的窗口句柄 this是当前dialog
	s_TrayIcon.uID = IDR_MAINFRAME;//定义的托盘图标ID
	s_TrayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;//设置属性，下面的三个属性是否有效
	lstrcpyn(s_TrayIcon.szTip, _T("单击右键显示菜单"), sizeof(_T("单击右键显示菜单")));//图标上的提示字符串
	s_TrayIcon.uCallbackMessage = WM_ONTRAY;//自定义的消息，

	s_TrayIcon.hIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));//显示在系统托盘上的图标
	Shell_NotifyIcon(NIM_ADD, &s_TrayIcon);// 向任务栏的状态栏发送添加托盘图标的消息
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



void CClockDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	size_t index;
	static CAlert alert;
	bool IsAlarm = CClockApp::m_srtClock.Update_TimeAlarm(alert.m_strAlert, index);
	alert.SetAlarm(IsAlarm);
	s_srtZonedTime.Update();
	if (index != -1)
	{
		if (!alert.IsModal)
		{
			alert.m_lstIndex.push_back(index);
			alert.DoModal();
			for (auto& i : alert.m_lstIndex)
			{
				
				s_srtAlarmPage.UpdateAlarm(i);
			}
			alert.m_lstIndex.clear();
		}	
		else
		{
			alert.Add(index);
		}
		
	}

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
		ShowWindow(SW_SHOWNORMAL);
	}
	else if (WM_RBUTTONUP == lParam)
	{
		CMenu* pPopup = s_Tray.GetSubMenu(0);
		POINT point;
		GetCursorPos(&point);	
		SetForegroundWindow();
		auto x= pPopup->TrackPopupMenu(TPM_RETURNCMD, point.x, point.y, this, TPM_LEFTALIGN);
		if (x == ID_EXIT && s_srtAlarmPage.OnKillActive() && s_srtSettings.OnKillActive())
		{
			PostQuitMessage(NULL);
		}
		else if(x == ID_DISPLAY)
		{
			ShowWindow(SW_SHOWNORMAL);
		}
	}
	return 1;
}
