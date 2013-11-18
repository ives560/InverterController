/********************************************************************************
** Form generated from reading UI file 'clock.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCK_H
#define UI_CLOCK_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QHeaderView>
#include <QtGui/QTimeEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Clock
{
public:
    QTimeEdit *timeEdit;
    QDateEdit *dateEdit;

    void setupUi(QWidget *Clock)
    {
        if (Clock->objectName().isEmpty())
            Clock->setObjectName(QString::fromUtf8("Clock"));
        Clock->resize(100, 40);
        timeEdit = new QTimeEdit(Clock);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(0, 0, 100, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font.setPointSize(9);
        timeEdit->setFont(font);
        timeEdit->setFocusPolicy(Qt::NoFocus);
        timeEdit->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"background: transparent;"));
        timeEdit->setAlignment(Qt::AlignCenter);
        timeEdit->setReadOnly(true);
        timeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dateEdit = new QDateEdit(Clock);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setEnabled(true);
        dateEdit->setGeometry(QRect(0, 20, 101, 20));
        dateEdit->setFont(font);
        dateEdit->setFocusPolicy(Qt::NoFocus);
        dateEdit->setAutoFillBackground(false);
        dateEdit->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"background:transparent;"));
        dateEdit->setAlignment(Qt::AlignCenter);
        dateEdit->setReadOnly(true);
        dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dateEdit->setDate(QDate(2000, 1, 1));
        QWidget::setTabOrder(dateEdit, timeEdit);

        retranslateUi(Clock);

        QMetaObject::connectSlotsByName(Clock);
    } // setupUi

    void retranslateUi(QWidget *Clock)
    {
        Clock->setWindowTitle(QApplication::translate("Clock", "Clock", 0, QApplication::UnicodeUTF8));
        timeEdit->setDisplayFormat(QApplication::translate("Clock", "hh:mm:ss", 0, QApplication::UnicodeUTF8));
        dateEdit->setDisplayFormat(QApplication::translate("Clock", "yyyy-M-d", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Clock: public Ui_Clock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOCK_H
