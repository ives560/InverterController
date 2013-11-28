#include "paramodel.h"

ParaModel::ParaModel(QObject *parent):
    QStandardItemModel(parent)
{


}

ParaModel::ParaModel( int rows, int columns, QObject * parent):
    QStandardItemModel(rows,columns,parent)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            this->setItem(i,j,new QStandardItem());
        }
    }
}

void ParaModel::initModel()
{

}
void ParaModel::bindData(int row,int clum,ParaItem *para)
{
    if(para==NULL)
        return ;
    QStandardItem* item=new QStandardItem();
    item->setData(Qt::UserRole,para->address);
    this->setItem(row,clum,item);
    itemlist.append(qMakePair(item,para));
}

//设置已经绑定的值
void ParaModel::setAllValToTable()
{
    for(int i=0;i<itemlist.count();i++)
        setValToItem(itemlist[i].first,itemlist[i].second);
}
//
void ParaModel::setValToTable(ParaItem *para)
{
    QStandardItem* item=NULL;
    item=getItem(para);
    if(item==NULL)
        return;
    setValToItem(item,para);
}
//
void ParaModel::setValToItem(QStandardItem* item,ParaItem* para)
{
    if((item==NULL)||(para==NULL))
        return;
    QString val_s;
    float val_f=para->values;
    val_f= val_f/para->scaling;
    val_s=QString("%1%2").arg(val_f).arg(para->unit);
    item->setText(val_s);
    //item->setData(Qt::DisplayRole,val_s);
}

ParaItem *ParaModel::getPara(QStandardItem* item)
{
    for(int i=0;i<itemlist.count();i++)
    {
        if(itemlist[i].first==item)
            return itemlist[i].second;
    }
    return NULL;
}

ParaItem *ParaModel::getPara(int addr)
{
    for(int i=0;i<itemlist.count();i++)
    {
        if(itemlist[i].second->address==addr)
            return itemlist[i].second;
    }
    return NULL;
}

QStandardItem* ParaModel::getItem(ParaItem *para)
{
    for(int i=0;i<itemlist.count();i++)
    {
        if(itemlist[i].second==para)
            return itemlist[i].first;
    }
    return NULL;
}
