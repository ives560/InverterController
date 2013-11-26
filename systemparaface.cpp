#include "systemparaface.h"
#include "clocksetface.h"
SystemParaFace::SystemParaFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    setupUi();

}

void SystemParaFace::setupUi()
{
    setTitle("系统参数",":/images/yunxingshezhi.png");
    /*------------------*/
    QToolButton *tbtn_language=new QToolButton(ui.showArea);
    tbtn_language->setObjectName("tbtn_language");
    connect(tbtn_language,SIGNAL(clicked()),this,SLOT(tbtn_language_clicked()));
    setupMenuButton(tbtn_language,"语言",QPoint(300,100),":/images/yuyantishi.png");

    /*------------------*/
    QToolButton *tbtn_clock=new QToolButton(ui.showArea);
    tbtn_clock->setObjectName("tbtn_clock");
    connect(tbtn_clock,SIGNAL(clicked()),this,SLOT(tbtn_clock_clicked()));
    setupMenuButton(tbtn_clock,"时钟",QPoint(400,100),":/images/time.png");
    /*------------------*/
    QToolButton *tbtn_protect=new QToolButton(ui.showArea);
    tbtn_protect->setObjectName("tbtn_protect");
    connect(tbtn_protect,SIGNAL(clicked()),this,SLOT(tbtn_protect_clicked()));
    setupMenuButton(tbtn_protect,"发电总量校正",QPoint(300,200),":/images/zhongfadian.png");
    /*------------------*/
    QToolButton *tbtn_comm=new QToolButton(ui.showArea);
    tbtn_comm->setObjectName("tbtn_comm");
    connect(tbtn_comm,SIGNAL(clicked()),this,SLOT(tbtn_comm_clicked()));
    setupMenuButton(tbtn_comm,"恢复出厂值",QPoint(400,200),":/images/chuchangshezi.png");
}
//语言设置
void SystemParaFace::tbtn_language_clicked()
{

}
//时钟设置
void SystemParaFace::tbtn_clock_clicked()
{
    qDebug()<<"tbtn_run_clicked";
    ClockSetFace* csf = new ClockSetFace((QWidget*)inverter,controller);
    csf->lastOne=this;
    inverter->addTopInterface(csf);
}

void SystemParaFace::tbtn_protect_clicked()
{

}
void SystemParaFace::tbtn_comm_clicked()
{

}
