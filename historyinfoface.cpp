#include "historyinfoface.h"
#include "invertercontroller.h"
#include "historydata.h"
#include "historyfault.h"
HistoryInfoFace::HistoryInfoFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    setupUi();
}

void HistoryInfoFace::setupUi()
{
    setTitle("历史记录",":/images/hostorybig.png");

    /*------------------*/
//    QToolButton *tbtn_event=new QToolButton(ui.showArea);
//    tbtn_event->setObjectName("tbtn_event");
//    connect(tbtn_event,SIGNAL(clicked()),this,SLOT(tbtn_event_Clicked()));
//    setupMenuButton(tbtn_event,"历史事件",QPoint(300,80),":/images/event.png");
    /*------------------*/
    QToolButton *tbtn_fault=new QToolButton(ui.showArea);
    tbtn_fault->setObjectName("tbtn_fault");
    connect(tbtn_fault,SIGNAL(clicked()),this,SLOT(tbtn_fault_Clicked()));
    setupMenuButton(tbtn_fault,"故障追踪",QPoint(400,80),":/images/guzhangzhuizhong.png");
    /*------------------*/
    QToolButton *tbtn_data=new QToolButton(ui.showArea);
    tbtn_data->setObjectName("tbtn_data");
    connect(tbtn_data,SIGNAL(clicked()),this,SLOT(tbtn_data_Clicked()));
    setupMenuButton(tbtn_data,"历史记录",QPoint(300,180),":/images/hostorybig.png");
}
//
void HistoryInfoFace::tbtn_event_Clicked()
{
    qDebug()<<"tbtn_event_Clickde";
}
//
void HistoryInfoFace::tbtn_fault_Clicked()
{
    qDebug()<<"tbtn_fault_Clickde";
    HistoryFault* faultWidget = new HistoryFault((QWidget*)inverter,controller);
    faultWidget->lastOne = this;
    inverter->addTopInterface(faultWidget);
}
//
void HistoryInfoFace::tbtn_data_Clicked()
{
    qDebug()<<"tbtn_data_Clickde";
    HistoryData* dataWidget=new HistoryData((QWidget*)inverter,controller);
    dataWidget->lastOne=this;
    inverter->addTopInterface(dataWidget);
}
