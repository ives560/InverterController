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
    ui_pwd.setupUi(ui.showArea);
    connect(ui_pwd.tbtn_ok,SIGNAL(clicked()),this,SLOT(tbtn_ok_clicked()));
    connect(ui_pwd.tbtn_back,SIGNAL(clicked()),this,SLOT(tbtn_ok_clicked()));
}

//参数设置界面
void paramSetFace::setupParaSetUi()
{
    ui_paraset.setupUi(ui.showArea);
    connect(ui_paraset.system,SIGNAL(clicked()),this,SLOT(tbtn_system_clicked()));
    connect(ui_paraset.run,SIGNAL(clicked()),this,SLOT(tbtn_run_clicked()));
    connect(ui_paraset.protect,SIGNAL(clicked()),this,SLOT(tbtn_protect_clicked()));
    connect(ui_paraset.comm,SIGNAL(clicked()),this,SLOT(tbtn_comm_clicked()));
}
//
bool paramSetFace::checkPassWord()
{
    OperaFile file=OperaFile("user.xml");
    QString in_pwd=ui_pwd.ledit_pwd->text();
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
        setAreaUi();
        setupParaSetUi();
        setAreaUi(true);
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
