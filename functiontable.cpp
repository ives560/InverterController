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
    setTitle("功能",":/images/gongneng.png");
    /*--------------------------------*/
    operationInfo=new QToolButton(ui.showArea);
    operationInfo->setObjectName("operationInfo");
    connect(operationInfo,SIGNAL(clicked()),this,SLOT(operationInfo_Clicked()));
    setupMenuButton(operationInfo,"使用信息",QPoint(200,20),":/images/shiyongxinxibig.png");
    /*--------------------------------*/
    historyInfo=new QToolButton(ui.showArea);
    historyInfo->setObjectName("historyInfo");
    connect(historyInfo,SIGNAL(clicked()),this,SLOT(historyInfo_Clicked()));
    setupMenuButton(historyInfo,"历史记录",QPoint(500,20),":/images/hostorybig.png");
    /*--------------------------------*/
    onOff=new QToolButton(ui.showArea);
    onOff->setObjectName("onOff");
    connect(onOff,SIGNAL(clicked()),this,SLOT(onOff_Clicked()));
    setupMenuButton(onOff,"开机/关机",QPoint(200,200),":/images/openbig.png");
    /*--------------------------------*/
    paramSet=new QToolButton(ui.showArea);
    paramSet->setObjectName("paramSet");
    connect(paramSet,SIGNAL(clicked()),this,SLOT(paramSet_Clicked()));
    setupMenuButton(paramSet,"参数设置",QPoint(500,200),":/images/canshusetbig.png");
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
