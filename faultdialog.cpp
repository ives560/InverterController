#include "faultdialog.h"

FaultDialog::FaultDialog(QWidget *parent, MController *mc)
    :QDialog(parent,Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint)
{
    controller = mc;
    ui.setupUi(this);
    setupUi();
}

void FaultDialog::setupUi()
{
    /*--------------------------------------------*/
    ui.tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    ui.tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//固定行高列宽

    setTableVal();

    connect(ui.tbtn_cancel,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui.tbtn_ok,SIGNAL(clicked()),this,SLOT(close()));

}

void FaultDialog::setTableVal()
{
    QList<CodeNode> codnes = controller->fault_queue.getCodeNodeList();
    const int cod_count = codnes.count();

    int columns=4;
    int rows = cod_count/columns;
    if((cod_count%columns) != 0)
        rows += 1;

    QStandardItemModel* model = new QStandardItemModel(rows,columns);

    QStandardItem* item;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            int idx = i*columns +j;
            if(idx>=cod_count)
                break;
            item = new QStandardItem(codnes[idx].name);
            if(idx==0)
                item->setForeground(QBrush(QColor(Qt::red)));
            model->setItem(i,j,item);
            //ui.tableView->setItem(i,j,item);
        }
    }
    ui.tableView->setModel(model);
}

//画StyleSheet
void FaultDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
