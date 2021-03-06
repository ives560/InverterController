﻿#ifndef SUBMENU_H
#define SUBMENU_H

#include <QtGui/QWidget>
#include "ui_submenu.h"

#include "common.h"
#include "mcontroller.h"

#include "invertercontroller.h"

class SubMenu : public QWidget
{
	Q_OBJECT

public:
    SubMenu(QWidget *parent,MController* mc);
	~SubMenu();
    void setTitle(QString text,QString pathIco);
    void setWidgetChildren(QWidget *widget, bool en=false);
    void setupButton(QToolButton *button, QString text, QRect rect, QString iconPath,
                         QSize iconSize, Qt::ToolButtonStyle style);

    void setupMenuButton(QToolButton *button, QString text,QPoint point,
                         QString iconPath);

    void setupChooseButton(QToolButton *button, QString text,QPoint point,
                            QString iconPath);

public:
	Ui::SubMenuClass ui;

public:
	SubMenu* lastOne;
    InverterController* inverter;
    MController *controller;
    bool isready;

protected:
    int show_width;
    int show_height;
	
};

#endif // SUBMENU_H
