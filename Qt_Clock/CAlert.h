#pragma once
#include <QDialog>

namespace Ui {
	class Dialog;
}
// CAlert 对话框

class CAlert : public QDialog
{
	Q_OBJECT

public:
	explicit CAlert(QWidget* parent = 0);   // 标准构造函数
	~CAlert();
	void Add(size_t index);
	std::list<size_t> m_lstIndex;
	void clear();
	// 对话框数据
	std::string m_strAlert;
	void reject();
	void SetAlarm(bool);
	void OnBnClickedDelay();
private:
	
	Ui::Dialog* ui;
public:
	
};
