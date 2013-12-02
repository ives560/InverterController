#include "systemparaface.h"
#include "clocksetface.h"
#include "language.h"

SystemParaFace::SystemParaFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    setupUi();

}

void SystemParaFace::setupUi()
{
    setTitle("系统参数",":/images/yunxingshezhi.png");
    ui_system.setupUi(ui.showArea);
    connect(ui_system.language,SIGNAL(clicked()),this,SLOT(tbtn_language_clicked()));
    connect(ui_system.clock,SIGNAL(clicked()),this,SLOT(tbtn_clock_clicked()));
    connect(ui_system.revise,SIGNAL(clicked()),this,SLOT(tbtn_revise_clicked()));
    connect(ui_system.restore,SIGNAL(clicked()),this,SLOT(tbtn_restore_clicked()));

}
//语言设置
void SystemParaFace::tbtn_language_clicked()
{
    qDebug()<<"tbtn_language_clicked";
    Language* lge = new Language((QWidget*)inverter,controller);
    lge->lastOne = this;
    inverter->addTopInterface(lge);
}
//时钟设置
void SystemParaFace::tbtn_clock_clicked()
{
    qDebug()<<"tbtn_run_clicked";
    ClockSetFace* csf = new ClockSetFace((QWidget*)inverter,controller);
    csf->lastOne=this;
    inverter->addTopInterface(csf);
}

void SystemParaFace::tbtn_revise_clicked()
{

}
void SystemParaFace::tbtn_restore_clicked()
{

}
