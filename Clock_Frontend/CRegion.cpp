// CRegion.cpp: 实现文件
//

#include "pch.h"
#include "Clock.h"
#include "CRegion.h"
#include "afxdialogex.h"


// CRegion 对话框

IMPLEMENT_DYNAMIC(CRegion, CDialogEx)

CRegion::CRegion(const CClock::_ZonedTime& strZonedTime, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIME, pParent)
	, p_strZonedTime(strZonedTime)
{
	std::apply([&](auto&... x) {auto t = std::make_tuple(CString(x.c_str())...);
	std::tie(p_strRegion, p_strDate, p_strTime) = t; }, strZonedTime);
	p_strRegion += "时间";
}

CRegion::~CRegion()
{

}

void CRegion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_TIME, p_strTime);
	DDX_Text(pDX, IDC_DATE, p_strDate);
	DDX_Text(pDX, IDC_REGION, p_strRegion);
}


BEGIN_MESSAGE_MAP(CRegion, CDialogEx)
ON_WM_DESTROY()

END_MESSAGE_MAP()


// CRegion 消息处理程序
BOOL CRegion::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	if (!TimeFont)
	{
		TimeFont = new CFont;
		LOGFONT lf;
		GetFont()->GetLogFont(&lf);
		StrCpyW(lf.lfFaceName, L"华文琥珀");
		lf.lfWeight = 100;
		TimeFont->CreateFontIndirectW(&lf);
	}
	return TRUE;
}

bool CRegion::CreatAfter(CRect& pRect, CWnd* pParent)
{
	
	bool b = Create(IDD_TIME , pParent);
	if (b)
	{
		if (pRect.IsRectEmpty())
		{
			CenterWindow();
			GetWindowRect(pRect);
			GetParent()->ScreenToClient(pRect);
		}
		else
		{
			pRect += SIZE(pRect.Width());
			MoveWindow(pRect);
		}
		ShowWindow(SW_SHOW);
	}
	return b;
}

bool CRegion::Update()
{
	std::tie(p_strDate, p_strTime) = std::apply([&](string region, auto&... x) 
		{return std::make_tuple(CString(x.c_str())...);}, p_strZonedTime);
	return UpdateData(false);
}

bool CRegion::ChangeTimeFontSize()
{
	auto w = GetDlgItem(IDC_TIME);
	CRect r,r1;
	w->GetClientRect(r);
	GetClientRect(r1);
	LOGFONT lf;
	TimeFont->GetLogFont(&lf);
	lf.lfHeight = r.Height();
	TimeFont->DeleteObject();
	bool b = TimeFont->CreateFontIndirectW(&lf);
	w->SetFont(TimeFont);
	return b;
}

void CRegion::OnDestroy()
{
	// TODO: 在此处添加消息处理程序代码
	CDialogEx::OnDestroy();
		if (TimeFont)
	{
		TimeFont->DeleteObject();
	}
}



