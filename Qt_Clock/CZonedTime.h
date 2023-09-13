#pragma once
// CRegion 对话框
// CZonedTime 对话框

#include "mainwindow.h"

namespace Ui {
	class Time;
}

class CZonedTime : public QGroupBox
{
	Q_OBJECT
	Ui::Time* ui;
	const CClock::_ZonedTime& p_strZonedTime;
public:
	CZonedTime(const CClock::_ZonedTime& p_strZonedTime);
	void UpdateData();
};
