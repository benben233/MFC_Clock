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
	clear();
}

CLog::~CLog()
{
}

void CLog::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, p_TypeSel);
	DDX_Control(pDX, IDC_LIST2, p_LogList);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, p_strFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, p_strTo);
}

BOOL CLog::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();
	for (auto& i : m_chszLog)
	{ 
		p_TypeSel.AddString(CString(i));
	}
	p_LogList.InsertColumn(0, L"操作类型");
	p_LogList.InsertColumn(1, L"操作时间");
	p_LogList.InsertColumn(2, L"详情");
	return true;
}

BOOL CLog::OnSetActive()
{
	Search();
	return true;
}


BEGIN_MESSAGE_MAP(CLog, CMFCPropertyPage)
	ON_LBN_SELCHANGE(IDC_LIST1, &CLog::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CLog::OnBnClickedButton1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CLog::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER3, &CLog::OnDtnDatetimechangeDatetimepicker3)
	ON_BN_CLICKED(IDC_BUTTON3, &CLog::OnBnClickedButton3)
END_MESSAGE_MAP()


// CLog 消息处理程序


void CLog::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	CArray<int> Sel;
	Sel.SetSize(p_TypeSel.GetSelCount());
	Type = 0;
	p_TypeSel.GetSelItems(Sel.GetSize(), Sel.GetData());
	for (size_t i = 0; i < Sel.GetSize(); i++)
	{
		Type[Sel[i]] = true;
	}
	Search();
}

void CLog::Search()
{
	p_LogList.DeleteAllItems();
	m_lstLog = CClockApp::m_srtClock.GetLog(Type, From, To);
	int i = p_LogList.GetItemCount();

	auto log = m_lstLog.begin();
	for (int i = 0; i < m_lstLog.size(); i++, log++)
	{
		p_LogList.InsertItem(i, CString(m_chszLog[int(log->eType)]));
		std::ostringstream oss;
		oss << CClock::to_local(log->srtTime);
		p_LogList.SetItemText(i, 1, CString(oss.str().c_str()));
		p_LogList.SetItemText(i, 2, CString(log->strDetail.c_str()));
	}

	for (size_t i = 0; i < 3; i++)
	{
		p_LogList.SetColumnWidth(i, LVSCW_AUTOSIZE);
	}
}

void CLog::clear()
{
	Type = 0;
	std::ostringstream oss;
	To = floor<std::chrono::days>(CClock::now());
	oss << CClock::now();
	p_strTo = CString(oss.str().c_str());
	oss.str("");
	auto&& frontTime = CClockApp::m_srtClock.GetFrontLogTime();
	From = frontTime == nullptr ? To
		: floor<std::chrono::days>(CClock::to_local(*frontTime));
	oss << From;
	p_strFrom = CString(oss.str().c_str());
}

void CLog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	p_TypeSel.SelItemRange(false, 0, p_TypeSel.GetCount());
	clear();
	UpdateData(false);
	Search();
}


void CLog::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	UpdateData();
	std::istringstream iss{ CT2A(p_strFrom).m_psz };
	iss >> std::chrono::parse("%Y/%m/%d", From);
	Search();
}


void CLog::OnDtnDatetimechangeDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	UpdateData();
	std::istringstream iss{ CT2A(p_strTo).m_psz };
	iss >> std::chrono::parse("%Y/%m/%d", To);
	Search();
}


void CLog::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	static TCHAR BASED_CODE szFilter[] = _T("Text Files (*.txt)|*.txt|")
		_T("All Files (*.*)|*.*||");
	CFileDialog FileDlg(FALSE, CString(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	if (FileDlg.DoModal() == IDOK)
	{
		std::ofstream fs{ FileDlg.GetPathName() };
		for (auto& i : m_lstLog)
		{
			fs << m_chszLog[int(i.eType)] << ' ' << CClock::to_local(i.srtTime) << ' '
				<< i.strDetail << std::endl;
		}
		fs.close();
		if (fs)
		{
			MessageBox(L"保存成功");
		}
		else
		{
			MessageBox(L"保存失败");
		}
	}

}
