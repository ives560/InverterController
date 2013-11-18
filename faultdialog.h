#ifndef FAULTDIALOG_H
#define FAULTDIALOG_H

#include <QDialog>
#include "common.h"

class FaultDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FaultDialog(QWidget *parent = 0);
    void setupUi();
    void tableInit();

private:
    QList<QString> getFaultNames();
    void setTableVal();
private:
    QTableWidget* tableWidget;
    QPushButton* pbtn_ok;
    QLabel* lab_fault;
    
signals:
    
public slots:
    
};

#endif // FAULTDIALOG_H
