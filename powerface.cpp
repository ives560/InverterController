#include "powerface.h"
#include <QMessageBox>
#include "msgbox.h"
PowerFace::PowerFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    if(controller==NULL)
        return;
    m_parent = parent;
    qRegisterMetaType<ParaList>("ParaList");
    connect(controller,SIGNAL(writeDataDone(ParaList,bool)),this,SLOT(writeDoneSlot(ParaList,bool)));
    setTitle("开机/关机",":/images/kaiguanji.png");
    setupButton(start,"启动",100,100,":/images/openbig.png",SLOT(start_Clickde()));
    setupButton(shutdown,"关机",250,100,":/images/shutdownbig.png",SLOT(shutdown_Clickde()));
    setupButton(reset,"重启",400,100,":/images/openbig.png",SLOT(reset_Clickde()));
    setupButton(stop,"停止",550,100,":/images/shutdownbig.png",SLOT(stop_Clickde()));
    isready=true;
}

PowerFace::~PowerFace()
{

}

//新建按钮
void PowerFace::setupButton(QToolButton *button,QString text,int x,int y,QString iconPath,const char* member)
{
    button=new QToolButton(this);
    button->setObjectName(text);
    button->setStyleSheet("background:transparent;color:white;font-Weight:bold;");
    button->setText(text);
    button->setGeometry(x,y,100,100);
	button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QIcon icon;
    //icon.addFile(QString::fromUtf8(path), QSize(), QIcon::Normal, QIcon::Off);
    icon.addFile(iconPath, QSize(), QIcon::Normal, QIcon::Off);
    button->setIcon(icon);
    button->setIconSize(QSize(60, 60));
    connect(button,SIGNAL(clicked()),this,member);
}

void PowerFace::shutdown_Clickde()
{
	qDebug()<<"shutdown_Clickde";
     int ret=showMessageBox("确定关机？");
     if(ret==QMessageBox::Ok)       
        controller->userWriteData(controller->paraArray[sys_cmd],1);//调试地址和实际地址不同
     m_parent->deleteLater();
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

