/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created: Mon Nov 18 12:20:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyBoard
{
public:
    QPushButton *pushButton_4;
    QPushButton *pushButton_enter;
    QPushButton *pushButton_6;
    QPushButton *pushButton_esc;
    QPushButton *pushButton_1;
    QPushButton *pushButton_7;
    QPushButton *pushButton_0;
    QPushButton *pushButton_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_line;
    QPushButton *pushButton_dot;
    QPushButton *pushButton_3;
    QPushButton *pushButton_9;
    QPushButton *pushButton_5;
    QPushButton *pushButton_ce;

    void setupUi(QWidget *KeyBoard)
    {
        if (KeyBoard->objectName().isEmpty())
            KeyBoard->setObjectName(QString::fromUtf8("KeyBoard"));
        KeyBoard->resize(249, 178);
        KeyBoard->setFocusPolicy(Qt::NoFocus);
        KeyBoard->setStyleSheet(QString::fromUtf8("QWidget#KeyBoard{background:rgb(85, 85, 255)}"));
        pushButton_4 = new QPushButton(KeyBoard);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 50, 50, 30));
        pushButton_4->setFocusPolicy(Qt::NoFocus);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_enter = new QPushButton(KeyBoard);
        pushButton_enter->setObjectName(QString::fromUtf8("pushButton_enter"));
        pushButton_enter->setGeometry(QRect(130, 134, 110, 30));
        pushButton_enter->setFocusPolicy(Qt::NoFocus);
        pushButton_enter->setStyleSheet(QString::fromUtf8("background: rgb(255, 255, 255);"));
        pushButton_6 = new QPushButton(KeyBoard);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(130, 50, 50, 30));
        pushButton_6->setFocusPolicy(Qt::NoFocus);
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_esc = new QPushButton(KeyBoard);
        pushButton_esc->setObjectName(QString::fromUtf8("pushButton_esc"));
        pushButton_esc->setGeometry(QRect(190, 92, 50, 30));
        pushButton_esc->setFocusPolicy(Qt::NoFocus);
        pushButton_esc->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_1 = new QPushButton(KeyBoard);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        pushButton_1->setGeometry(QRect(10, 92, 50, 30));
        pushButton_1->setFocusPolicy(Qt::NoFocus);
        pushButton_1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_7 = new QPushButton(KeyBoard);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(10, 8, 50, 30));
        pushButton_7->setFocusPolicy(Qt::NoFocus);
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_7->setIconSize(QSize(16, 16));
        pushButton_0 = new QPushButton(KeyBoard);
        pushButton_0->setObjectName(QString::fromUtf8("pushButton_0"));
        pushButton_0->setGeometry(QRect(70, 134, 50, 30));
        pushButton_0->setFocusPolicy(Qt::NoFocus);
        pushButton_0->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_2 = new QPushButton(KeyBoard);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(70, 92, 50, 30));
        pushButton_2->setFocusPolicy(Qt::NoFocus);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_8 = new QPushButton(KeyBoard);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(70, 8, 50, 30));
        pushButton_8->setFocusPolicy(Qt::NoFocus);
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_line = new QPushButton(KeyBoard);
        pushButton_line->setObjectName(QString::fromUtf8("pushButton_line"));
        pushButton_line->setGeometry(QRect(190, 8, 50, 30));
        pushButton_line->setFocusPolicy(Qt::NoFocus);
        pushButton_line->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_dot = new QPushButton(KeyBoard);
        pushButton_dot->setObjectName(QString::fromUtf8("pushButton_dot"));
        pushButton_dot->setGeometry(QRect(10, 134, 50, 30));
        pushButton_dot->setFocusPolicy(Qt::NoFocus);
        pushButton_dot->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_3 = new QPushButton(KeyBoard);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(130, 92, 50, 30));
        pushButton_3->setFocusPolicy(Qt::NoFocus);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_9 = new QPushButton(KeyBoard);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(130, 8, 50, 30));
        pushButton_9->setFocusPolicy(Qt::NoFocus);
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_5 = new QPushButton(KeyBoard);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(70, 50, 50, 30));
        pushButton_5->setFocusPolicy(Qt::NoFocus);
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_ce = new QPushButton(KeyBoard);
        pushButton_ce->setObjectName(QString::fromUtf8("pushButton_ce"));
        pushButton_ce->setGeometry(QRect(190, 50, 50, 30));
        pushButton_ce->setFocusPolicy(Qt::NoFocus);
        pushButton_ce->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(KeyBoard);

        QMetaObject::connectSlotsByName(KeyBoard);
    } // setupUi

    void retranslateUi(QWidget *KeyBoard)
    {
        KeyBoard->setWindowTitle(QApplication::translate("KeyBoard", "KeyBoard", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("KeyBoard", "4", 0, QApplication::UnicodeUTF8));
        pushButton_enter->setText(QApplication::translate("KeyBoard", "ENTER", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("KeyBoard", "6", 0, QApplication::UnicodeUTF8));
        pushButton_esc->setText(QApplication::translate("KeyBoard", "ESC", 0, QApplication::UnicodeUTF8));
        pushButton_1->setText(QApplication::translate("KeyBoard", "1", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("KeyBoard", "7", 0, QApplication::UnicodeUTF8));
        pushButton_0->setText(QApplication::translate("KeyBoard", "0", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("KeyBoard", "2", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("KeyBoard", "8", 0, QApplication::UnicodeUTF8));
        pushButton_line->setText(QApplication::translate("KeyBoard", "-", 0, QApplication::UnicodeUTF8));
        pushButton_dot->setText(QApplication::translate("KeyBoard", ".", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("KeyBoard", "3", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("KeyBoard", "9", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("KeyBoard", "5", 0, QApplication::UnicodeUTF8));
        pushButton_ce->setText(QApplication::translate("KeyBoard", "CE", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KeyBoard: public Ui_KeyBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
