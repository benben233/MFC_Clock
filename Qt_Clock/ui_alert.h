/********************************************************************************
** Form generated from reading UI file 'alert.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALERT_H
#define UI_ALERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QListWidget *listWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *Stop;
    QPushButton *Delay;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->setWindowModality(Qt::ApplicationModal);
        Dialog->resize(407, 298);
        listWidget = new QListWidget(Dialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(60, 20, 281, 201));
        listWidget->setFrameShape(QFrame::NoFrame);
        horizontalLayoutWidget = new QWidget(Dialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(180, 250, 195, 30));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Stop = new QPushButton(horizontalLayoutWidget);
        Stop->setObjectName(QStringLiteral("Stop"));

        horizontalLayout->addWidget(Stop);

        Delay = new QPushButton(horizontalLayoutWidget);
        Delay->setObjectName(QStringLiteral("Delay"));

        horizontalLayout->addWidget(Delay);


        retranslateUi(Dialog);
        QObject::connect(Stop, SIGNAL(clicked()), Dialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        Stop->setText(QApplication::translate("Dialog", "\345\201\234\346\255\242", Q_NULLPTR));
        Delay->setText(QApplication::translate("Dialog", "\345\273\266\350\277\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALERT_H
