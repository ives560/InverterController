/********************************************************************************
** Form generated from reading UI file 'historydata.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYDATA_H
#define UI_HISTORYDATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <chart.h>

QT_BEGIN_NAMESPACE

class Ui_HistoryData
{
public:
    Chart *chart;
    QLabel *label;
    QComboBox *cbox_para;
    QLabel *label_2;
    QComboBox *cbox_data;

    void setupUi(QWidget *HistoryData)
    {
        if (HistoryData->objectName().isEmpty())
            HistoryData->setObjectName(QString::fromUtf8("HistoryData"));
        HistoryData->resize(800, 320);
        chart = new Chart(HistoryData);
        chart->setObjectName(QString::fromUtf8("chart"));
        chart->setGeometry(QRect(30, 80, 711, 200));
        label = new QLabel(HistoryData);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 20, 63, 38));
        QFont font;
        font.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font.setPointSize(10);
        label->setFont(font);
        cbox_para = new QComboBox(HistoryData);
        cbox_para->setObjectName(QString::fromUtf8("cbox_para"));
        cbox_para->setGeometry(QRect(297, 20, 103, 38));
        cbox_para->setFont(font);
        label_2 = new QLabel(HistoryData);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(228, 20, 63, 38));
        label_2->setFont(font);
        cbox_data = new QComboBox(HistoryData);
        cbox_data->setObjectName(QString::fromUtf8("cbox_data"));
        cbox_data->setGeometry(QRect(119, 20, 103, 38));
        cbox_data->setFont(font);

        retranslateUi(HistoryData);

        QMetaObject::connectSlotsByName(HistoryData);
    } // setupUi

    void retranslateUi(QWidget *HistoryData)
    {
        HistoryData->setWindowTitle(QApplication::translate("HistoryData", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("HistoryData", "\346\227\245\346\234\237\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("HistoryData", "\345\217\202\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HistoryData: public Ui_HistoryData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYDATA_H
