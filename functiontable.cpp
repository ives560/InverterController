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
    ui_function.setupUi(ui.showArea);
    connect(ui_function.operationInfo,SIGNAL(clicked()),this,SLOT(operationInfo_Clicked()));
    connect(ui_function.historyInfo,SIGNAL(clicked()),this,SLOT(historyInfo_Clicked()));
    connect(ui_function.onOff,SIGNAL(clicked()),this,SLOT(onOff_Clicked()));
    connect(ui_function.paramSet,SIGNAL(clicked()),this,SLOT(paramSet_Clicked()));
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
