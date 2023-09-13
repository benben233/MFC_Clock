// CZonedTime.cpp: 实现文件
//

#include "CZonedTime.h"
#include "ui_time.h"

CZonedTime::CZonedTime(const CClock::_ZonedTime& strZonedTime):
	p_strZonedTime(strZonedTime),
	ui(new Ui::Time)
{
	ui->setupUi(this);
	setTitle(to_Qstr(get<0>(p_strZonedTime)) + "时间");
	UpdateData();
}

void CZonedTime::UpdateData()
{
	ui->label->setText(to_Qstr(get<1>(p_strZonedTime)));
	ui->lcdNumber->display(to_Qstr(get<2>(p_strZonedTime)));
}

