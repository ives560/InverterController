#include "rltimdttable.h"
#include "ui_rltimdttable.h"

RlTimDtTable::RlTimDtTable(QWidget *parent,MController *mc) :
    QWidget(parent),
    ui(new Ui::RlTimDtTable)
{
    ui->setupUi(this);
    controller = mc;
    itemNamesInit();

    connect(ui->tbtn_left,SIGNAL(clicked()),this,SLOT(tbtn_left_clicked()));
    connect(ui->tbtn_right,SIGNAL(clicked()),this,SLOT(tbtn_right_clicked()));

    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(86,197,255);}");
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//固定行高列宽
    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);

    currentPage = 2;
    model_realtime = NULL;
    ui->tbtn_left->click();
}

RlTimDtTable::~RlTimDtTable()
{
    controller->paralist.setType(itemNames,FAST_READ,false);
    controller->paralist.setType(nextItemNames,FAST_READ,false);
    delete ui;
}
void RlTimDtTable::itemNamesInit()
{
    itemNames<<PARA::Va<<     PARA::Vb<<       PARA::Vc<<
               PARA::Ia<<     PARA::Ib<<       PARA::Ic<<
               PARA::Int_Ia<< PARA::Int_Ib<<   PARA::Int_Ic;

    nextItemNames<<PARA::kva  <<PARA::kw    <<PARA::kvar  <<PARA::pf    <<PARA::freq  <<PARA::efficy
                 <<PARA::Vpv   <<PARA::Ipv   <<PARA::kwpv;

    controller->paralist.setType(itemNames,FAST_READ,true);
    controller->paralist.setType(nextItemNames,FAST_READ,true);
    totalPage = nextItemNames.count()/TABLE_ROWS +1;
}
void RlTimDtTable::TableInit()
{
    if(model_realtime!=NULL)
        model_realtime->deleteLater();

    model_realtime = new ParaModel(3,4);

    QStringList labels_h;
    labels_h<<"  "<<"A"<<"B"<<"C";
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

    model_realtime->setAllValToTable();

    /*-----------------------*/
    ui->tableView->horizontalHeader()->show();//xians 行标题列标题
    ui->tableView->setModel(model_realtime);

}

void RlTimDtTable::setTablePageShow(int star)
{
    if(model_realtime!=NULL)
        model_realtime->deleteLater();
    model_realtime = new ParaModel(TABLE_ROWS,4);
    for(int i=0;i<TABLE_ROWS;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(star>=nextItemNames.count())
                break;
            int name = nextItemNames[star];
            ParaItem* para = controller->paralist[name];
            model_realtime->item(i,j*2)->setText(para->name);
            model_realtime->bindData(i,j*2+1,para);
            star++;
        }
    }

    model_realtime->setAllValToTable();
    /*-----------------------*/
    ui->tableView->horizontalHeader()->hide();//隐藏行标题列标题
    ui->tableView->setModel(model_realtime);
}


void RlTimDtTable::tbtn_left_clicked()
{
    currentPage--;
    if(currentPage==1)
    {
        ui->tbtn_left->hide();
        ui->tbtn_right->show();
        TableInit();
    }
    else
    {
        setTablePageShow((currentPage-2)*TABLE_ROWS);
    }

    ui->lab_page->setText(QString("%1/%2").arg(currentPage).arg(totalPage));
}

void RlTimDtTable::tbtn_right_clicked()
{
    currentPage++;
    if(currentPage==totalPage)
    {
        ui->tbtn_left->show();
        ui->tbtn_right->hide();
    }
    setTablePageShow((currentPage-2)*TABLE_ROWS);
    ui->lab_page->setText(QString("%1/%2").arg(currentPage).arg(totalPage));
}
