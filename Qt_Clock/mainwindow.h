#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "..\Clock_Backend\clock.h"
#include "ui_mainwindow.h"
#include "CAlert.h"
namespace Ui {
class MainWindow;
}

inline QString to_Qstr(const std::string& str) {
    return QString::fromLocal8Bit(str.c_str());
}
inline QString to_Qstr(const char* str) {
    return QString::fromLocal8Bit(str);
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
        
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    inline static CClock m_srtClock;
    static bool Unsaved() {
       return QMessageBox::question(nullptr, to_Qstr("未保存"), to_Qstr("有尚未保存的内容，是否放弃更改"),
           to_Qstr("放弃"), to_Qstr("取消"));
    }
    static auto to_local(const QDateTime& datetime) {
        return CClock::to_local(std::chrono::sys_seconds(
            std::chrono::seconds(datetime.toSecsSinceEpoch())));
    }
    Ui::MainWindow* GetUi() {
        return ui;
    }
    void ChangeRegion();
protected:
    void closeEvent(QCloseEvent* event);
private slots:
    void UpdateData();
    void UpdateAlarm(int result);
    void Ontray(QSystemTrayIcon::ActivationReason reason);
    void TabChanged(int index);
private:
    int p_nTab;
    std::vector<class CZonedTime*> p_vctTime;
    class CSettings* p_Settings;
    class CAlarmPage* p_Alarm;
    class CLog* p_Log;
    class CAlert alert;
    QSystemTrayIcon* trayIcon;
    QMenu trayMenu;
    QCalendarWidget c;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
