#ifndef FAULTDIALOG_H
#define FAULTDIALOG_H

#include <QDialog>
#include "ui_faultdialog.h"
#include "common.h"
#include "mcontroller.h"

class FaultDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::FaultDialog ui;
    MController *controller;
public:
    explicit FaultDialog(QWidget *parent = 0,MController* mc=0);
    void setupUi();

private:
    void setTableVal();

private:
    void paintEvent(QPaintEvent *);
    
signals:
    
public slots:
    
};

#endif // FAULTDIALOG_H
