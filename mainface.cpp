#include "mainface.h"
#include "faultdialog.h"
#include <QBrush>

MainFace::MainFace(QWidget *parent, MController *mc)
	: QWidget(parent)
{
	ui.setupUi(this);
    controller=mc;
    setReadType(FAST_READ,true);
    labelDataBinding();
    chartInit();
    tableInit();
    upDataPara();
    readFastDataDoneSlot();
    connect(controller, SIGNAL(readDataDone()),this, SLOT(upDataPara()));
    connect(controller, SIGNAL(readFastDataDone()),this, SLOT(readFastDataDoneSlot()));
}

MainFace::~MainFace()
{
    setReadType(FAST_READ,false);
}
//设置参数快速读取
void MainFace::setReadType(int type,bool en)
{
    int names[] = {Ia,Ib,Ic,Va,Vb,Vc,Ipv,Vpv,kw,kwh_today,kwh_nv, Mwh_nv,Gwh_nv, HS1};
    ParaInfo* para;
    for(int i=0;i<12;i++)
    {
        para = controller->paraArray[names[i]];
        if(para!=NULL)
        {
            if(en == true)
                ParaInfo::seType(para,type);
            else
                ParaInfo::clearType(para,type);
        }
    }
}

//将数据和控件绑定
void MainFace::labelDataBinding()
{
    //按地址进行排列，根据地址索引变量
    int names[] = {Ia,Ib,Ic,Va,Vb,Vc,Ipv,Vpv};

    QLabel* label[]={ui.lab_ia, ui.lab_ib, ui.lab_ic,//交流电流
                     ui.lab_va, ui.lab_vb, ui.lab_vc,//交流电压
                     ui.lab_ipv, ui.lab_vpv};//直流
    ParaInfo* para;
    for(int i=0;i<8;i++)
    {
        para = controller->paraArray[names[i]];
        if(para!=NULL)
            labelist.append(QPair<QLabel*,ParaInfo*>(label[i],para));
    }
}
//更新参数
void MainFace::upDataPara()
{
    qDebug()<<"upDataPara";
    if(controller!=NULL)
    {
        chartUpData();
    }
}
//
void MainFace::readFastDataDoneSlot()
{
    qDebug()<<"readFastDataDoneSlot";
    if(controller!=NULL)
    {
        labelUpData();
        tableUpData();
    }
}

//更新label中的数据
void MainFace::labelUpData()
{
    int len=labelist.count();
    for(int i=0;i<len;i++)
    {
        int scaling=labelist[i].second->scaling;
        float val= labelist[i].second->values;
        val=val/scaling;
        QString unit=labelist[i].second->unit;
        labelist[i].first->setText(QString("%1%2").arg(val).arg(unit));
    }
}
//更新表中的数据
void MainFace::tableUpData()
{
    QTableWidgetItem* item=NULL;
    int names[4]={kw,kwh_today,Mwh_nv,HS1};
    ParaInfo* para;
    QString display;
    for(int i=0;i<4;i++)
    {
        item = ui.tableWidget->item(i,1);
        int name=names[i];
        para=controller->paraArray[name];

        float val_f=para->values;
        val_f= val_f/para->scaling;
        display=QString("%1%2").arg(val_f).arg(para->unit);
        item->setData(Qt::DisplayRole,display);
    }

        ParaInfo* para_k = controller->paraArray[kwh_nv];
        ParaInfo* para_m = controller->paraArray[Mwh_nv];
        ParaInfo* para_g = controller->paraArray[Gwh_nv];

        float val_mf = para_k->values/1000;
        val_mf += para_m->values;
        val_mf += para_g->values*1000;
        item = ui.tableWidget->item(2,1);
        display = QString("%1%2").arg(val_mf).arg(para_m->unit);
        item->setData(Qt::DisplayRole,display);

    //更新故障显示
    para=controller->paraArray[HS1];
    item=ui.tableWidget->item(4,1);
    if(para->values==0)
    {
        item->setData(Qt::DisplayRole,"故障");
        item->setForeground(QBrush(QColor(Qt::red)));

    }
    else
    {
        item->setData(Qt::DisplayRole,"运行");
        item->setForeground(QBrush(QColor(Qt::black)));
    }

}

//更新图表
void MainFace::chartUpData()
{
    QSqlQuery query;
    if(controller->database!=NULL)
        query= controller->database->readTodayTable("kw");

    ui.chart_power->setQuery(query);
    ui.chart_power->paint(true);
}

//曲线图初始化
void MainFace::chartInit()
{
    ui.chart_power->CoordDataInit();
    ui.chart_power->setAxis(Chart::X,0,24,6,"t");
    ui.chart_power->setAxis(Chart::Y,0,100,5,"E");
    ui.chart_power->paint(true);
}
//状态表初始化
void MainFace::tableInit()
{
    int rows=5,columns=2;
    QString paras[]={"输出功率","日发电量","总发电量","温度","工作状态"};
    ui.tableWidget->setRowCount(rows);
    ui.tableWidget->setColumnCount(columns);
    QTableWidgetItem* item;
    for(int i=0;i<rows;i++)
    {
        item = new QTableWidgetItem(paras[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));

        ui.tableWidget->setItem(i,0,item);
        ui.tableWidget->setItem(i,1,new QTableWidgetItem());
    }
    /*--------------设置表格属性--------------------------------*/

    ui.tableWidget->setGeometry(20,30,columns*100,rows*30);
    ui.tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui.tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//伸展行高列宽

    ui.tableWidget->setFocusPolicy(Qt::NoFocus);//不获得焦点，单击后没有虚线边框
    ui.tableWidget->setSelectionMode(QAbstractItemView::NoSelection);//单击后单元格不变灰
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//单元格只读

    ui.tableWidget->horizontalHeader()->hide();
    ui.tableWidget->verticalHeader()->hide();//隐藏行标题列标题

    ui.tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条

    connect(ui.tableWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(tableWidget_clicked(QModelIndex)));
}

//单击故障行
void MainFace::tableWidget_clicked(QModelIndex index)
{
    qDebug()<<"tableWidget_clicked:";
    if(index.row()==4)
    {
        qDebug()<<"row:"<<index.row();
        if(index.column()==1)
        {
            qDebug()<<"column:"<<index.column();
            FaultDialog* dialog=new FaultDialog(this);
            //传入错误编号
            dialog->show();
        }
    }
}

//画StyleSheet
void MainFace::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
