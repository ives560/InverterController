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
    QStandardItemModel* model=new QStandardItemModel(3,4);
    QStringList labels_h;
        labels_h<<""<<"A"<<"B"<<"C";
    model->setHorizontalHeaderLabels(labels_h);
    ui->tableView->setModel(model);
//    table1=new ParaTableWidget(ui->widget);
//    table1->setObjectName("table1");
//    table1->setGeometry(0,0,ui->widget->width(),ui->widget->height());

//    /*--------------设置表格数据--------------------------------*/
//    table1->setRowCount(3);
//    table1->setColumnCount(4);
//    QStringList labels_h;
//    labels_h<<""<<"A"<<"B"<<"C";
//    table1->setHorizontalHeaderLabels(labels_h);
//    table1->horizontalHeader()->show();

//    QStringList labels_v;
//    labels_v<<"电网电压"<<"电网电流"<<"逆变器电流";
//    table1->setVerticalHeaderLabels(labels_v);
//    table1->verticalHeader()->show();

    /*---------------------------------------------------------*/
//    table1->setFocusPolicy(Qt::NoFocus);//不获得焦点，单击后没有虚线边框
//    table1->setSelectionMode(QAbstractItemView::NoSelection);//单击后单元格不变灰
//    table1->show();
}

void RlTimDtTable::bindTableData()
{

}
