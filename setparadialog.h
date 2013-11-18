#ifndef SETPARADIALOG_H
#define SETPARADIALOG_H

#include <QDialog>
#include "common.h"
#include "mcontroller.h"
namespace Ui {
class SetParaDialog;
}

class SetParaDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetParaDialog(QWidget *parent,MController* mc);
    ~SetParaDialog();
    void getPara(QString name,ParaInfo* p);


private:
    Ui::SetParaDialog *ui;
    ParaInfo* para;
    MController *controller;

private slots:
    void pbtn_OK_clicked();
};

#endif // SETPARADIALOG_H
