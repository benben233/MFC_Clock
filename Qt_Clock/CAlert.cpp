// CAlert.cpp: 实现文件
//
#include "CAlert.h"
#include "ui_alert.h"
#include "mainwindow.h"

// CAlert 对话框
CAlert::CAlert(QWidget* parent):   
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);
	connect(ui->Delay, &QPushButton::clicked, this, &CAlert::OnBnClickedDelay);
}

CAlert::~CAlert()
{
	delete ui;
}

void CAlert::Add(size_t index)
{
	if (m_lstIndex.empty() || index != m_lstIndex.back())
	{
		ui->listWidget->insertItem(m_lstIndex.size(), to_Qstr(m_strAlert));
		m_lstIndex.push_back(index);
	}
	else
	{
		ui->listWidget->item(m_lstIndex.size() - 1)->setText(to_Qstr(m_strAlert));
	}
}

void CAlert::clear() {
	m_lstIndex.clear();
	ui->listWidget->clear();
}

void CAlert::SetAlarm(bool b)
{
	ui->Stop->setEnabled(b);
	ui->Delay->setEnabled(b);
}

void CAlert::OnBnClickedDelay()
{
	finished(2);
	ui->Stop->setEnabled(false);
	QDialog::reject();
}

void CAlert::reject()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ui->Stop->isEnabled())
	{
		QMessageBox::information(this, "关闭闹钟", "默认停止闹钟");
		accept();
	}
	QDialog::reject();
}
