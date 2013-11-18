#include "functiontable.h"
#include "invertercontroller.h"
#include "paramsetface.h"
#include "runinfoface.h"
#include "historyinfoface.h"
#include "powerface.h"

FunctionTable::FunctionTable(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    setupUi();
}

FunctionTable::~FunctionTable()
{

}

void FunctionTable::setupUi()
{
    setTitle("功能表",":/images/gongnengbiao.png");
    /*--------------------------------*/
    operationInfo=new QToolButton(this);
    operationInfo->setObjectName("operationInfo");
    connect(operationInfo,SIGNAL(clicked()),this,SLOT(operationInfo_Clicked()));
    setupMenuButton(operationInfo,"运行信息",QPoint(300,90),":/images/yunxingxinxi.png");
    /*--------------------------------*/
    historyInfo=new QToolButton(this);
    historyInfo->setObjectName("historyInfo");
    connect(historyInfo,SIGNAL(clicked()),this,SLOT(historyInfo_Clicked()));
    setupMenuButton(historyInfo,"历史信息",QPoint(400,90),":/images/lishixinxi.png");
    /*--------------------------------*/
    onOff=new QToolButton(this);
    onOff->setObjectName("onOff");
    connect(onOff,SIGNAL(clicked()),this,SLOT(onOff_Clicked()));
    setupMenuButton(onOff,"开/关机",QPoint(300,190),":/images/kaiguanji.png");
    /*--------------------------------*/
    paramSet=new QToolButton(this);
    paramSet->setObjectName("paramSet");
    connect(paramSet,SIGNAL(clicked()),this,SLOT(paramSet_Clicked()));
    setupMenuButton(paramSet,"参数设置",QPoint(400,190),":/images/canshushezi.png");
}

//运行信息
void FunctionTable::operationInfo_Clicked()
{
	qDebug()<<"operationInfo_Clickde";
    RunInfoFace* rif=new RunInfoFace((QWidget*)inverter,controller);
	rif->lastOne=this;
	inverter->addTopInterface(rif);
}
//历史信息
void FunctionTable::historyInfo_Clicked()
{
	qDebug()<<"historyInfo_Clickde";
    HistoryInfoFace* hif = new HistoryInfoFace((QWidget*)inverter,controller);
    hif->lastOne=this;
    inverter->addTopInterface(hif);
}
//开关机
void FunctionTable::onOff_Clicked()
{
	qDebug()<<"onOff_Clickde";
    PowerFace* pf = new PowerFace((QWidget*)inverter,controller);
    pf->lastOne=this;
    inverter->addTopInterface(pf);
}

//参数设置
void FunctionTable::paramSet_Clicked()
{
	qDebug()<<"paramSet_Clickde";
    paramSetFace* psf=new paramSetFace((QWidget*)inverter,controller);
    psf->lastOne=this;
    inverter->addTopInterface(psf);

}
