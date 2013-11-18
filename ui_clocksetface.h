/********************************************************************************
** Form generated from reading UI file 'clocksetface.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCKSETFACE_H
#define UI_CLOCKSETFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClockSetFace
{
public:
    QWidget *widget;
    QLineEdit *ldt_s;
    QLineEdit *ldt_tm;
    QLineEdit *ldt_h;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QLabel *lb_date;
    QLineEdit *ldt_y;
    QLineEdit *ldt_d;
    QLabel *label_5;
    QLineEdit *ldt_m;
    QLabel *label_4;
    QToolButton *tbtn_ok;
    QToolButton *tbtn_cancel;

    void setupUi(QWidget *ClockSetFace)
    {
        if (ClockSetFace->objectName().isEmpty())
            ClockSetFace->setObjectName(QString::fromUtf8("ClockSetFace"));
        ClockSetFace->resize(800, 320);
        QFont font;
        font.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font.setPointSize(16);
        ClockSetFace->setFont(font);
        ClockSetFace->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        widget = new QWidget(ClockSetFace);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(250, 50, 300, 150));
        QFont font1;
        font1.setFamily(QString::fromUtf8("AR PL UKai CN"));
        font1.setPointSize(10);
        widget->setFont(font1);
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        ldt_s = new QLineEdit(widget);
        ldt_s->setObjectName(QString::fromUtf8("ldt_s"));
        ldt_s->setGeometry(QRect(230, 100, 52, 34));
        ldt_s->setFont(font1);
        ldt_s->setMaxLength(2);
        ldt_s->setAlignment(Qt::AlignCenter);
        ldt_tm = new QLineEdit(widget);
        ldt_tm->setObjectName(QString::fromUtf8("ldt_tm"));
        ldt_tm->setGeometry(QRect(155, 100, 53, 34));
        ldt_tm->setFont(font1);
        ldt_tm->setMaxLength(2);
        ldt_tm->setAlignment(Qt::AlignCenter);
        ldt_h = new QLineEdit(widget);
        ldt_h->setObjectName(QString::fromUtf8("ldt_h"));
        ldt_h->setGeometry(QRect(81, 100, 52, 34));
        ldt_h->setFont(font1);
        ldt_h->setMaxLength(2);
        ldt_h->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(214, 93, 10, 49));
        label_3->setFont(font1);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(139, 93, 10, 49));
        label_2->setFont(font1);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(23, 93, 52, 49));
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font-color:rgb(0, 0, 255)"));
        lb_date = new QLabel(widget);
        lb_date->setObjectName(QString::fromUtf8("lb_date"));
        lb_date->setGeometry(QRect(10, 10, 52, 49));
        lb_date->setFont(font1);
        lb_date->setStyleSheet(QString::fromUtf8("font-color:rgb(0, 0, 255)"));
        ldt_y = new QLineEdit(widget);
        ldt_y->setObjectName(QString::fromUtf8("ldt_y"));
        ldt_y->setGeometry(QRect(68, 17, 58, 34));
        ldt_y->setFont(font1);
        ldt_y->setMaxLength(4);
        ldt_y->setAlignment(Qt::AlignCenter);
        ldt_d = new QLineEdit(widget);
        ldt_d->setObjectName(QString::fromUtf8("ldt_d"));
        ldt_d->setGeometry(QRect(231, 17, 58, 34));
        ldt_d->setFont(font1);
        ldt_d->setMaxLength(2);
        ldt_d->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(213, 10, 12, 49));
        label_5->setFont(font1);
        ldt_m = new QLineEdit(widget);
        ldt_m->setObjectName(QString::fromUtf8("ldt_m"));
        ldt_m->setGeometry(QRect(150, 17, 57, 34));
        ldt_m->setFont(font1);
        ldt_m->setMaxLength(2);
        ldt_m->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(132, 10, 12, 49));
        label_4->setFont(font1);
        tbtn_ok = new QToolButton(ClockSetFace);
        tbtn_ok->setObjectName(QString::fromUtf8("tbtn_ok"));
        tbtn_ok->setGeometry(QRect(280, 260, 100, 35));
        tbtn_ok->setStyleSheet(QString::fromUtf8("background: transparent;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/shangyiye.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_ok->setIcon(icon);
        tbtn_ok->setIconSize(QSize(32, 32));
        tbtn_ok->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        tbtn_cancel = new QToolButton(ClockSetFace);
        tbtn_cancel->setObjectName(QString::fromUtf8("tbtn_cancel"));
        tbtn_cancel->setGeometry(QRect(440, 260, 100, 35));
        tbtn_cancel->setStyleSheet(QString::fromUtf8("background: transparent;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/xiayiye.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_cancel->setIcon(icon1);
        tbtn_cancel->setIconSize(QSize(32, 32));
        tbtn_cancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        tbtn_cancel->setArrowType(Qt::NoArrow);

        retranslateUi(ClockSetFace);

        QMetaObject::connectSlotsByName(ClockSetFace);
    } // setupUi

    void retranslateUi(QWidget *ClockSetFace)
    {
        ClockSetFace->setWindowTitle(QApplication::translate("ClockSetFace", "Form", 0, QApplication::UnicodeUTF8));
        ldt_s->setText(QApplication::translate("ClockSetFace", "24", 0, QApplication::UnicodeUTF8));
        ldt_tm->setText(QApplication::translate("ClockSetFace", "24", 0, QApplication::UnicodeUTF8));
        ldt_h->setText(QApplication::translate("ClockSetFace", "24", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ClockSetFace", ":", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ClockSetFace", ":", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ClockSetFace", "\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        lb_date->setText(QApplication::translate("ClockSetFace", "\346\227\245\346\234\237:", 0, QApplication::UnicodeUTF8));
        ldt_y->setText(QApplication::translate("ClockSetFace", "2013", 0, QApplication::UnicodeUTF8));
        ldt_d->setText(QApplication::translate("ClockSetFace", "20", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ClockSetFace", "/", 0, QApplication::UnicodeUTF8));
        ldt_m->setText(QApplication::translate("ClockSetFace", "10", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ClockSetFace", "/", 0, QApplication::UnicodeUTF8));
        tbtn_ok->setText(QApplication::translate("ClockSetFace", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        tbtn_cancel->setText(QApplication::translate("ClockSetFace", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClockSetFace: public Ui_ClockSetFace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOCKSETFACE_H
