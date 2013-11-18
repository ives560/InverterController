/********************************************************************************
** Form generated from reading UI file 'setparaitem.ui'
**
** Created: Thu Oct 17 15:49:09 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPARAITEM_H
#define UI_SETPARAITEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetParaItem
{
public:
    QLineEdit *lidit_val;
    QPushButton *pbtn_OK;
    QPushButton *pbtn_cancel;

    void setupUi(QWidget *SetParaItem)
    {
        if (SetParaItem->objectName().isEmpty())
            SetParaItem->setObjectName(QString::fromUtf8("SetParaItem"));
        SetParaItem->resize(360, 100);
        lidit_val = new QLineEdit(SetParaItem);
        lidit_val->setObjectName(QString::fromUtf8("lidit_val"));
        lidit_val->setGeometry(QRect(120, 10, 120, 30));
        pbtn_OK = new QPushButton(SetParaItem);
        pbtn_OK->setObjectName(QString::fromUtf8("pbtn_OK"));
        pbtn_OK->setGeometry(QRect(20, 60, 116, 30));
        pbtn_cancel = new QPushButton(SetParaItem);
        pbtn_cancel->setObjectName(QString::fromUtf8("pbtn_cancel"));
        pbtn_cancel->setGeometry(QRect(210, 60, 116, 30));

        retranslateUi(SetParaItem);
        QObject::connect(pbtn_OK, SIGNAL(clicked()), SetParaItem, SLOT(close()));
        QObject::connect(pbtn_cancel, SIGNAL(clicked()), SetParaItem, SLOT(close()));

        QMetaObject::connectSlotsByName(SetParaItem);
    } // setupUi

    void retranslateUi(QWidget *SetParaItem)
    {
        SetParaItem->setWindowTitle(QApplication::translate("SetParaItem", "Form", 0, QApplication::UnicodeUTF8));
        pbtn_OK->setText(QApplication::translate("SetParaItem", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pbtn_cancel->setText(QApplication::translate("SetParaItem", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetParaItem: public Ui_SetParaItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPARAITEM_H
