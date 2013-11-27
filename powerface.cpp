#include "powerface.h"
#include <QMessageBox>
#include "msgbox.h"
PowerFace::PowerFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    if(controller==NULL)
        return;
    ui_power.setupUi(ui.showArea);
    m_parent = parent;
    qRegisterMetaType<ParaList>("ParaList");
    connect(controller,SIGNAL(writeDataDone(ParaList,bool)),this,SLOT(writeDoneSlot(ParaList,bool)));
    setTitle("开机/关机",":/images/kaiguanji.png");
    connect(ui_power.start,SIGNAL(clicked()),this,SLOT(start_Clickde()));
    connect(ui_power.shutdown,SIGNAL(clicked()),this,SLOT(shutdown_Clickde()));
    connect(ui_power.reset,SIGNAL(clicked()),this,SLOT(reset_Clickde()));
    connect(ui_power.stop,SIGNAL(clicked()),this,SLOT(stop_Clickde()));
    isready=true;
}

PowerFace::~PowerFace()
{

}


void PowerFace::shutdown_Clickde()
{
	qDebug()<<"shutdown_Clickde";
     int ret=showMessageBox("确定关机？");
     if(ret==QMessageBox::Ok)
     {
        controller->userWriteData(controller->paraArray[sys_cmd],1);//调试地址和实际地址不同
        m_parent->deleteLater();
     }

}

void PowerFace::stop_Clickde()
{
    qDebug()<<"stop_Clickde";
    int ret=showMessageBox("确定停止？");
    if(ret==QMessageBox::Ok)
        controller->userWriteData(controller->paraArray[sys_cmd],2);
}

void PowerFace::reset_Clickde()
{
	qDebug()<<"reset_Clickde";
    int ret=showMessageBox("确定重新启动？");
    if(ret==QMessageBox::Ok)
        controller->userWriteData(controller->paraArray[sys_cmd],4);
}

void PowerFace::start_Clickde()
{
	qDebug()<<"start_Clickde";
    int ret=showMessageBox("确定启动？");
    if(ret==QMessageBox::Ok)
        controller->userWriteData(controller->paraArray[sys_cmd],8);
}
//串口写入失败槽
void PowerFace::writeDoneSlot(ParaList list,bool succeed)
{
    if(succeed==false)
    {
        qDebug()<<"writeError";

        QString str;
        for(int i=0;i<list.count();i++)
        {
            str +=QString("写地址%1值%2失败！\n").arg(list[i]->address).arg(list[i]->val_w);
        }
        MsgBox* msgBox=new MsgBox(this,MsgBox::Critical,str);
        msgBox->show();
    }
}
//显示警告窗口
int PowerFace::showMessageBox(QString text)
{
    MsgBox msgBox(this,MsgBox::Question,text);

    return msgBox.exec();
}

