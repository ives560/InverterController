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
    void setValToItem(QTableWidgetItem* item,ParaInfo* para);
    void setAllValToTable();
    void setValToTable(ParaInfo* para);
    void bindData(int row,int clum,ParaInfo* para);
    ParaInfo* getPara(QTableWidgetItem* item);
    ParaInfo* getPara(int addr);
    QTableWidgetItem* getItem(ParaInfo* para);
private:
    QList< QPair<QTableWidgetItem*,ParaInfo*> > itemlist;

//private slots:
//    void readDoneSlot();
//    void writeDoneSlot(ParaList list,bool succeed);
};

#endif // PARATABLEWIDGET_H
