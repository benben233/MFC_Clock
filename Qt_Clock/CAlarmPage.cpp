// CAlarmPage.cpp: 实现文件

#include "CAlarmPage.h"
//// CAlarmPage 对话框

CAlarmPage::CAlarmPage(MainWindow* parent)
	: QObject(parent), ui(parent->GetUi()),p_vctAlert(MainWindow::m_srtClock.GetAlert())
{
	p_Alert.srtTime = p_AlertNew.srtTime = CClock::now();
	ui->alarmTime->setDateTime(QDateTime::currentDateTime());
	for (int i = 0; i < p_vctAlert.size(); i++)
	{
		UpdateList(i);
	}
	ui->alarmList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	connect(ui->alarmList, &QTableWidget::itemSelectionChanged, this, &CAlarmPage::OnLvnItemchangedList);
	connect(ui->alarmAdd, &QPushButton::clicked, this, &CAlarmPage::OnBnClickedAdd);
	connect(ui->alarmChange, &QPushButton::clicked, this, &CAlarmPage::OnBnClickedChange);
	connect(ui->alarmDelete, &QPushButton::clicked, this, &CAlarmPage::OnBnClickedDelete);
	connect(ui->alarmLabel, &QLineEdit::textEdited, this, &CAlarmPage::OnEnChangeLabel);
	connect(ui->alarmTime, &QDateTimeEdit::dateTimeChanged, this, &CAlarmPage::OnDtnDatetimechangeDatetimepicker);
	connect(ui->CycleW, &QListWidget::itemSelectionChanged, this, &CAlarmPage::OnLbnSelchangeCycleW);
	connect(ui->CycleD, &QLineEdit::textEdited, this, &CAlarmPage::OnEnChangeEdit);
	connect(ui->Enable, &QRadioButton::clicked, this, &CAlarmPage::OnBnClickedRadio);
	connect(ui->Disable, &QRadioButton::clicked, this, &CAlarmPage::OnBnClickedRadio);
	ui->CycleD->setValidator(new QIntValidator(1, 999));
}

bool CAlarmPage::OnKillActive()
{
	if (p_bChanged)
	{
		if (MainWindow::Unsaved())
		{
			return false;
		}
		else
		{
			if (-1 != p_nSel )
			{
				Update(p_nSel);
			}
			else
			{
				clear();
			}		
		}
	}
	return true;
}

void CAlarmPage::OnLvnItemchangedList()
{
	if (p_bChanged && MainWindow::Unsaved())
	{
		ui->alarmList->blockSignals(true);
		if (p_nSel==-1)
		{
			ui->alarmList->clearSelection();
		}
		else
		{
			ui->alarmList->selectRow(p_nSel);
		}
		ui->alarmList->blockSignals(false);
	}
	else
	{
		Update(ui->alarmList->currentRow());
	}
}

void CAlarmPage::OnEnChangeLabel(const QString& str)
{
	p_AlertNew.strLabel = str.toLocal8Bit().constData();
	SetChange();
}


void CAlarmPage::OnLbnSelchangeCycleW()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < 7; i++)
	{
		p_AlertNew.CycleW[i] = ui->CycleW->item(i)->isSelected();
	}
	if (1 == p_AlertNew.CycleW.count())
	{
		p_AlertNew.srtCycleD = std::chrono::days(7);
		ui->CycleD->setText("7");
	}
	else
	{
		p_AlertNew.srtCycleD = std::chrono::days(0);
		ui->CycleD->setText("");
	}
	SetChange();
}

void CAlarmPage::OnEnChangeEdit(const QString& str)
{
	int d = str.toInt();
	p_AlertNew.srtCycleD = std::chrono::days(d);
	if (d > 0)
	{
		p_AlertNew.CycleW = 0;
		ui->CycleW->clearSelection();
		if (7 == d)
		{
			int wd = std::chrono::weekday(floor<std::chrono::days>(CClock::now())).c_encoding();
			ui->CycleW->item(wd)->setSelected(true);
			p_AlertNew.CycleW[wd] = true;
		}
	}
	SetChange();
}



void CAlarmPage::OnBnClickedRadio()
{
	// TODO: 在此添加控件通知处理程序代码	
	p_AlertNew.bEnable = ui->Enable->isChecked();
	SetChange();
}

void CAlarmPage::OnDtnDatetimechangeDatetimepicker(const QDateTime& datetime)
{
	p_AlertNew.srtTime = MainWindow::to_local(datetime);
	SetChange();	
}

void CAlarmPage::clear()
{
	p_Alert = p_AlertNew = CAlarm::_ALERT();
	ui->alarmLabel->clear();
	p_Alert.srtTime = p_AlertNew.srtTime = CClock::now();
	ui->alarmTime->setDateTime(QDateTime::currentDateTime());
	ui->CycleW->clearSelection();
	ui->CycleD->clear();
	ui->Enable->setChecked(true);
	ui->alarmDelete->setEnabled(false);
	SetChange(false);
}

/******************************************************************************
* 更新显示第index行数据
* [in]目标行的index
******************************************************************************/
void CAlarmPage::Update(int index)
{
	p_nSel = index;
	if (index >= p_vctAlert.size())
	{
		clear();
		return;
	}

	p_Alert = p_AlertNew = p_vctAlert[index];
	ui->alarmLabel->setText(to_Qstr(p_Alert.strLabel));
	ui->alarmTime->setDateTime(QDateTime::fromSecsSinceEpoch(p_Alert.srtTime.time_since_epoch().count(),Qt::UTC));

	for (int i = 0; i < 7; i++)
	{
		ui->CycleW->item(i)->setSelected(p_Alert.CycleW[i]);
	}
	int d = p_Alert.srtCycleD.count();
	ui->CycleD->setText(d ? QString::number(d) : QString());

	p_Alert.bEnable ? ui->Enable->setChecked(true) : ui->Disable->setChecked(true);

	SetChange(false);
	ui->alarmDelete->setEnabled(true);
}

/******************************************************************************
* 根据后台数据更新列表第index行
* [in]目标闹钟的index
******************************************************************************/
void CAlarmPage::UpdateList(int index)
{
	auto vct = CAlarm::to_string(p_vctAlert[index]);
	if (index >= ui->alarmList->rowCount() - 1)
	{
		ui->alarmList->setRowCount(index + 2);
	}
	for (int i = 0; i < vct.size(); i++)
	{
		ui->alarmList->setItem(index, i, new QTableWidgetItem(to_Qstr(vct[i])));
	}
}

bool CAlarmPage::Check()
{
//#undef DEBUG
#ifndef _DEBUG
	if (p_AlertNew.srtTime <= CClock::now() && p_AlertNew.bEnable)
	{
		QMessageBox::warning(nullptr, to_Qstr("时间错误"), to_Qstr("设置闹钟时间不能小于当前时间"));
		return false;
	}
	int d = ui->alarmTime->date().dayOfWeek();
	if (7 == d)
	{
		d = 0;
	}
	if (p_AlertNew.CycleW.any() && !p_AlertNew.CycleW[d])
	{
		QMessageBox::warning(nullptr, to_Qstr("日期错误"), to_Qstr("闹钟时间与循环周期设置的星期不匹配"));
		return false;
	}
#define _DEGUG
#endif // !_DEBUG
	return true;

}


void CAlarmPage::OnBnClickedAdd()
{
	if (!Check())
	{
		return;
	}
	if (MainWindow::m_srtClock.ChangeAlarm(CClock::_LOG::eTYPE::ADD_ALARM, p_AlertNew))
	{
		UpdateList(ui->alarmList->rowCount() - 1);
		p_AlertNew.nID = p_Alert.nID;
		p_bChanged = false;
	}
	else
	{
		QMessageBox::critical(nullptr, to_Qstr("创建错误"), to_Qstr("无法创建新闹钟，可能超过512个"));
	}
}

void CAlarmPage::OnBnClickedChange()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!Check())
	{
		return;
	}
	MainWindow::m_srtClock.ChangeAlarm(CClock::_LOG::eTYPE::CHANGE_ALARM, p_AlertNew);
	UpdateList(ui->alarmList->currentRow());
	p_Alert = p_AlertNew;
	SetChange(false);
}

void CAlarmPage::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (p_bChanged && MainWindow::Unsaved())
	{
		return;
	}
	MainWindow::m_srtClock.ChangeAlarm(CClock::_LOG::eTYPE::DELETED_ALARM, p_AlertNew);
	p_bChanged = false;
	ui->alarmList->removeRow(ui->alarmList->currentRow());
	Update(ui->alarmList->currentRow());
}

void CAlarmPage::SetChange(bool change)
{
	if (change)
	{
		p_bChanged = p_bChanged ? (p_AlertNew.bEnable != p_Alert.bEnable)
			|| (p_AlertNew.nID != p_Alert.nID)
			|| (p_AlertNew.srtCycleD != p_Alert.srtCycleD)
			|| (p_AlertNew.srtTime != p_Alert.srtTime)
			|| (p_AlertNew.strLabel != p_Alert.strLabel)
			|| (p_AlertNew.CycleW != p_Alert.CycleW) : true;
		if (p_nSel != ui->alarmList->rowCount() - 1 && p_nSel != -1)
		{
			ui->alarmChange->setEnabled(p_bChanged);
		}
	}
	else
	{
		p_bChanged = false;	
		ui->alarmChange->setEnabled(false);
	}
}

