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
    int names[] = {Va,Vb,Vc,Ia,Ib,Ic,Int_Ia,Int_Ib,Int_Ic,kva,kw,kvar};
    setReadType(names,12,FAST_READ,en);
}

void RunInfoFace::setupUi()
{
    setTitle("运行信息",":/images/yunxingxinxi.png");
    /*-------------------------------------*/
    showRealTimePage();

	/*-------------按钮初始化------------------*/
    setupButton(pbtn_realTime,"实时数据",200,350,NULL,SLOT(realTime_clicked()));
    setupButton(pbtn_powerNet,"功率曲线",300,350,NULL,SLOT(powerNet_clicked()));
    setupButton(pbtn_powerColumn,"电量柱状图",400,350,NULL,SLOT(powerColumn_clicked()));
}

void RunInfoFace::realTimeTableInit()
{
    int rows=6,columns=4;
    QString clum0Names[]={"直流电压","直流电流","电网频率","日运行分钟","减少CO2排放","功率因数"};
    QString clum2Names[]={"输出功率","日发电量","月发电量","总发电量","总运行时数","工作状态"};

    tableWidget=new ParaTableWidget(ui.showArea);

    tableWidget->setObjectName("table_realTime");
    tableWidget->setGeometry(150,0,500,250);

    /*--------------设置表格数据--------------------------------*/
    tableWidget->setRowCount(rows);
    tableWidget->setColumnCount(columns);
    QTableWidgetItem* item;
    for(int i=0;i<rows;i++)
    {
        item = new QTableWidgetItem(clum0Names[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(i,0,item);
        item = new QTableWidgetItem(clum2Names[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(i,2,item);
    }
    /*---------------------------------------------------------*/ 
    tableWidget->setFocusPolicy(Qt::NoFocus);//不获得焦点，单击后没有虚线边框
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);//单击后单元格不变灰
    tableWidget->show();
}

void RunInfoFace::setupButton(QPushButton *button,QString text,int x,int y,
                                QString iconPath,const char* member)
{
    button=new QPushButton(this);
    button->setObjectName(text);
    button->setStyleSheet("background:transparent");
    button->setText(text);
    button->setGeometry(x,y,100,30);
    connect(button,SIGNAL(clicked()),this,member);

}

void RunInfoFace::bindRealTimeTableData()
{
    ParaInfo** paraArray=controller->paraArray;
    int clum_a[]={Va,Vb,Vc,Ia,Ib,Ic};
    int clum_b[]={Int_Ia,Int_Ib,Int_Ic,kva,kw,kvar};

    for(int i=0;i<tableWidget->rowCount();i++)
    {
        tableWidget->bindData(i,1,paraArray[clum_a[i]]);
        tableWidget->bindData(i,3,paraArray[clum_b[i]]);
    }
    tableWidget->setAllValToTable();
}

void RunInfoFace::showRealTimePage()
{
    realTimeTableInit();
    bindRealTimeTableData();
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
        clearShowUi();
        showRealTimePage();
        page = RealTime;
    }

}
void RunInfoFace::powerNet_clicked()
{
    qDebug()<<"powerNet_clicked";
    if(page != PowerNet)
    {
        clearShowUi();
        showPowerNetPage();
        page = PowerNet;
    }
}
void RunInfoFace::powerColumn_clicked()
{
    qDebug()<<"powerColumn_clicked";
    if(page != PowerCln)
    {
        clearShowUi();
        page = PowerCln;
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
