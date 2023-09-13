#pragma once
#include "mainwindow.h"
// CSettings 对话框

class CSettings : public QObject
{
	Q_OBJECT
	Ui::MainWindow* ui;
public:
	explicit CSettings(MainWindow* parent);   // 标准构造函数
	bool OnKillActive();
	void Initial();
public slots:
	void OnBnClickedCheck();
	void OnBnClickedButton();
	void OnEnChangeEdit();
private:
	inline const static std::string p_chszRegions[] = { "北京", "东京", "伦敦", "华盛顿" };
	std::string p_strRegion, p_strRegionOld;
	void setEnabled();
	int p_nDuration, p_nDelay;
	int p_nDurationOld, p_nDelayOld;

};
