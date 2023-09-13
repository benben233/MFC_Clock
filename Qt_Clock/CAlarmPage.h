#pragma once
#include "mainwindow.h"

// CAlarmPage 对话框
class CAlarmPage : public QObject
{
	Q_OBJECT
	Ui::MainWindow* ui;
public:
	explicit CAlarmPage(MainWindow* parent);   // 标准构造函数
	bool OnKillActive();

public slots:
	 void OnLvnItemchangedList();
	 void OnEnChangeLabel(const QString&);
	 void OnEnChangeEdit(const QString&);
	 void OnLbnSelchangeCycleW();
	 void OnBnClickedRadio();
	 void OnDtnDatetimechangeDatetimepicker(const QDateTime& datetime);
	 void OnBnClickedAdd();
	 void OnBnClickedChange();
	 void OnBnClickedDelete();
	// void OnLvnItemchangingList(NMHDR* pNMHDR, LRESULT* pResult);
private:
	bool p_bChanged{ false };
	int p_nSel{ -1 };
	void SetChange(bool = true);
	const std::vector<CAlarm::_ALERT>& p_vctAlert;
	CAlarm::_ALERT p_Alert, p_AlertNew;
public:
	bool Check();
	void clear();
	void Update(int index);
	void UpdateList(int index);
	void UpdateAlarm(int index) {
		UpdateList(index);
		if (index == p_nSel)
		{
			SetChange();
		}
	}
};
