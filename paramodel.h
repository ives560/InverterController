#ifndef PARAMODEL_H
#define PARAMODEL_H

#include "common.h"
#include <QStandardItemModel>

class ParaModel : public QStandardItemModel
{

public:
    ParaModel( QObject * parent = 0);
    ParaModel( int rows, int columns, QObject * parent = 0 );

    void initModel();
    void setValToItem(QStandardItem* item,ParaItem* para);
    void setAllValToTable();
    void setValToTable(ParaItem* para);
    void bindData(int row,int clum,ParaItem* para);
    ParaItem* getPara(QStandardItem* item);
    ParaItem* getPara(int addr);
    QStandardItem* getItem(ParaItem* para);

private:
    QList< QPair<QStandardItem*,ParaItem*> > itemlist;
};

#endif // PARAMODEL_H
