#include "rltimdttable.h"
#include "ui_rltimdttable.h"

RlTimDtTable::RlTimDtTable(QWidget *parent,MController *mc) :
    QWidget(parent),
    ui(new Ui::RlTimDtTable)
{
    ui->setupUi(this);
    controller = mc;
    TableInit();

    connect(ui->tbtn_left,SIGNAL(clicked()),this,SLOT(tbtn_left_clicked()));
    connect(ui->tbtn_right,SIGNAL(clicked()),this,SLOT(tbtn_right_clicked()));
}

RlTimDtTable::~RlTimDtTable()
{
    delete ui;
}
void RlTimDtTable::itemNamesInit()
{
    itemNames<<PARA::Va<<     PARA::Vb<<       PARA::Vc<<
               PARA::Ia<<     PARA::Ib<<       PARA::Ic<<
               PARA::Int_Ia<< PARA::Int_Ib<<   PARA::Int_Ic;

    nextItemNames<<PARA::kva  <<PARA::kw    <<PARA::kvar  <<PARA::pf    <<PARA::freq  <<PARA::efficy
                 <<PARA::Vpv   <<PARA::Ipv   <<PARA::kwpv;

}
void RlTimDtTable::TableInit()
{
    model_realtime = new ParaModel(3,4);

    QStringList labels_h;
    labels_h<<""<<"A"<<"B"<<"C";
    model_realtime->setHorizontalHeaderLabels(labels_h);

    QString rowNames[] = {"电网电压","电网电流","逆变器电流"};

    QStandardItem* item;
    for(int i=0;i<3;i++)
    {
        item = model_realtime->item(i);
        item->setText(rowNames[i]);
        for(int j=0;j<3;j++)
        {
            int name = itemNames[i*3+j];
            ParaItem* para = controller->paralist[name];
            model_realtime->bindData(i,j+1,para);
        }
    }
    controller->paralist.setType(itemNames,FAST_READ,true);
    model_realtime->setAllValToTable();

    /*-----------------------*/
    ui->tableView->setModel(model_realtime);

}

void RlTimDtTable::setTablePageShow(int star,int rows)
{
    if(model_realtime!=NULL)
        model_realtime->deleteLater();
    model_realtime = new ParaModel(rows,4);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(star>nextItemNames.count())
                return;
            int name = nextItemNames[star];
            ParaItem* para = controller->paralist[name];
            model_realtime->item(i,j*2)->setText(para->name);
            model_realtime->bindData(i,j*2+1,para);
            star++;
        }
    }

    /*-----------------------*/
    ui->tableView->horizontalHeader()->hide();//隐藏行标题列标题
    ui->tableView->verticalHeader()->hide();//隐藏行标题列标题
    ui->tableView->setModel(model_realtime);
}


void RlTimDtTable::tbtn_left_clicked()
{
    currentPage--;

}

void RlTimDtTable::tbtn_right_clicked()
{
    currentPage++;
    /*----------------------*/
//    int count = nextItemNames.count()/5;
//    if(index>=count)
//        ui->tbtn_right->hide();
//    else if(index<=)
}
