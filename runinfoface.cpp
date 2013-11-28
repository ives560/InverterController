#include "runinfoface.h"

RunInfoFace::RunInfoFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    page =None;
	setupUi();
    ui_runinfo.pbtn_realTime->click();

    //setFastReadType(true);
    //connect(controller, SIGNAL(readDataDone()),this, SLOT(readDataDone()));
}

RunInfoFace::~RunInfoFace()
{
    setFastReadType(false);
}

void RunInfoFace::setFastReadType(bool en)
{
    int count =18;
    int names[] = {Va,Vb,Vc,Ia,Ib,Ic,Int_Ia,Int_Ib,Int_Ic,kva,kw,kvar,pf,freq,efficy,Vpv,Ipv,kwpv};

    setReadType(names,count,FAST_READ,en);
}

void RunInfoFace::setupUi()
{
    setTitle("运行信息",":/images/shiyongxinxi.png");
    /*-------------------------------------*/
    ui_runinfo.setupUi(ui.showArea);
    connect(ui_runinfo.pbtn_realTime,SIGNAL(clicked()),this,SLOT(realTime_clicked()));
    connect(ui_runinfo.pbtn_powerNet,SIGNAL(clicked()),this,SLOT(powerNet_clicked()));
    connect(ui_runinfo.pbtn_powerColumn,SIGNAL(clicked()),this,SLOT(powerColumn_clicked()));
}

//
void RunInfoFace::showRealTimePage(QWidget* widget)
{
    realtimePage = new RlTimDtTable(widget,controller);
    realtimePage->setObjectName("realtimePage");
    realtimePage->show();
}

//显示功率曲线页面
void RunInfoFace::showPowerNetPage()
{
    chartWidget = new Chart(ui_runinfo.wgt_show);
    chartWidget->setObjectName("chartWidget");
    chartWidget->setGeometry(5,5,ui_runinfo.wgt_show->width()-10,250);

    chartWidget->CoordDataInit();
    chartWidget->setAxis(Chart::X,0,24,6,"t");
    chartWidget->setAxis(Chart::Y,0,100,5,"E");
    chartWidget->show();
    chartWidget->paint(true);
}

void RunInfoFace::powerNetInit()
{

}

//更新图表
void RunInfoFace::chartUpData()
{
    QSqlQuery query;
    if(controller->database!=NULL)
        query= controller->database->readTodayTable("kw");

    chartWidget->setQuery(query);
    chartWidget->paint(true);
}

void RunInfoFace::realTime_clicked()
{
    qDebug()<<"realTime_clicked";
    if(page != RealTime)
    {
        setWidgetChildren(ui_runinfo.wgt_show);
        showRealTimePage(ui_runinfo.wgt_show);
        page = RealTime;
        //readDataDone();
    }

}
void RunInfoFace::powerNet_clicked()
{
    qDebug()<<"powerNet_clicked";

    if(page != PowerNet)
    {
        setWidgetChildren(ui_runinfo.wgt_show);
        showPowerNetPage();
        page = PowerNet;
        readDataDone();
    }
}
void RunInfoFace::powerColumn_clicked()
{
    qDebug()<<"powerColumn_clicked";
    if(page != PowerCln)
    {
//        setAreaUi();
//        page = PowerCln;
//        readDataDone();
    }
}

void RunInfoFace::readDataDone()
{
    qDebug()<<"RunInfoFace"<<"readDataDone";
    if(page == RealTime)
    {tableWidget->setAllValToTable();}
    else if(page == PowerNet)
    {chartUpData();}
    else if(page == PowerCln)
    {}

}
