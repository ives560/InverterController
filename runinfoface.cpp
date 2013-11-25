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
    setTitle("运行信息",":/images/yunxingxinxi.png");
    /*-------------------------------------*/
    showRealTimePage();

	/*-------------按钮初始化------------------*/
    setupButton(pbtn_realTime,"实时数据",200,350,NULL,SLOT(realTime_clicked()));
    setupButton(pbtn_powerNet,"功率曲线",310,350,NULL,SLOT(powerNet_clicked()));
    setupButton(pbtn_powerColumn,"电量柱状图",420,350,NULL,SLOT(powerColumn_clicked()));
}

void RunInfoFace::realTimeTableInit()
{
    int rows=6,columns=6;

    QString clum0Names[]={"电网电压A","电网电压B","电网电压C"};
    QString clum1Names[]={"电网电流A","电网电流B","电网电流C"};
    QString clum2Names[]={"逆变器电流A","逆变器电流B","逆变器电流C"};
    QString clum3Names[]={"视在功率","有功功率","无功功率"};
    QString clum4Names[]={"功率因数","电网频率","计算效率"};
    QString clum5Names[]={"太阳板输出电压","太阳板输出电流","太阳板输出功率"};

    tableWidget=new ParaTableWidget(ui.showArea);

    tableWidget->setObjectName("table_realTime");
    tableWidget->setGeometry(0,0,700,250);

    /*--------------设置表格数据--------------------------------*/
    tableWidget->setRowCount(rows);
    tableWidget->setColumnCount(columns);
    QTableWidgetItem* item;
    for(int i=0;i<3;i++)
    {
        item = new QTableWidgetItem(clum0Names[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(0,i*2,item);
        item = new QTableWidgetItem(clum1Names[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(1,i*2,item);
        item = new QTableWidgetItem(clum2Names[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(2,i*2,item);
        item = new QTableWidgetItem(clum3Names[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(3,i*2,item);
        item = new QTableWidgetItem(clum4Names[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(4,i*2,item);
        item = new QTableWidgetItem(clum5Names[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(5,i*2,item);
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

void RunInfoFace::bindRealTimeTableData()
{
    ParaInfo** paraArray=controller->paraArray;
    int clum_a[]={Va,Vb,Vc};
    int clum_b[]={Ia,Ib,Ic};
    int clum_c[]={Int_Ia,Int_Ib,Int_Ic};
    int clum_d[]={kva,kw,kvar};
    int clum_e[]={pf,freq,efficy};
    int clum_f[]={Vpv,Ipv,kwpv};

    for(int i=1;i<4;i++)
    {
        tableWidget->bindData(0,i*2-1,paraArray[clum_a[i-1]]);
        tableWidget->bindData(1,i*2-1,paraArray[clum_b[i-1]]);
        tableWidget->bindData(2,i*2-1,paraArray[clum_c[i-1]]);
        tableWidget->bindData(3,i*2-1,paraArray[clum_d[i-1]]);
        tableWidget->bindData(4,i*2-1,paraArray[clum_e[i-1]]);
        tableWidget->bindData(5,i*2-1,paraArray[clum_f[i-1]]);
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
        readDataDone();
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
        readDataDone();
    }
}
void RunInfoFace::powerColumn_clicked()
{
    qDebug()<<"powerColumn_clicked";
    if(page != PowerCln)
    {
        clearShowUi();
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
