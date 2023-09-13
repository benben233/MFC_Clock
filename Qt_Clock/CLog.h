#pragma once
#include "mainwindow.h"
// CLog 对话框

class CLog : public QObject
{
	Q_OBJECT
	Ui::MainWindow* ui;
public:
	explicit CLog(MainWindow* parent);   // 标准构造函数
	~CLog();
	void Search();
// 对话框数据
public slots:
	 void OnLbnSelchangeList();
	 void clear();
	 void OnDtnDatetimechangeDatetimepicker1(const QDateTime& datetime);
	 void OnDtnDatetimechangeDatetimepicker2(const QDateTime& datetime);
	 void OnBnClickedButton();
private:
	constexpr static const char* p_chszLog[]{ "更改时区","更改延迟时间","更改持续时间","新增闹钟","删除闹钟","更改闹钟" };
	constexpr static size_t p_TypeNum = std::size(p_chszLog);
	std::chrono::local_days From, To;
	std::bitset<std::size(p_chszLog)> Type;
	
};
