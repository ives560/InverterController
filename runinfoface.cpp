#include "runinfoface.h"

RunInfoFace::RunInfoFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    page =None;
	setupUi();
    ui_runinfo.pbtn_realTime->click();


}

RunInfoFace::~RunInfoFace()
{

}

void RunInfoFace::setupUi()
{
    setTitle("运行信息",":/images/shiyongxinxi.png");
    /*-------------------------------------*/
    ui_runinfo.setupUi(ui.showArea);
    connect(ui_runinfo.pbtn_realTime,SIGNAL(clicked()),this,SLOT(realTime_clicked()));
    connect(ui_runinfo.pbtn_powerNet,SIGNAL(clicked()),this,SLOT(powerNet_clicked()));
    connect(ui_runinfo.pbtn_powerColumn,SIGNAL(clicked()),this,SLOT(powerColumn_clicked()));

    connect(controller, SIGNAL(readAlwaysDataDone()),this, SLOT(readAlwaysDataSlot()));
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
        setWidgetChildren(ui_runinfo.wgt_show,false);
        showRealTimePage(ui_runinfo.wgt_show);
        page = RealTime;
    }

}
void RunInfoFace::powerNet_clicked()
{
    qDebug()<<"powerNet_clicked";

    if(page != PowerNet)
    {
        setWidgetChildren(ui_runinfo.wgt_show,false);
        showPowerNetPage();
        page = PowerNet;
        //readAlwaysDataSlot();
    }
}
void RunInfoFace::powerColumn_clicked()
{
    qDebug()<<"powerColumn_clicked";
    if(page != PowerCln)
    {
        setWidgetChildren(ui_runinfo.wgt_show,false);
        elechartPage = new ElectricityChart(ui_runinfo.wgt_show,controller);
        elechartPage->setObjectName("realtimePage");
        elechartPage->show();
        page = PowerCln;
    }
}

void RunInfoFace::readAlwaysDataSlot()
{
    qDebug()<<"RunInfoFace"<<"readAlwaysDataSlot";
    if(page == PowerNet)
    {chartUpData();}


}
