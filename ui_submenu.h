/********************************************************************************
** Form generated from reading UI file 'submenu.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBMENU_H
#define UI_SUBMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <clock.h>

QT_BEGIN_NAMESPACE

class Ui_SubMenuClass
{
public:
    QWidget *widget_title;
    QLabel *label_icon;
    Clock *widget;
    QLabel *label_title;
    QLabel *label;
    QWidget *showArea;

    void setupUi(QWidget *SubMenuClass)
    {
        if (SubMenuClass->objectName().isEmpty())
            SubMenuClass->setObjectName(QString::fromUtf8("SubMenuClass"));
        SubMenuClass->resize(800, 400);
        widget_title = new QWidget(SubMenuClass);
        widget_title->setObjectName(QString::fromUtf8("widget_title"));
        widget_title->setGeometry(QRect(0, 30, 800, 50));
        widget_title->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 255);"));
        label_icon = new QLabel(widget_title);
        label_icon->setObjectName(QString::fromUtf8("label_icon"));
        label_icon->setGeometry(QRect(0, 0, 50, 50));
        label_icon->setTextFormat(Qt::AutoText);
        label_icon->setScaledContents(true);
        widget = new Clock(widget_title);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(700, 5, 100, 40));
        label_title = new QLabel(widget_title);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setGeometry(QRect(150, 10, 181, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font.setPointSize(14);
        label_title->setFont(font);
        label = new QLabel(SubMenuClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 99, 25));
        showArea = new QWidget(SubMenuClass);
        showArea->setObjectName(QString::fromUtf8("showArea"));
        showArea->setGeometry(QRect(0, 80, 800, 320));

        retranslateUi(SubMenuClass);

        QMetaObject::connectSlotsByName(SubMenuClass);
    } // setupUi

    void retranslateUi(QWidget *SubMenuClass)
    {
        SubMenuClass->setWindowTitle(QApplication::translate("SubMenuClass", "Form", 0, QApplication::UnicodeUTF8));
        label_icon->setText(QString());
        label_title->setText(QApplication::translate("SubMenuClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SubMenuClass", "\344\270\262\345\217\243\351\200\232\350\256\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SubMenuClass: public Ui_SubMenuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBMENU_H
