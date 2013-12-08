#include "historyfault.h"

HistoryFault::HistoryFault(QWidget *parent,MController* mc)
                :SubMenu(parent,mc)
{
    setTitle("故障追踪",":/images/guzhangzhuizhong.png");
    ui_hstyflt.setupUi(ui.showArea);
    tableViewInit();

    connect(ui_hstyflt.tbtn_left,SIGNAL(clicked()),this,SLOT(tbtn_left_clicked()));
    connect(ui_hstyflt.tbtn_right,SIGNAL(clicked()),this,SLOT(tbtn_right_clicked()));
    model = NULL;
    currentPage = 2;
    ui_hstyflt.tbtn_left->click();
}

void HistoryFault::tableViewInit()
{
    ui_hstyflt.tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(86,197,255);color: rgb(255, 255, 255);}");
    ui_hstyflt.tableView->setSelectionMode(QAbstractItemView::NoSelection);//单击后单元格不变灰
    ui_hstyflt.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//单元格只读
    ui_hstyflt.tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui_hstyflt.tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui_hstyflt.tableView->horizontalHeader()->setDisabled(true);

}

void HistoryFault::setTablePageShow(int star)
{
    if(model!=NULL)
        model->deleteLater();

    QStringList list;
    list<<"序号"<<"时间"<<"故障名称"<<"故障描述";
    const int count_list = list.count();
    model = new QStandardItemModel(ONE_PAGE_ROWS,count_list);
    model->setHorizontalHeaderLabels(list);

    int count =controller->fault_queue.count();
    int page = count/ONE_PAGE_ROWS;
    if((count%ONE_PAGE_ROWS)>0)
        page++;
    totalPage =  page;

    for(int i=0;i<ONE_PAGE_ROWS;i++)
    {
        if(star>=count)
            break;

        FaultItem faultem = controller->fault_queue[star];
        QStandardItem* item = new QStandardItem(QString("%1").arg(star+1));
        model->setItem(i,0,item);

        item = new QStandardItem(faultem.date);
        model->setItem(i,1,item);

        item = new QStandardItem(faultem.node.name);
        model->setItem(i,2,item);

        item = new QStandardItem(faultem.node.details);
        model->setItem(i,3,item);

        star++;
    }
    /*-----------------------*/
    ui_hstyflt.tableView->setModel(model);
    QHeaderView* hView = ui_hstyflt.tableView->horizontalHeader();
    hView->setResizeMode((hView->count()-1),QHeaderView::Stretch);//拉伸行高列宽

}

void HistoryFault::tbtn_left_clicked()
{
    currentPage--;
    if(currentPage==1)
    {
        ui_hstyflt.tbtn_left->hide();
    }
    if(ui_hstyflt.tbtn_right->isHidden())
        ui_hstyflt.tbtn_right->show();
    setTablePageShow((currentPage-1)*ONE_PAGE_ROWS);
    ui_hstyflt.lab_page->setText(QString("%1/%2").arg(currentPage).arg(totalPage));
}

void HistoryFault::tbtn_right_clicked()
{
    currentPage++;
    if(currentPage==totalPage)
    {
        ui_hstyflt.tbtn_right->hide();
    }
    if(ui_hstyflt.tbtn_left->isHidden())
        ui_hstyflt.tbtn_left->show();
    setTablePageShow((currentPage-1)*ONE_PAGE_ROWS);
    ui_hstyflt.lab_page->setText(QString("%1/%2").arg(currentPage).arg(totalPage));
}
