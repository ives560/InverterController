#include "historyfault.h"

HistoryFault::HistoryFault(QWidget *parent,MController* mc)
                :SubMenu(parent,mc)
{
    setupUi();

}

void HistoryFault::setupUi()
{
    setTitle("故障追踪",":/images/guzhangzhuizhong.png");
    sqlTableModelInit();
    tableViewInit();

}

void HistoryFault::sqlTableModelInit()
{
    model = new QSqlTableModel();
    model->setTable("fault");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"序号");
    model->setHeaderData(1,Qt::Horizontal,"时间");
    model->setHeaderData(2,Qt::Horizontal,"故障名称");
    model->setHeaderData(3,Qt::Horizontal,"故障描述");
}

void HistoryFault::tableViewInit()
{
    tableView = new QTableView(ui.showArea);
    tableView->setObjectName("tableView");
    tableView->setGeometry(25,25,ui.showArea->width()-50,ui.showArea->height()-50);
    tableView->setStyleSheet("QHeaderView::section{background-color:white;color:blue}");
    tableView->setModel(model);//要在setStyleSheet上面
    QHeaderView* hView = tableView->horizontalHeader();
    hView->setDisabled(true);
    hView->setResizeMode(QHeaderView::ResizeToContents);//拉伸行高列宽
    if(hView->width()<tableView->width())
        hView->setResizeMode((hView->count()-1),QHeaderView::Stretch);//拉伸行高列宽

    tableView->verticalHeader()->hide();//隐藏行标题列标题
    tableView->setFocusPolicy(Qt::NoFocus);//不获得焦点，单击后没有虚线边框
    tableView->setSelectionMode(QAbstractItemView::NoSelection);//单击后单元格不变灰
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//单元格只读
}
