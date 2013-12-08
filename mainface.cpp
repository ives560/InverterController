#include "mainface.h"
#include "faultdialog.h"

#include "historyfault.h"

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
    connect(controller, SIGNAL(readAlwaysDataDone()),this, SLOT(upDataPara()));
    connect(controller, SIGNAL(readFastDataDone()),this, SLOT(readFastDataDoneSlot()));
}

MainFace::~MainFace()
{
    setReadType(FAST_READ,false);
}
//设置参数快速读取
void MainFace::setReadType(int type,bool en)
{
    int names[14] = {PARA::Ia,      PARA::Ib,       PARA::Ic,       PARA::Va,       PARA::Vb,
                     PARA::Vc,      PARA::Ipv,      PARA::Vpv,      PARA::kw,       PARA::kwh_today,
                     PARA::kwh_nv,  PARA::Mwh_nv,   PARA::Gwh_nv,   PARA::HS1};
    controller->paralist.setType(names,14,type,en);
}

//将数据和控件绑定
void MainFace::labelDataBinding()
{
    //按地址进行排列，根据地址索引变量
    int names[] = {PARA::Ia,    PARA::Ib,   PARA::Ic,
                   PARA::Va,    PARA::Vb,   PARA::Vc,
                   PARA::Ipv,   PARA::Vpv};

    QLabel* label[]={ui.lab_ia, ui.lab_ib, ui.lab_ic,//交流电流
                     ui.lab_va, ui.lab_vb, ui.lab_vc,//交流电压
                     ui.lab_ipv, ui.lab_vpv};//直流
    ParaItem* para;
    for(int i=0;i<8;i++)
    {
        para = controller->paralist[names[i]];
        if(para!=NULL)
            labelist.append(QPair<QLabel*,ParaItem*>(label[i],para));
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
    int names[4]={PARA::kw,PARA::kwh_today,PARA::Mwh_nv,PARA::HS1};
    ParaItem* para;
    QString display;
    for(int i=0;i<4;i++)
    {
        item = ui.tableWidget->item(i,1);
        para=controller->paralist[names[i]];

        float val_f=para->values;
        val_f= val_f/para->scaling;
        display=QString("%1%2").arg(val_f).arg(para->unit);
        item->setData(Qt::DisplayRole,display);
    }

        ParaItem* para_m = controller->paralist[PARA::Mwh_nv];

        double val_mf = controller->paralist.countTotal(PARA::Gwh_nv,PARA::Mwh_nv,PARA::kwh_nv);
        item = ui.tableWidget->item(2,1);
        display = QString("%1%2").arg(val_mf,0, 'f', 3).arg(para_m->unit);
        item->setData(Qt::DisplayRole,display);

    //更新故障显示
    int led = controller->paralist[PARA::digi_out1]->values;
    bool g = led&0x02;
    bool r = led&0x04;
    item=ui.tableWidget->item(4,1);
    if((g==true)&&(r==false))//绿灯灭，红灯亮
    {
        item->setData(Qt::DisplayRole,"故障");
        item->setForeground(QBrush(QColor(Qt::red)));

    }
    else if((g==false)&&(r==true))//绿灯亮，红灯灭
    {
        item->setData(Qt::DisplayRole,"运行");
        item->setForeground(QBrush(QColor(Qt::black)));
    }
    else
        item->setData(Qt::DisplayRole,"");
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
//            HistoryFault* hif = new HistoryFault((QWidget*)inverter,controller);
//            hif->lastOne=this;
//            inverter->addTopInterface(hif);
//            FaultDialog* dialog=new FaultDialog(this,controller);
//            //传入错误编号
//            dialog->show();
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
