/********************************************************************************
** Form generated from reading UI file 'setparadialog.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETPARADIALOG_H
#define UI_SETPARADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetParaDialog
{
public:
    QPushButton *pbtn_OK;
    QPushButton *pbtn_cancel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_name;
    QLineEdit *lineEdit;
    QLabel *label_unit;

    void setupUi(QDialog *SetParaDialog)
    {
        if (SetParaDialog->objectName().isEmpty())
            SetParaDialog->setObjectName(QString::fromUtf8("SetParaDialog"));
        SetParaDialog->resize(300, 100);
        pbtn_OK = new QPushButton(SetParaDialog);
        pbtn_OK->setObjectName(QString::fromUtf8("pbtn_OK"));
        pbtn_OK->setGeometry(QRect(10, 60, 116, 30));
        pbtn_cancel = new QPushButton(SetParaDialog);
        pbtn_cancel->setObjectName(QString::fromUtf8("pbtn_cancel"));
        pbtn_cancel->setGeometry(QRect(180, 60, 116, 30));
        horizontalLayoutWidget = new QWidget(SetParaDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 0, 261, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_name = new QLabel(horizontalLayoutWidget);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setLayoutDirection(Qt::LeftToRight);
        label_name->setFrameShape(QFrame::NoFrame);
        label_name->setTextFormat(Qt::AutoText);
        label_name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_name);

        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        label_unit = new QLabel(horizontalLayoutWidget);
        label_unit->setObjectName(QString::fromUtf8("label_unit"));

        horizontalLayout->addWidget(label_unit);


        retranslateUi(SetParaDialog);

        QMetaObject::connectSlotsByName(SetParaDialog);
    } // setupUi

    void retranslateUi(QDialog *SetParaDialog)
    {
        SetParaDialog->setWindowTitle(QApplication::translate("SetParaDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pbtn_OK->setText(QApplication::translate("SetParaDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pbtn_cancel->setText(QApplication::translate("SetParaDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_name->setText(QApplication::translate("SetParaDialog", "name", 0, QApplication::UnicodeUTF8));
        label_unit->setText(QApplication::translate("SetParaDialog", "unit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetParaDialog: public Ui_SetParaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETPARADIALOG_H
