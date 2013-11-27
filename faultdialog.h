#ifndef FAULTDIALOG_H
#define FAULTDIALOG_H

#include <QDialog>
#include "common.h"
#include <QPainter>

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
    QToolButton* tbtn_ok;
    QToolButton* tbtn_cancel;
    QLabel* lb_title;
private:
    void paintEvent(QPaintEvent *);
    
signals:
    
public slots:
    
};

#endif // FAULTDIALOG_H
