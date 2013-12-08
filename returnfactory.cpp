#include "returnfactory.h"
#include "msgbox.h"
ReturnFactory::ReturnFactory(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    ui_rtfty.setupUi(ui.showArea);
    connect(ui_rtfty.tbtn_fault,SIGNAL(clicked()),this,SLOT(tbtn_fault_clicked()));
    connect(ui_rtfty.tbtn_power,SIGNAL(clicked()),this,SLOT(tbtn_power_clicked()));
    connect(ui_rtfty.tbtn_run,SIGNAL(clicked()),this,SLOT(tbtn_run_clicked()));

}


void  ReturnFactory::tbtn_fault_clicked()
{
    qDebug()<<"tbtn_fault_clicked";
    MsgBox msg(this,MsgBox::Question,"是否清空故障表?");
    if(msg.exec()==MsgBox::Ok)
    {
        controller->userWriteData(PARA::Clear_cmd,3);
    }
}

void ReturnFactory::tbtn_power_clicked()
{
    qDebug()<<"tbtn_power_clicked";
    MsgBox msg(this,MsgBox::Question,"是否清空发电量?");
    if(msg.exec()==MsgBox::Ok)
    {
        controller->userWriteData(PARA::Clear_cmd,2);
    }
}

void ReturnFactory::tbtn_run_clicked()
{
    qDebug()<<"tbtn_run_clicked";
    MsgBox msg(this,MsgBox::Question,"是否清空运行时间?");
    if(msg.exec()==MsgBox::Ok)
    {
        controller->userWriteData(PARA::Clear_cmd,1);
    }
}
