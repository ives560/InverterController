#include "paramsetface.h"
#include "operafile.h"
#include "runparasetface.h"
#include "systemparaface.h"
#include "msgbox.h"
paramSetFace::paramSetFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    setupUi();
    setupPassWordUi();

}

void paramSetFace::setupUi()
{
    setTitle("参数设置",":/images/canshuset.png");
}
//密码验证界面
void paramSetFace::setupPassWordUi()
{
    QLabel *label_text=new QLabel(ui.showArea);
    label_text->setObjectName("label_text");
    label_text->setGeometry(200,105,100,30);
    label_text->setStyleSheet("color:white;");
    label_text->setText("请输入管理员密码:");
    label_text->adjustSize();//自动调整宽度
    /*-------------------------------------*/
    ledit_pwd= new QLineEdit(ui.showArea);
    ledit_pwd->setObjectName("ledit_pwd");
    ledit_pwd->setGeometry(350,100,100,40);
    ledit_pwd->setEchoMode(QLineEdit::Password);
    ledit_pwd->setAlignment(Qt::AlignHCenter);
    ledit_pwd->setFrame(false);
    ledit_pwd->setStyleSheet("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0 rgba(0, 150, 228, 255), stop:1 rgba(190, 255, 247, 255));\
                             border:2px outset rgb(0, 150, 228);\
                             border-radius:5px;");

    /*--------确定按钮--------------------*/
    QToolButton *tbtn_ok=new QToolButton(ui.showArea);
    tbtn_ok->setObjectName("tbtn_ok");
    connect(tbtn_ok,SIGNAL(clicked()),this,SLOT(tbtn_ok_clicked()));
    setupChooseButton(tbtn_ok,"确定",QPoint(200,200),":/images/okbutton.png");
    /*---------返回按钮----------------------*/
    QToolButton *tbtn_back=new QToolButton(ui.showArea);
    connect(tbtn_back,SIGNAL(clicked()),this,SLOT(tbtn_ok_clicked()));
    tbtn_back->setObjectName("tbtn_back");
    setupChooseButton(tbtn_back,"返回",QPoint(400,200),":/images/return.png");
}

//参数设置界面
void paramSetFace::setupParamSetUi()
{
    /*------------------*/
    QToolButton *tbtn_system=new QToolButton(ui.showArea);
    tbtn_system->setObjectName("tbtn_system");
    connect(tbtn_system,SIGNAL(clicked()),this,SLOT(tbtn_system_clicked()));
    setupMenuButton(tbtn_system,"系统参数",QPoint(300,100),":/images/canshusetbig.png");

    /*------------------*/
    QToolButton *tbtn_run=new QToolButton(ui.showArea);
    tbtn_run->setObjectName("tbtn_run");
    connect(tbtn_run,SIGNAL(clicked()),this,SLOT(tbtn_run_clicked()));
    setupMenuButton(tbtn_run,"运行参数",QPoint(400,100),":/images/canshusetbig.png");
    /*------------------*/
    QToolButton *tbtn_protect=new QToolButton(ui.showArea);
    tbtn_protect->setObjectName("tbtn_protect");
    connect(tbtn_protect,SIGNAL(clicked()),this,SLOT(tbtn_protect_clicked()));
    setupMenuButton(tbtn_protect,"保护参数",QPoint(300,200),":/images/canshusetbig.png");
    /*------------------*/
    QToolButton *tbtn_comm=new QToolButton(ui.showArea);
    tbtn_comm->setObjectName("tbtn_comm");
    connect(tbtn_comm,SIGNAL(clicked()),this,SLOT(tbtn_comm_clicked()));
    setupMenuButton(tbtn_comm,"通讯参数",QPoint(400,200),":/images/canshusetbig.png");
}
//
bool paramSetFace::checkPassWord()
{
    OperaFile file=OperaFile("user.xml");
    QString in_pwd=ledit_pwd->text();
    QString pwd=file.getElementText("pwd");
    qDebug()<<"in_pwd:"<<in_pwd<<"pwd:"<<pwd;
    if(pwd==in_pwd)
        return true;
    else
        return false;
}
//
void paramSetFace::tbtn_ok_clicked()
{
    qDebug()<<"tbtn_ok_clicked";

    if(checkPassWord()==true)
    {
        clearShowUi();
        setupParamSetUi();
    }
    else
    {
        MsgBox msg(this,MsgBox::Critical,"密码错误，请重新输入");
        msg.exec();

    }
}
void paramSetFace::tbtn_system_clicked()
{
    qDebug()<<"tbtn_system_clicked";
    SystemParaFace* face = new SystemParaFace((QWidget*)inverter,controller);
    face->lastOne=this;
    inverter->addTopInterface(face);
}
void paramSetFace::tbtn_run_clicked()
{
    qDebug()<<"tbtn_run_clicked";
    RunParaSetFace* rpsf = new RunParaSetFace((QWidget*)inverter,controller);
    rpsf->lastOne=this;
    inverter->addTopInterface(rpsf);
}
void paramSetFace::tbtn_protect_clicked()
{
    qDebug()<<"tbtn_protect_clicked";
}
void paramSetFace::tbtn_comm_clicked()
{
    qDebug()<<"tbtn_comm_clicked";
}
