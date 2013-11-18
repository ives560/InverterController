/********************************************************************************
** Form generated from reading UI file 'chart.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHART_H
#define UI_CHART_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chart
{
public:

    void setupUi(QWidget *Chart)
    {
        if (Chart->objectName().isEmpty())
            Chart->setObjectName(QString::fromUtf8("Chart"));
        Chart->resize(400, 300);

        retranslateUi(Chart);

        QMetaObject::connectSlotsByName(Chart);
    } // setupUi

    void retranslateUi(QWidget *Chart)
    {
        Chart->setWindowTitle(QApplication::translate("Chart", "Chart", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Chart: public Ui_Chart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHART_H
