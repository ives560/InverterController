#include "runinfoface.h"

RunInfoFace::RunInfoFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    page =RealTime;
    setFastReadType(true);
	setupUi();
    connect(controller, SIGNAL(readDataDone()),this, SLOT(readDataDone()));
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
    showRealTimePage();

	/*-------------按钮初始化------------------*/
    setupButton(pbtn_realTime,"实时数据",200,365,NULL,SLOT(realTime_clicked()));
    setupButton(pbtn_powerNet,"功率曲线",310,365,NULL,SLOT(powerNet_clicked()));
    setupButton(pbtn_powerColumn,"电量柱状图",420,365,NULL,SLOT(powerColumn_clicked()));
}



void RunInfoFace::setupButton(QPushButton *button,QString text,int x,int y,
                                QString iconPath,const char* member)
{
    button=new QPushButton(this);
    button->setObjectName(text);
    button->setStyleSheet(" background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #96f7fa, stop: 1 #dadbde);\
                          border-style: outset;\
                          border-width: 1px;\
                          border-radius: 3px;\
                          border-color: beige;\
                          font: bold 14px;");
    button->setText(text);
    button->setGeometry(x,y,100,30);
    connect(button,SIGNAL(clicked()),this,member);

}

//
void RunInfoFace::showRealTimePage()
{
    realtimePage = new RlTimDtTable(ui.showArea,controller);
    realtimePage->setObjectName("realtimePage");
    realtimePage->move(0,0);
    realtimePage->show();
}

//显示功率曲线页面
void RunInfoFace::showPowerNetPage()
{
    chartWidget = new Chart(ui.showArea);
    chartWidget->setObjectName("chartWidget");
    chartWidget->setGeometry(5,5,ui.showArea->width()-10,250);

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
        setAreaUi();
        showRealTimePage();
        page = RealTime;
        readDataDone();
    }

}
void RunInfoFace::powerNet_clicked()
{
    qDebug()<<"powerNet_clicked";
    if(page != PowerNet)
    {
        setAreaUi();
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
        setAreaUi();
        page = PowerCln;
        readDataDone();
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
