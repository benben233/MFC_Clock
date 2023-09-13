#include "mainwindow.h"
#include "CAlarmPage.h"
#include "CSettings.h"
#include "CZonedTime.h"
#include "CLog.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    alert(this)
{
    ui->setupUi(this);
    p_Settings = new CSettings(this);
    p_Alarm = new CAlarmPage(this);
    p_Log = new CLog(this);
    QTimer* t = new QTimer;
    t->setInterval(1000);
    QMainWindow::connect(t, &QTimer::timeout, this, &MainWindow::UpdateData);
    t->start();
    ChangeRegion();

    QIcon icon = QIcon("./alarmIcon.png");
    setWindowIcon(icon);
    trayIcon = new QSystemTrayIcon(QIcon("./alarmIcon.png"));
    trayIcon->show();
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::Ontray);
    trayMenu.addAction(to_Qstr("显示"), this, &MainWindow::showNormal);
    trayMenu.addAction(to_Qstr("退出"), this, &MainWindow::close);
    trayIcon->setContextMenu(&trayMenu);

    connect(&alert, &QDialog::finished, this, &MainWindow::UpdateAlarm);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::TabChanged);
    p_nTab = ui->tabWidget->currentIndex();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete p_Settings;
    delete p_Alarm;
    delete p_Log;
    delete trayIcon;
    for (auto& i : p_vctTime)
    {
        delete i;
    }
}

void MainWindow::UpdateData()
{
    size_t index;
    bool IsAlarm = m_srtClock.Update_TimeAlarm(alert.m_strAlert, index);
    alert.SetAlarm(IsAlarm);
    for (auto& i : p_vctTime)
    {
        i->UpdateData();
    }
    if (index != -1)
    {
        alert.Add(index);
        show();
        alert.show();
    }
}

void MainWindow::UpdateAlarm(int result)
{
    if (result == 1)
    {
        m_srtClock.Stop();
    }
    else if (result == 2)
    {
        m_srtClock.Delay();
        alert.m_lstIndex.pop_back();
    }
    for (auto& i : alert.m_lstIndex)
    {
        p_Alarm->UpdateAlarm(i);
    }
    alert.clear();
}

void MainWindow::ChangeRegion()
{
    for (auto& i : p_vctTime)
    {
        delete i;
    }
    p_vctTime.clear();
    for (auto& i : m_srtClock.GetTime())
    {
        CZonedTime* zt = new CZonedTime(i);
        ui->times->addWidget(zt);
        p_vctTime.emplace_back(zt);
    }
}

void MainWindow::Ontray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        showNormal();
        break;
    default:
        break;
    }
}

void MainWindow::TabChanged(int index)
{
    if (index==2)
    {
        p_Log->Search();
    }
    switch (p_nTab)
    {
    case 1:
    case 3:
        ui->tabWidget->blockSignals(true);
        ui->tabWidget->setCurrentIndex(p_nTab);
        if ((3 == p_nTab && p_Settings->OnKillActive())
            || (1== p_nTab && p_Alarm->OnKillActive()))
        {
            ui->tabWidget->setCurrentIndex(index);
            p_nTab = index;
        }
        ui->tabWidget->blockSignals(false);
        return;
    default:
        p_nTab = index;
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (!event->spontaneous() || !isVisible())
    {
        if (3 == p_nTab || 1 == p_nTab)
        {
            if (p_Settings->OnKillActive() != true || p_Alarm->OnKillActive()!=true )
            {
                event->ignore();
            }
        }
        return;
    }  
    if (trayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
}