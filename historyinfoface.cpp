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
    ui_history.setupUi(ui.showArea);
    //connect(ui_history.event,SIGNAL(clicked()),this,SLOT(tbtn_event_Clicked()));
    connect(ui_history.fault,SIGNAL(clicked()),this,SLOT(tbtn_fault_Clicked()));
    connect(ui_history.record,SIGNAL(clicked()),this,SLOT(tbtn_record_Clicked()));
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
void HistoryInfoFace::tbtn_record_Clicked()
{
    qDebug()<<"tbtn_data_Clickde";
    HistoryData* dataWidget=new HistoryData((QWidget*)inverter,controller);
    dataWidget->lastOne=this;
    inverter->addTopInterface(dataWidget);
}
