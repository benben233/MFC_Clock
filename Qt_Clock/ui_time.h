/********************************************************************************
** Form generated from reading UI file 'time.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIME_H
#define UI_TIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Time
{
public:
    QVBoxLayout *verticalLayout;
    QLCDNumber *lcdNumber;
    QLabel *label;

    void setupUi(QGroupBox *Time)
    {
        if (Time->objectName().isEmpty())
            Time->setObjectName(QStringLiteral("Time"));
        Time->resize(417, 278);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        Time->setFont(font);
        verticalLayout = new QVBoxLayout(Time);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(11, -1, 11, -1);
        lcdNumber = new QLCDNumber(Time);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);
        lcdNumber->setSizeIncrement(QSize(0, 20));
        lcdNumber->setBaseSize(QSize(0, 20));
        lcdNumber->setFrameShape(QFrame::Box);
        lcdNumber->setFrameShadow(QFrame::Sunken);
        lcdNumber->setMidLineWidth(1);
        lcdNumber->setSmallDecimalPoint(true);
        lcdNumber->setDigitCount(8);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(1.23457e+7));
        lcdNumber->setProperty("intValue", QVariant(12345678));

        verticalLayout->addWidget(lcdNumber);

        label = new QLabel(Time);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        retranslateUi(Time);

        QMetaObject::connectSlotsByName(Time);
    } // setupUi

    void retranslateUi(QGroupBox *Time)
    {
        Time->setWindowTitle(QApplication::translate("Time", "GroupBox", Q_NULLPTR));
        Time->setTitle(QApplication::translate("Time", "GroupBox", Q_NULLPTR));
        label->setText(QApplication::translate("Time", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Time: public Ui_Time {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIME_H
