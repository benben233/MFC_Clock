/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiona;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *zonedTime;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *times;
    QWidget *alarm;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *alarmList;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_2;
    QLabel *IDC_STATIC;
    QDateTimeEdit *alarmTime;
    QLabel *IDC_STATIC_9;
    QLineEdit *alarmLabel;
    QLabel *IDC_STATIC_2;
    QListWidget *CycleW;
    QHBoxLayout *horizontalLayout_11;
    QLabel *IDC_STATIC_8;
    QLabel *label;
    QLineEdit *CycleD;
    QLabel *IDC_STATIC_7;
    QGridLayout *gridLayout;
    QRadioButton *Disable;
    QRadioButton *Enable;
    QPushButton *alarmAdd;
    QPushButton *alarmDelete;
    QPushButton *alarmChange;
    QSpacerItem *verticalSpacer_2;
    QWidget *log;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *logTable;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *IDC_STATIC_11;
    QListWidget *logType;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *IDC_STATIC_10;
    QDateEdit *logFrom;
    QLabel *IDC_STATIC_12;
    QDateEdit *logTo;
    QSpacerItem *verticalSpacer_3;
    QPushButton *logClear;
    QPushButton *logSave;
    QWidget *settings;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *IDC_CHECK1;
    QCheckBox *IDC_CHECK2;
    QCheckBox *IDC_CHECK3;
    QCheckBox *IDC_CHECK4;
    QGroupBox *alarmSettings;
    QHBoxLayout *horizontalLayout_2;
    QLabel *IDC_STATIC_6;
    QLineEdit *Duration;
    QLabel *IDC_STATIC_4;
    QSpacerItem *horizontalSpacer;
    QLabel *IDC_STATIC_5;
    QLineEdit *Delay;
    QLabel *IDC_STATIC_3;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Apply;
    QButtonGroup *timeZone;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(838, 447);
#ifndef QT_NO_TOOLTIP
        MainWindow->setToolTip(QStringLiteral(""));
#endif // QT_NO_TOOLTIP
        actiona = new QAction(MainWindow);
        actiona->setObjectName(QStringLiteral("actiona"));
        actiona->setCheckable(true);
        widget = new QWidget(MainWindow);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(true);
        zonedTime = new QWidget();
        zonedTime->setObjectName(QStringLiteral("zonedTime"));
        horizontalLayout_6 = new QHBoxLayout(zonedTime);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        times = new QHBoxLayout();
        times->setSpacing(10);
        times->setObjectName(QStringLiteral("times"));
        times->setContentsMargins(5, 20, 5, 20);

        horizontalLayout_6->addLayout(times);

        tabWidget->addTab(zonedTime, QString());
        alarm = new QWidget();
        alarm->setObjectName(QStringLiteral("alarm"));
        horizontalLayout_4 = new QHBoxLayout(alarm);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        alarmList = new QTableWidget(alarm);
        if (alarmList->columnCount() < 5)
            alarmList->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        alarmList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        alarmList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        alarmList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        alarmList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        alarmList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        alarmList->setObjectName(QStringLiteral("alarmList"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(alarmList->sizePolicy().hasHeightForWidth());
        alarmList->setSizePolicy(sizePolicy);
        alarmList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        alarmList->setSelectionMode(QAbstractItemView::SingleSelection);
        alarmList->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_4->addWidget(alarmList);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        IDC_STATIC = new QLabel(alarm);
        IDC_STATIC->setObjectName(QStringLiteral("IDC_STATIC"));
        IDC_STATIC->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC->setWordWrap(true);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, IDC_STATIC);

        alarmTime = new QDateTimeEdit(alarm);
        alarmTime->setObjectName(QStringLiteral("alarmTime"));
        alarmTime->setCalendarPopup(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, alarmTime);

        IDC_STATIC_9 = new QLabel(alarm);
        IDC_STATIC_9->setObjectName(QStringLiteral("IDC_STATIC_9"));
        IDC_STATIC_9->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_9->setWordWrap(true);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, IDC_STATIC_9);

        alarmLabel = new QLineEdit(alarm);
        alarmLabel->setObjectName(QStringLiteral("alarmLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(alarmLabel->sizePolicy().hasHeightForWidth());
        alarmLabel->setSizePolicy(sizePolicy1);
        alarmLabel->setClearButtonEnabled(true);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, alarmLabel);


        verticalLayout->addLayout(formLayout_2);

        IDC_STATIC_2 = new QLabel(alarm);
        IDC_STATIC_2->setObjectName(QStringLiteral("IDC_STATIC_2"));
        IDC_STATIC_2->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_2->setWordWrap(true);

        verticalLayout->addWidget(IDC_STATIC_2);

        CycleW = new QListWidget(alarm);
        new QListWidgetItem(CycleW);
        new QListWidgetItem(CycleW);
        new QListWidgetItem(CycleW);
        new QListWidgetItem(CycleW);
        new QListWidgetItem(CycleW);
        new QListWidgetItem(CycleW);
        new QListWidgetItem(CycleW);
        CycleW->setObjectName(QStringLiteral("CycleW"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(CycleW->sizePolicy().hasHeightForWidth());
        CycleW->setSizePolicy(sizePolicy2);
        CycleW->setMaximumSize(QSize(16777215, 30));
        CycleW->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        CycleW->setEditTriggers(QAbstractItemView::NoEditTriggers);
        CycleW->setSelectionMode(QAbstractItemView::MultiSelection);
        CycleW->setViewMode(QListView::IconMode);

        verticalLayout->addWidget(CycleW);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(2);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        IDC_STATIC_8 = new QLabel(alarm);
        IDC_STATIC_8->setObjectName(QStringLiteral("IDC_STATIC_8"));
        IDC_STATIC_8->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_8->setTextFormat(Qt::PlainText);
        IDC_STATIC_8->setWordWrap(true);

        horizontalLayout_11->addWidget(IDC_STATIC_8);

        label = new QLabel(alarm);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(18, 16777215));

        horizontalLayout_11->addWidget(label);

        CycleD = new QLineEdit(alarm);
        CycleD->setObjectName(QStringLiteral("CycleD"));
        CycleD->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_11->addWidget(CycleD);

        IDC_STATIC_7 = new QLabel(alarm);
        IDC_STATIC_7->setObjectName(QStringLiteral("IDC_STATIC_7"));
        IDC_STATIC_7->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_7->setWordWrap(true);

        horizontalLayout_11->addWidget(IDC_STATIC_7);


        verticalLayout->addLayout(horizontalLayout_11);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Disable = new QRadioButton(alarm);
        Disable->setObjectName(QStringLiteral("Disable"));

        gridLayout->addWidget(Disable, 0, 1, 1, 1);

        Enable = new QRadioButton(alarm);
        Enable->setObjectName(QStringLiteral("Enable"));
        sizePolicy1.setHeightForWidth(Enable->sizePolicy().hasHeightForWidth());
        Enable->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Enable, 0, 0, 1, 1);

        alarmAdd = new QPushButton(alarm);
        alarmAdd->setObjectName(QStringLiteral("alarmAdd"));
        sizePolicy1.setHeightForWidth(alarmAdd->sizePolicy().hasHeightForWidth());
        alarmAdd->setSizePolicy(sizePolicy1);
        alarmAdd->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(alarmAdd, 2, 0, 1, 1);

        alarmDelete = new QPushButton(alarm);
        alarmDelete->setObjectName(QStringLiteral("alarmDelete"));
        alarmDelete->setEnabled(false);
        alarmDelete->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(alarmDelete, 2, 2, 1, 1);

        alarmChange = new QPushButton(alarm);
        alarmChange->setObjectName(QStringLiteral("alarmChange"));
        alarmChange->setEnabled(false);
        alarmChange->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(alarmChange, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout_4->addLayout(verticalLayout);

        tabWidget->addTab(alarm, QString());
        log = new QWidget();
        log->setObjectName(QStringLiteral("log"));
        horizontalLayout_3 = new QHBoxLayout(log);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        logTable = new QTableWidget(log);
        if (logTable->columnCount() < 3)
            logTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        logTable->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        logTable->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        logTable->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        logTable->setObjectName(QStringLiteral("logTable"));
        logTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout_3->addWidget(logTable);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setHorizontalSpacing(7);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        IDC_STATIC_11 = new QLabel(log);
        IDC_STATIC_11->setObjectName(QStringLiteral("IDC_STATIC_11"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(IDC_STATIC_11->sizePolicy().hasHeightForWidth());
        IDC_STATIC_11->setSizePolicy(sizePolicy3);
        IDC_STATIC_11->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_11->setWordWrap(true);

        verticalLayout_3->addWidget(IDC_STATIC_11);

        logType = new QListWidget(log);
        logType->setObjectName(QStringLiteral("logType"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(logType->sizePolicy().hasHeightForWidth());
        logType->setSizePolicy(sizePolicy4);
        logType->setMinimumSize(QSize(100, 0));
        logType->setMaximumSize(QSize(150, 16777215));
        logType->setEditTriggers(QAbstractItemView::NoEditTriggers);
        logType->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout_3->addWidget(logType);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        IDC_STATIC_10 = new QLabel(log);
        IDC_STATIC_10->setObjectName(QStringLiteral("IDC_STATIC_10"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(1);
        sizePolicy5.setHeightForWidth(IDC_STATIC_10->sizePolicy().hasHeightForWidth());
        IDC_STATIC_10->setSizePolicy(sizePolicy5);
        IDC_STATIC_10->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_10->setWordWrap(true);

        verticalLayout_4->addWidget(IDC_STATIC_10);

        logFrom = new QDateEdit(log);
        logFrom->setObjectName(QStringLiteral("logFrom"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(1);
        sizePolicy6.setHeightForWidth(logFrom->sizePolicy().hasHeightForWidth());
        logFrom->setSizePolicy(sizePolicy6);
        logFrom->setCalendarPopup(true);

        verticalLayout_4->addWidget(logFrom);

        IDC_STATIC_12 = new QLabel(log);
        IDC_STATIC_12->setObjectName(QStringLiteral("IDC_STATIC_12"));
        sizePolicy5.setHeightForWidth(IDC_STATIC_12->sizePolicy().hasHeightForWidth());
        IDC_STATIC_12->setSizePolicy(sizePolicy5);
        IDC_STATIC_12->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_12->setWordWrap(true);

        verticalLayout_4->addWidget(IDC_STATIC_12);

        logTo = new QDateEdit(log);
        logTo->setObjectName(QStringLiteral("logTo"));
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(1);
        sizePolicy7.setHeightForWidth(logTo->sizePolicy().hasHeightForWidth());
        logTo->setSizePolicy(sizePolicy7);
        logTo->setCalendarPopup(true);

        verticalLayout_4->addWidget(logTo);

        verticalSpacer_3 = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout_4);

        logClear = new QPushButton(log);
        logClear->setObjectName(QStringLiteral("logClear"));
        QSizePolicy sizePolicy8(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(1);
        sizePolicy8.setVerticalStretch(1);
        sizePolicy8.setHeightForWidth(logClear->sizePolicy().hasHeightForWidth());
        logClear->setSizePolicy(sizePolicy8);

        formLayout->setWidget(1, QFormLayout::LabelRole, logClear);

        logSave = new QPushButton(log);
        logSave->setObjectName(QStringLiteral("logSave"));
        sizePolicy1.setHeightForWidth(logSave->sizePolicy().hasHeightForWidth());
        logSave->setSizePolicy(sizePolicy1);

        formLayout->setWidget(1, QFormLayout::FieldRole, logSave);


        horizontalLayout_3->addLayout(formLayout);

        tabWidget->addTab(log, QString());
        settings = new QWidget();
        settings->setObjectName(QStringLiteral("settings"));
        verticalLayout_2 = new QVBoxLayout(settings);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(settings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy9(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy9);
        groupBox->setMinimumSize(QSize(0, 50));
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        IDC_CHECK1 = new QCheckBox(groupBox);
        timeZone = new QButtonGroup(MainWindow);
        timeZone->setObjectName(QStringLiteral("timeZone"));
        timeZone->setExclusive(false);
        timeZone->addButton(IDC_CHECK1);
        IDC_CHECK1->setObjectName(QStringLiteral("IDC_CHECK1"));

        horizontalLayout_7->addWidget(IDC_CHECK1);

        IDC_CHECK2 = new QCheckBox(groupBox);
        timeZone->addButton(IDC_CHECK2);
        IDC_CHECK2->setObjectName(QStringLiteral("IDC_CHECK2"));

        horizontalLayout_7->addWidget(IDC_CHECK2);

        IDC_CHECK3 = new QCheckBox(groupBox);
        timeZone->addButton(IDC_CHECK3);
        IDC_CHECK3->setObjectName(QStringLiteral("IDC_CHECK3"));

        horizontalLayout_7->addWidget(IDC_CHECK3);

        IDC_CHECK4 = new QCheckBox(groupBox);
        timeZone->addButton(IDC_CHECK4);
        IDC_CHECK4->setObjectName(QStringLiteral("IDC_CHECK4"));

        horizontalLayout_7->addWidget(IDC_CHECK4);


        verticalLayout_2->addWidget(groupBox);

        alarmSettings = new QGroupBox(settings);
        alarmSettings->setObjectName(QStringLiteral("alarmSettings"));
        horizontalLayout_2 = new QHBoxLayout(alarmSettings);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        IDC_STATIC_6 = new QLabel(alarmSettings);
        IDC_STATIC_6->setObjectName(QStringLiteral("IDC_STATIC_6"));
        IDC_STATIC_6->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_6->setWordWrap(true);

        horizontalLayout_2->addWidget(IDC_STATIC_6);

        Duration = new QLineEdit(alarmSettings);
        Duration->setObjectName(QStringLiteral("Duration"));
        QSizePolicy sizePolicy10(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(Duration->sizePolicy().hasHeightForWidth());
        Duration->setSizePolicy(sizePolicy10);
        Duration->setMinimumSize(QSize(0, 0));
        Duration->setMaximumSize(QSize(30, 16777215));
        Duration->setClearButtonEnabled(false);

        horizontalLayout_2->addWidget(Duration);

        IDC_STATIC_4 = new QLabel(alarmSettings);
        IDC_STATIC_4->setObjectName(QStringLiteral("IDC_STATIC_4"));
        IDC_STATIC_4->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_4->setWordWrap(true);

        horizontalLayout_2->addWidget(IDC_STATIC_4);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        IDC_STATIC_5 = new QLabel(alarmSettings);
        IDC_STATIC_5->setObjectName(QStringLiteral("IDC_STATIC_5"));
        IDC_STATIC_5->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_5->setWordWrap(true);

        horizontalLayout_2->addWidget(IDC_STATIC_5);

        Delay = new QLineEdit(alarmSettings);
        Delay->setObjectName(QStringLiteral("Delay"));
        QSizePolicy sizePolicy11(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(Delay->sizePolicy().hasHeightForWidth());
        Delay->setSizePolicy(sizePolicy11);
        Delay->setMaximumSize(QSize(30, 16777215));
        Delay->setMaxLength(32767);
        Delay->setFrame(true);
        Delay->setClearButtonEnabled(false);

        horizontalLayout_2->addWidget(Delay);

        IDC_STATIC_3 = new QLabel(alarmSettings);
        IDC_STATIC_3->setObjectName(QStringLiteral("IDC_STATIC_3"));
        IDC_STATIC_3->setInputMethodHints(Qt::ImhMultiLine);
        IDC_STATIC_3->setWordWrap(true);

        horizontalLayout_2->addWidget(IDC_STATIC_3);

        horizontalSpacer_3 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(alarmSettings);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        frame = new QFrame(settings);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(0, 20));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_2 = new QSpacerItem(729, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        Apply = new QPushButton(frame);
        Apply->setObjectName(QStringLiteral("Apply"));

        horizontalLayout_9->addWidget(Apply);


        verticalLayout_2->addWidget(frame);

        tabWidget->addTab(settings, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(widget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actiona->setText(QApplication::translate("MainWindow", "a", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(zonedTime), QApplication::translate("MainWindow", "\346\227\266\351\227\264", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = alarmList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = alarmList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\217\220\351\206\222\346\226\207\345\255\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = alarmList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = alarmList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\346\217\220\351\206\222\345\221\250\346\234\237", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = alarmList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\346\230\257\345\220\246\345\220\257\347\224\250", Q_NULLPTR));
        IDC_STATIC->setText(QApplication::translate("MainWindow", "\346\217\220\351\206\222\346\226\207\345\255\227", Q_NULLPTR));
        alarmTime->setDisplayFormat(QApplication::translate("MainWindow", "yyyy/M/d H:mm:ss", Q_NULLPTR));
        IDC_STATIC_9->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264", Q_NULLPTR));
        IDC_STATIC_2->setText(QApplication::translate("MainWindow", "\345\276\252\347\216\257\345\221\250\346\234\237", Q_NULLPTR));

        const bool __sortingEnabled = CycleW->isSortingEnabled();
        CycleW->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = CycleW->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "\345\221\250\346\227\245", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem1 = CycleW->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "\345\221\250\344\270\200", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem2 = CycleW->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "\345\221\250\344\272\214", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem3 = CycleW->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", "\345\221\250\344\270\211", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem4 = CycleW->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindow", "\345\221\250\345\233\233", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem5 = CycleW->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("MainWindow", "\345\221\250\344\272\224", Q_NULLPTR));
        QListWidgetItem *___qlistwidgetitem6 = CycleW->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("MainWindow", "\345\221\250\345\205\255", Q_NULLPTR));
        CycleW->setSortingEnabled(__sortingEnabled);

        IDC_STATIC_8->setText(QApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211\345\276\252\347\216\257\345\244\251\346\225\260 ", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\257\217", Q_NULLPTR));
        IDC_STATIC_7->setText(QApplication::translate("MainWindow", "\345\244\251", Q_NULLPTR));
        Disable->setText(QApplication::translate("MainWindow", "\345\201\234\347\224\250", Q_NULLPTR));
        Enable->setText(QApplication::translate("MainWindow", "\345\220\257\347\224\250", Q_NULLPTR));
        alarmAdd->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\351\227\271\351\222\237", Q_NULLPTR));
        alarmDelete->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\351\227\271\351\222\237", Q_NULLPTR));
        alarmChange->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271\351\227\271\351\222\237", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(alarm), QApplication::translate("MainWindow", "\351\227\271\351\222\237", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = logTable->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\346\223\215\344\275\234\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = logTable->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "\346\223\215\344\275\234\346\227\266\351\227\264", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = logTable->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "\350\257\246\346\203\205", Q_NULLPTR));
        IDC_STATIC_11->setText(QApplication::translate("MainWindow", "\346\223\215\344\275\234\347\261\273\345\236\213", Q_NULLPTR));
        IDC_STATIC_10->setText(QApplication::translate("MainWindow", "\350\265\267\345\247\213\346\227\266\351\227\264", Q_NULLPTR));
        IDC_STATIC_12->setText(QApplication::translate("MainWindow", "\346\210\252\346\255\242\346\227\266\351\227\264", Q_NULLPTR));
        logClear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\347\255\233\351\200\211", Q_NULLPTR));
        logSave->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(log), QApplication::translate("MainWindow", "\345\216\206\345\217\262\350\256\260\345\275\225", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\230\276\347\244\272\346\227\266\345\214\272", Q_NULLPTR));
        IDC_CHECK1->setText(QApplication::translate("MainWindow", "\345\214\227\344\272\254", Q_NULLPTR));
        IDC_CHECK2->setText(QApplication::translate("MainWindow", "\344\270\234\344\272\254", Q_NULLPTR));
        IDC_CHECK3->setText(QApplication::translate("MainWindow", "\344\274\246\346\225\246", Q_NULLPTR));
        IDC_CHECK4->setText(QApplication::translate("MainWindow", "\345\215\216\347\233\233\351\241\277", Q_NULLPTR));
        alarmSettings->setTitle(QApplication::translate("MainWindow", "\351\227\271\351\222\237\350\256\276\347\275\256", Q_NULLPTR));
        IDC_STATIC_6->setText(QApplication::translate("MainWindow", "\346\214\201\347\273\255\346\227\266\351\227\264", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        Duration->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>\350\257\267\350\276\223\345\205\2451-60\347\232\204\346\225\264\346\225\260</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        Duration->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p>abc</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        IDC_STATIC_4->setText(QApplication::translate("MainWindow", "\345\210\206\351\222\237", Q_NULLPTR));
        IDC_STATIC_5->setText(QApplication::translate("MainWindow", "\345\273\266\350\277\237\346\227\266\351\227\264", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        Delay->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>\350\257\267\350\276\223\345\205\2451-60\347\232\204\346\225\264\346\225\260</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        Delay->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        Delay->setInputMask(QString());
        IDC_STATIC_3->setText(QApplication::translate("MainWindow", "\345\210\206\351\222\237", Q_NULLPTR));
        Apply->setText(QApplication::translate("MainWindow", "\345\272\224\347\224\250", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(settings), QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
