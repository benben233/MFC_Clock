// CLog.cpp: 实现文件
//
#include "CLog.h"



// CLog 对话框


CLog::CLog(MainWindow* parent) :
	QObject(parent), ui(parent->GetUi())
{
	for (size_t i = 0; i < p_TypeNum; i++)
	{
		ui->logType->insertItem(i, to_Qstr(p_chszLog[i]));
	}
	connect(ui->logClear, &QPushButton::clicked, this, &CLog::clear);
	connect(ui->logSave, &QPushButton::clicked, this, &CLog::OnBnClickedButton);
	connect(ui->logType, &QListWidget::itemSelectionChanged, this, &CLog::OnLbnSelchangeList);
	connect(ui->logFrom, &QDateEdit::dateTimeChanged, this, &CLog::OnDtnDatetimechangeDatetimepicker1);
	connect(ui->logTo, &QDateEdit::dateTimeChanged, this, &CLog::OnDtnDatetimechangeDatetimepicker2);
	auto a = ui->logTable->horizontalHeaderItem(1)->text();
	clear();
	Search();
}

CLog::~CLog()
{
}

void CLog::OnLbnSelchangeList()
{
	// TODO: 在此添加控件通知处理程序代码
	for (size_t i = 0; i < Type.size(); i++)
	{
		Type[i] = ui->logType->item(i)->isSelected();
	}
	Search();
}

void CLog::Search()
{
	QApplication::setOverrideCursor(Qt::BusyCursor);
	ui->logTable->clearContents();
	auto&& m_lstLog = MainWindow::m_srtClock.GetLog(Type, From, To);
	ui->logTable->setRowCount(m_lstLog.size());
	auto log = m_lstLog.begin();
	ui->logTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	for (int i = 0; i < m_lstLog.size(); i++, log++)
	{
		ui->logTable->setItem(i, 0, new QTableWidgetItem(to_Qstr(p_chszLog[int(log->eType)])));
		std::ostringstream oss;
		oss << CClock::to_local(log->srtTime);
		ui->logTable->setItem(i, 1, new QTableWidgetItem(to_Qstr(oss.str())));
		ui->logTable->setItem(i, 2, new QTableWidgetItem(to_Qstr(log->strDetail.c_str())));
	}
	ui->logTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//ui->logTable->repaint();
	QApplication::restoreOverrideCursor();
}

void CLog::clear()
{
	auto&& now = CClock::now();
	QDateTime&& Qnow = QDateTime::fromSecsSinceEpoch(now.time_since_epoch().count(), Qt::UTC);
	To = floor<std::chrono::days>(now);
	ui->logTo->blockSignals(true);
	ui->logTo->setDateTime(Qnow);
	ui->logTo->blockSignals(false);
	ui->logFrom->setMaximumDateTime(Qnow);

	ui->logFrom->blockSignals(true);
	auto&& time = MainWindow::m_srtClock.GetFrontLogTime();
	if (nullptr == time)
	{
		From = To;	
	}
	else
	{
		From = floor<std::chrono::days>(CClock::to_local(*time));
		Qnow = QDateTime::fromSecsSinceEpoch(time->time_since_epoch().count());	
	}
	ui->logFrom->setMinimumDateTime(Qnow);
	ui->logFrom->blockSignals(false);
	ui->logTo->setMinimumDateTime(Qnow);
	
	ui->logType->clearSelection();
}


void CLog::OnDtnDatetimechangeDatetimepicker1(const QDateTime& datetime)
{
	From = floor<std::chrono::days>(MainWindow::to_local(datetime));
	ui->logTo->setMinimumDateTime(datetime);
	Search();
}


void CLog::OnDtnDatetimechangeDatetimepicker2(const QDateTime& datetime)
{
	To = floor<std::chrono::days>(MainWindow::to_local(datetime));
	ui->logFrom->setMaximumDateTime(datetime);
	Search();
}


void CLog::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	auto fileName = QFileDialog::getSaveFileName(nullptr, "", "", "Text Files (*.txt);; All Files(*.*)");
	if (fileName.isEmpty())
	{
		return;
	}
	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(nullptr, tr("Unable to open file"),
			file.errorString());
		return;
	}
	QTextStream out(&file);
	for (int i = 0; i < ui->logTable->rowCount(); i++)
	{
		out << ui->logTable->item(i, 0)->text() << ' '
			<< ui->logTable->item(i, 1)->text() << ' '
			<< ui->logTable->item(i, 2)->text() << endl;
	}
	
	//file.close();
}
