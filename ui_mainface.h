/********************************************************************************
** Form generated from reading UI file 'mainface.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFACE_H
#define UI_MAINFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>
#include <chart.h>

QT_BEGIN_NAMESPACE

class Ui_MainFace
{
public:
    Chart *chart_power;
    QLabel *lab_vb;
    QLabel *lab_ipv;
    QLabel *lab_ib;
    QLabel *lab_vc;
    QLabel *lab_vpv;
    QLabel *lab_va;
    QLabel *lab_ic;
    QLabel *lab_ia;
    QTableWidget *tableWidget;

    void setupUi(QWidget *MainFace)
    {
        if (MainFace->objectName().isEmpty())
            MainFace->setObjectName(QString::fromUtf8("MainFace"));
        MainFace->resize(800, 400);
        QFont font;
        font.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font.setPointSize(9);
        MainFace->setFont(font);
        MainFace->setStyleSheet(QString::fromUtf8("#MainFace{border-image:url(:/images/mainpic.png);}"));
        chart_power = new Chart(MainFace);
        chart_power->setObjectName(QString::fromUtf8("chart_power"));
        chart_power->setGeometry(QRect(300, 20, 500, 200));
        lab_vb = new QLabel(MainFace);
        lab_vb->setObjectName(QString::fromUtf8("lab_vb"));
        lab_vb->setGeometry(QRect(394, 286, 80, 25));
        QFont font1;
        font1.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font1.setPointSize(12);
        lab_vb->setFont(font1);
        lab_ipv = new QLabel(MainFace);
        lab_ipv->setObjectName(QString::fromUtf8("lab_ipv"));
        lab_ipv->setGeometry(QRect(190, 280, 80, 25));
        lab_ipv->setFont(font1);
        lab_ib = new QLabel(MainFace);
        lab_ib->setObjectName(QString::fromUtf8("lab_ib"));
        lab_ib->setGeometry(QRect(484, 286, 80, 25));
        lab_ib->setFont(font1);
        lab_vc = new QLabel(MainFace);
        lab_vc->setObjectName(QString::fromUtf8("lab_vc"));
        lab_vc->setGeometry(QRect(394, 318, 80, 25));
        lab_vc->setFont(font1);
        lab_vpv = new QLabel(MainFace);
        lab_vpv->setObjectName(QString::fromUtf8("lab_vpv"));
        lab_vpv->setGeometry(QRect(190, 320, 80, 25));
        lab_vpv->setFont(font1);
        lab_va = new QLabel(MainFace);
        lab_va->setObjectName(QString::fromUtf8("lab_va"));
        lab_va->setGeometry(QRect(394, 257, 80, 25));
        lab_va->setFont(font1);
        lab_ic = new QLabel(MainFace);
        lab_ic->setObjectName(QString::fromUtf8("lab_ic"));
        lab_ic->setGeometry(QRect(484, 318, 80, 25));
        lab_ic->setFont(font1);
        lab_ia = new QLabel(MainFace);
        lab_ia->setObjectName(QString::fromUtf8("lab_ia"));
        lab_ia->setGeometry(QRect(484, 257, 80, 25));
        lab_ia->setFont(font1);
        tableWidget = new QTableWidget(MainFace);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 31, 251, 161));

        retranslateUi(MainFace);

        QMetaObject::connectSlotsByName(MainFace);
    } // setupUi

    void retranslateUi(QWidget *MainFace)
    {
        MainFace->setWindowTitle(QApplication::translate("MainFace", "MainFace", 0, QApplication::UnicodeUTF8));
        lab_vb->setText(QApplication::translate("MainFace", "TextLabel", 0, QApplication::UnicodeUTF8));
        lab_ipv->setText(QApplication::translate("MainFace", "TextLabel", 0, QApplication::UnicodeUTF8));
        lab_ib->setText(QApplication::translate("MainFace", "TextLabel", 0, QApplication::UnicodeUTF8));
        lab_vc->setText(QApplication::translate("MainFace", "TextLabel", 0, QApplication::UnicodeUTF8));
        lab_vpv->setText(QApplication::translate("MainFace", "TextLabel", 0, QApplication::UnicodeUTF8));
        lab_va->setText(QApplication::translate("MainFace", "TextLabel", 0, QApplication::UnicodeUTF8));
        lab_ic->setText(QApplication::translate("MainFace", "TextLabel", 0, QApplication::UnicodeUTF8));
        lab_ia->setText(QApplication::translate("MainFace", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainFace: public Ui_MainFace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFACE_H
