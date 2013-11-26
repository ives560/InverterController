#include "rltimdttable.h"
#include "ui_rltimdttable.h"

RlTimDtTable::RlTimDtTable(QWidget *parent,MController *mc) :
    QWidget(parent),
    ui(new Ui::RlTimDtTable)
{
    ui->setupUi(this);
    controller = mc;
    TableInit();
}

RlTimDtTable::~RlTimDtTable()
{
    delete ui;
}

void RlTimDtTable::TableInit()
{
    table1=new ParaTableWidget(ui->widget);
    table1->setObjectName("table1");
    table1->setGeometry(0,0,ui->widget->width(),ui->widget->height());

    /*--------------设置表格数据--------------------------------*/
    table1->setRowCount(3);
    table1->setColumnCount(3);
    QStringList labels_h;
    labels_h<<"A"<<"B"<<"C";
    table1->setHorizontalHeaderLabels(labels_h);
    table1->horizontalHeader()->show();
    QStringList labels_v;
    labels_v<<"电网电压"<<"电网电流"<<"逆变器电流";
    table1->setVerticalHeaderLabels(labels_v);
   // table1->verticalHeader()->show();
    /*---------------------------------------------------------*/
    table1->setFocusPolicy(Qt::NoFocus);//不获得焦点，单击后没有虚线边框
    table1->setSelectionMode(QAbstractItemView::NoSelection);//单击后单元格不变灰
    table1->show();
}

void RlTimDtTable::bindTableData()
{
//    QString rowNames[]={"电网电压A","电网电压B","电网电压C",
//                         "电网电流A","电网电流B","电网电流C",
//                         "逆变器电流A","逆变器电流B","逆变器电流C"};
    //QString clum3Names[]={"视在功率","有功功率","无功功率"};
    //QString clum4Names[]={"功率因数","电网频率","计算效率"};
    //QString clum5Names[]={"太阳板输出电压","太阳板输出电流","太阳板输出功率"};
//    ParaInfo** paraArray=controller->paraArray;
//    int clum_a[]={Va,Vb,Vc};
//    int clum_b[]={Ia,Ib,Ic};
//    int clum_c[]={Int_Ia,Int_Ib,Int_Ic};
//    int clum_d[]={kva,kw,kvar};
//    int clum_e[]={pf,freq,efficy};
//    int clum_f[]={Vpv,Ipv,kwpv};

//    for(int i=1;i<4;i++)
//    {
//        tableWidget->bindData(0,i*2-1,paraArray[clum_a[i-1]]);
//        tableWidget->bindData(1,i*2-1,paraArray[clum_b[i-1]]);
//        tableWidget->bindData(2,i*2-1,paraArray[clum_c[i-1]]);
//        tableWidget->bindData(3,i*2-1,paraArray[clum_d[i-1]]);
//        tableWidget->bindData(4,i*2-1,paraArray[clum_e[i-1]]);
//        tableWidget->bindData(5,i*2-1,paraArray[clum_f[i-1]]);
//    }
//    tableWidget->setAllValToTable();
}
