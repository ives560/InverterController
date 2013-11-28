#include "paratablewidget.h"
#include <QHeaderView>
ParaTableWidget::ParaTableWidget(QWidget *parent)
    :QTableWidget(parent)
{
    setupUi();
}

void ParaTableWidget::setupUi()
{
    this->setAlternatingRowColors(true);
    this->setStyleSheet("background:rgb(233,245,255);alternate-background-color: rgb(209,234,255);");

    this->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(86,197,255);}");
    this->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setDisabled(true);
    this->verticalHeader()->hide();//隐藏行标题列标题

    this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(86,197,255);}");
    this->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//固定行高列宽
    this->horizontalHeader()->setDisabled(true);
    this->horizontalHeader()->hide();//隐藏行标题列标题


    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条

    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);//单元格只读
}

//
void ParaTableWidget::bindData(int row,int clum,ParaInfo* para)
{
    if(para==NULL)
        return ;
    QTableWidgetItem* item=new QTableWidgetItem();
    item->setData(Qt::UserRole,para->address);
    this->setItem(row,clum,item);
    itemlist.append(qMakePair(item,para));
}

//设置已经绑定的值
void ParaTableWidget::setAllValToTable()
{
    for(int i=0;i<itemlist.count();i++)
        setValToItem(itemlist[i].first,itemlist[i].second);
}
//
void ParaTableWidget::setValToTable(ParaInfo* para)
{
    QTableWidgetItem* item=NULL;
    item=getItem(para);
    if(item==NULL)
        return;
    setValToItem(item,para);
}
//
void ParaTableWidget::setValToItem(QTableWidgetItem* item,ParaInfo* para)
{
    if((item==NULL)||(para==NULL))
        return;
    QString val_s;
    float val_f=para->values;
    val_f= val_f/para->scaling;
    val_s=QString("%1%2").arg(val_f).arg(para->unit);
    item->setData(Qt::DisplayRole,val_s);
}

ParaInfo* ParaTableWidget::getPara(QTableWidgetItem* item)
{
    for(int i=0;i<itemlist.count();i++)
    {
        if(itemlist[i].first==item)
            return itemlist[i].second;
    }
    return NULL;
}

ParaInfo* ParaTableWidget::getPara(int addr)
{
    for(int i=0;i<itemlist.count();i++)
    {
        if(itemlist[i].second->address==addr)
            return itemlist[i].second;
    }
    return NULL;
}

QTableWidgetItem* ParaTableWidget::getItem(ParaInfo* para)
{
    for(int i=0;i<itemlist.count();i++)
    {
        if(itemlist[i].second==para)
            return itemlist[i].first;
    }
    return NULL;
}

//串口数据读取
/*void ParaTableWidget::readDoneSlot()
{
    qDebug()<<"readDoneSlot";
    setAllValToTable();
}

void ParaTableWidget::writeDoneSlot(ParaList list,bool succeed)
{
    if(succeed==true)
    {
        for(int i=0;i<list.count();i++)
        {
            list[i]->values = list[i]->val_w;
            setValToTable(list[i]);
        }
    }
    else
    {
        qDebug()<<"writeError";
        QMessageBox* msgBox=new QMessageBox(this);
        QString str;
        for(int i=0;i<list.count();i++)
        {
            str +=QString("写地址%1值%2失败！\n").arg(list[i]->address).arg(list[i]->val_w);
        }
        msgBox->setText(str);
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setStandardButtons( QMessageBox::Ok);
        msgBox->show();
    }
}*/

