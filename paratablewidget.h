#ifndef PARATABLEWIDGET_H
#define PARATABLEWIDGET_H

#include <QTableWidget>

#include "common.h"

class ParaTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    ParaTableWidget(QWidget *parent=0);
    void setupUi();
    void setValToItem(QTableWidgetItem* item,ParaItem* para);
    void setAllValToTable();
    void setValToTable(ParaItem* para);
    void bindData(int row,int clum,ParaItem* para);
    ParaItem* getPara(QTableWidgetItem* item);
    ParaItem* getPara(int addr);
    QTableWidgetItem* getItem(ParaItem* para);
private:
    QList< QPair<QTableWidgetItem*,ParaItem*> > itemlist;

//private slots:
//    void readDoneSlot();
//    void writeDoneSlot(ParaList list,bool succeed);
};

#endif // PARATABLEWIDGET_H
