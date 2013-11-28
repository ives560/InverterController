#ifndef MAINFACE_H
#define MAINFACE_H

#include <QWidget>
#include "ui_mainface.h"
#include "common.h"
#include "mcontroller.h"

class MainFace : public QWidget
{
	Q_OBJECT

public:
    MainFace(QWidget *parent ,MController *mc);
	~MainFace();

private:
	Ui::MainFace ui;
    QList< QPair<QLabel*,ParaItem*> > labelist;
    MController* controller;
    ParaItem* paraMain[];

private:
    void chartInit();
    void tableInit();
    void labelMapInit();
    void labelDataBinding();
    void labelUpData();
    void tableUpData();
    void chartUpData();
    void setReadType(int type,bool en);

    void paintEvent(QPaintEvent *);

public slots:
    void upDataPara();
    void readFastDataDoneSlot();
    void tableWidget_clicked(QModelIndex);

};

#endif // MAINFACE_H
