//// CSettings.cpp: 实现文件

#include "CSettings.h"
//// CSettings 对话框

CSettings::CSettings(MainWindow* parent):
	QObject(parent), ui(parent->GetUi())
{
	std::tie(p_strRegionOld, p_nDurationOld, p_nDelayOld) = MainWindow::m_srtClock.GetSetting();
	Initial();
	connect(ui->timeZone, qOverload<int>(&QButtonGroup::buttonClicked), this, &CSettings::OnBnClickedCheck);
	auto valid = new QIntValidator(1, 60);
	ui->Delay->setValidator(valid);
	ui->Duration->setValidator(valid);
	connect(ui->Delay, &QLineEdit::textEdited, this, &CSettings::OnEnChangeEdit);
	connect(ui->Duration, &QLineEdit::textEdited, this, &CSettings::OnEnChangeEdit);
	connect(ui->Apply, &QPushButton::clicked, this, &CSettings::OnBnClickedButton);

}

bool CSettings::OnKillActive()
{
	if (ui->Apply->isEnabled())
	{
		if (MainWindow::Unsaved())
		{
			return false;
		}
		else
		{			
			Initial();
		}
	}
	return true;
}

void CSettings::Initial()
{
	ui->Apply->setDisabled(true);
	std::tie(p_strRegion, p_nDuration, p_nDelay) = std::tie(p_strRegionOld, p_nDurationOld, p_nDelayOld);
	auto&& zones = ui->timeZone->buttons();
	for (int i = 0; i < zones.size(); i++)
	{
		if (p_strRegion.find(p_chszRegions[i]) != std::string::npos)
		{
			zones[i]->setChecked(true);
		}
		else
		{
			zones[i]->setChecked(false);
		}
	}
	ui->Duration->setPlaceholderText(QString::number(p_nDuration));
	ui->Delay->setPlaceholderText(QString::number(p_nDelay));
	ui->Delay->setText("");
	ui->Duration->setText("");
}

void CSettings::OnBnClickedCheck()
{
	p_strRegion.clear();
	auto&& zones = ui->timeZone->buttons();
	for (int i = 0; i < zones.size(); i++)
	{
		if (zones[i]->isChecked())
		{
			p_strRegion += p_chszRegions[i] + ' ';
		}
	}
	setEnabled();
}

void CSettings::OnBnClickedButton()
{
	if (p_strRegion != p_strRegionOld
		&& MainWindow::m_srtClock.ChangeRegion(p_strRegion))
	{
		((MainWindow*)parent())->ChangeRegion();
		p_strRegionOld = p_strRegion;
	}
	if (p_nDelay != p_nDelayOld
		&& MainWindow::m_srtClock.ChangeSetting(CClock::_LOG::eTYPE::DELAY, p_nDelay))
	{
		p_nDelayOld = p_nDelay;
		ui->Delay->setPlaceholderText(QString::number(p_nDelay));
	}
	if (p_nDuration != p_nDurationOld
		&& MainWindow::m_srtClock.ChangeSetting(CClock::_LOG::eTYPE::DURATION, p_nDuration))
	{
		p_nDurationOld = p_nDuration;
		ui->Duration->setPlaceholderText(QString::number(p_nDuration));	
	}
	ui->Delay->setText("");
	ui->Duration->setText("");

	setEnabled();
}

void CSettings::OnEnChangeEdit()
{
	int delay = ui->Delay->text().toInt();
	p_nDelay = delay ? delay : p_nDelayOld;

	int duration = ui->Duration->text().toInt();
	p_nDuration = duration ? duration : p_nDurationOld;
	
	setEnabled();
}

inline void CSettings::setEnabled() {
	ui->Apply->setDisabled((p_strRegionOld == p_strRegion
		&& p_nDelayOld == p_nDelay && p_nDurationOld == p_nDuration)
		|| 0 == p_nDelay || 0 == p_nDuration);
}

