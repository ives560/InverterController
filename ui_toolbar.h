/********************************************************************************
** Form generated from reading UI file 'toolbar.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBAR_H
#define UI_TOOLBAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include <clock.h>

QT_BEGIN_NAMESPACE

class Ui_ToolBar
{
public:
    Clock *widget_time;
    QToolButton *tBtn_power;
    QToolButton *tBtn_main;
    QToolButton *tBtn_function;

    void setupUi(QWidget *ToolBar)
    {
        if (ToolBar->objectName().isEmpty())
            ToolBar->setObjectName(QString::fromUtf8("ToolBar"));
        ToolBar->resize(800, 89);
        ToolBar->setWindowOpacity(1);
        ToolBar->setAutoFillBackground(false);
        ToolBar->setStyleSheet(QString::fromUtf8(""));
        widget_time = new Clock(ToolBar);
        widget_time->setObjectName(QString::fromUtf8("widget_time"));
        widget_time->setGeometry(QRect(660, 0, 120, 80));
        widget_time->setStyleSheet(QString::fromUtf8("background-color: rgb(131, 239, 255);"));
        tBtn_power = new QToolButton(ToolBar);
        tBtn_power->setObjectName(QString::fromUtf8("tBtn_power"));
        tBtn_power->setGeometry(QRect(40, 0, 80, 80));
        tBtn_power->setIconSize(QSize(40, 40));
        tBtn_power->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tBtn_main = new QToolButton(ToolBar);
        tBtn_main->setObjectName(QString::fromUtf8("tBtn_main"));
        tBtn_main->setGeometry(QRect(140, 0, 80, 80));
        tBtn_main->setStyleSheet(QString::fromUtf8(""));
        tBtn_main->setIconSize(QSize(50, 50));
        tBtn_main->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tBtn_function = new QToolButton(ToolBar);
        tBtn_function->setObjectName(QString::fromUtf8("tBtn_function"));
        tBtn_function->setGeometry(QRect(240, 0, 80, 80));
        tBtn_function->setStyleSheet(QString::fromUtf8("QToolButton#toolButton_3 {\n"
"	 background: transparent;\n"
"	Repeat:no-repeat;\n"
" }"));
        tBtn_function->setIconSize(QSize(50, 50));
        tBtn_function->setCheckable(false);
        tBtn_function->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        retranslateUi(ToolBar);

        QMetaObject::connectSlotsByName(ToolBar);
    } // setupUi

    void retranslateUi(QWidget *ToolBar)
    {
        ToolBar->setWindowTitle(QApplication::translate("ToolBar", "ToolBar", 0, QApplication::UnicodeUTF8));
        tBtn_power->setText(QApplication::translate("ToolBar", "\345\274\200\346\234\272/\345\205\263\346\234\272", 0, QApplication::UnicodeUTF8));
        tBtn_main->setText(QApplication::translate("ToolBar", "\344\270\273\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
        tBtn_function->setText(QApplication::translate("ToolBar", "\345\212\237\350\203\275\350\241\250", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ToolBar: public Ui_ToolBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBAR_H
