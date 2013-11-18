/********************************************************************************
** Form generated from reading UI file 'invertercontroller.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVERTERCONTROLLER_H
#define UI_INVERTERCONTROLLER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <clock.h>

QT_BEGIN_NAMESPACE

class Ui_InverterControllerClass
{
public:
    QWidget *widget;
    QToolButton *tBtn_main;
    Clock *widget_time;
    QToolButton *tBtn_function;
    QToolButton *tBtn_power;
    QWidget *widget_layout;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *InverterControllerClass)
    {
        if (InverterControllerClass->objectName().isEmpty())
            InverterControllerClass->setObjectName(QString::fromUtf8("InverterControllerClass"));
        InverterControllerClass->resize(800, 480);
        QFont font;
        font.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font.setPointSize(10);
        InverterControllerClass->setFont(font);
        InverterControllerClass->setContextMenuPolicy(Qt::CustomContextMenu);
        InverterControllerClass->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(InverterControllerClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 400, 800, 80));
        widget->setFont(font);
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(58, 163, 255, 255), stop:0.495 rgba(58, 163, 255, 255), stop:0.505 rgba(17, 60, 255, 255), stop:1 rgba(17, 60, 255, 255));}"));
        tBtn_main = new QToolButton(widget);
        tBtn_main->setObjectName(QString::fromUtf8("tBtn_main"));
        tBtn_main->setGeometry(QRect(120, 0, 80, 80));
        QFont font1;
        font1.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        tBtn_main->setFont(font1);
        tBtn_main->setFocusPolicy(Qt::StrongFocus);
        tBtn_main->setStyleSheet(QString::fromUtf8("background: transparent;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/zhuyemian.png"), QSize(), QIcon::Normal, QIcon::Off);
        tBtn_main->setIcon(icon);
        tBtn_main->setIconSize(QSize(60, 60));
        tBtn_main->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        widget_time = new Clock(widget);
        widget_time->setObjectName(QString::fromUtf8("widget_time"));
        widget_time->setGeometry(QRect(700, 40, 100, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font2.setPointSize(9);
        widget_time->setFont(font2);
        widget_time->setStyleSheet(QString::fromUtf8("background-color: rgb(131, 239, 255);"));
        tBtn_function = new QToolButton(widget);
        tBtn_function->setObjectName(QString::fromUtf8("tBtn_function"));
        tBtn_function->setGeometry(QRect(220, 0, 80, 80));
        tBtn_function->setFont(font1);
        tBtn_function->setFocusPolicy(Qt::StrongFocus);
        tBtn_function->setStyleSheet(QString::fromUtf8("background: transparent;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/gongnengbiao.png"), QSize(), QIcon::Normal, QIcon::Off);
        tBtn_function->setIcon(icon1);
        tBtn_function->setIconSize(QSize(60, 60));
        tBtn_function->setCheckable(false);
        tBtn_function->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tBtn_power = new QToolButton(widget);
        tBtn_power->setObjectName(QString::fromUtf8("tBtn_power"));
        tBtn_power->setGeometry(QRect(20, 0, 80, 80));
        tBtn_power->setFont(font1);
        tBtn_power->setFocusPolicy(Qt::StrongFocus);
        tBtn_power->setStyleSheet(QString::fromUtf8("background: transparent;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/kaiguanji.png"), QSize(), QIcon::Normal, QIcon::Off);
        tBtn_power->setIcon(icon2);
        tBtn_power->setIconSize(QSize(50, 50));
        tBtn_power->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        widget_layout = new QWidget(InverterControllerClass);
        widget_layout->setObjectName(QString::fromUtf8("widget_layout"));
        widget_layout->setGeometry(QRect(0, 0, 800, 400));
        widget_layout->setStyleSheet(QString::fromUtf8("#widget_layout{background-color: rgb(0, 85, 255);}"));
        verticalLayoutWidget = new QWidget(widget_layout);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 801, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(InverterControllerClass);

        QMetaObject::connectSlotsByName(InverterControllerClass);
    } // setupUi

    void retranslateUi(QWidget *InverterControllerClass)
    {
        InverterControllerClass->setWindowTitle(QApplication::translate("InverterControllerClass", "InverterController", 0, QApplication::UnicodeUTF8));
        tBtn_main->setText(QApplication::translate("InverterControllerClass", "\344\270\273\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
        tBtn_function->setText(QApplication::translate("InverterControllerClass", "\345\212\237\350\203\275\350\241\250", 0, QApplication::UnicodeUTF8));
        tBtn_power->setText(QApplication::translate("InverterControllerClass", "\345\274\200\346\234\272/\345\205\263\346\234\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InverterControllerClass: public Ui_InverterControllerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVERTERCONTROLLER_H
