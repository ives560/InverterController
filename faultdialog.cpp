#include "faultdialog.h"
#include <QHeaderView>
#include "operafile.h"

FaultDialog::FaultDialog(QWidget *parent)
    :QDialog(parent,Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint)
{
    setupUi();

}

void FaultDialog::setupUi()
{
    resize(650,350);
    setStyleSheet("background:rgb(85, 85, 255)");
    /*--------------------------------------------*/
    tableInit();
    setTableVal();
    /*-------------------*/
    lab_fault = new QLabel(this);
    lab_fault->setObjectName("lab_fault");
    lab_fault->setGeometry(0,0,32,32);
    lab_fault->setScaledContents(true);
    lab_fault->setPixmap(QPixmap(QString::fromUtf8(":/images/guzhangzhuizhong.png")));
    /*--------------*/
    pbtn_ok = new QPushButton(this);
    pbtn_ok->setObjectName("pbtn_ok");
    pbtn_ok->setGeometry(300,300,100,25);
    pbtn_ok->setText("确定");
    pbtn_ok->setStyleSheet("");
    connect(pbtn_ok,SIGNAL(clicked()),this,SLOT(close()));

}

void FaultDialog::tableInit()
{
    tableWidget = new QTableWidget(this);
    /*--------------设置表格属性--------------------------------*/
    tableWidget->setGeometry(32,32,3*190,8*30);
    tableWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);//固定行高列宽

    tableWidget->setFocusPolicy(Qt::NoFocus);//不获得焦点，单击后没有虚线边框
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);//单击后单元格不变灰
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//单元格只读

    tableWidget->horizontalHeader()->hide();
    tableWidget->verticalHeader()->hide();//隐藏行标题列标题

    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
}

void FaultDialog::setTableVal()
{
    QList<QString> names = getFaultNames();
    int columns=3;
    int rows = names.count()/columns;
    if((names.count()%columns) != 0)
        rows += 1;

    tableWidget->setRowCount(rows);
    tableWidget->setColumnCount(columns);
    QTableWidgetItem* item;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            int idx = i*columns +j;
            if(idx>=names.count())
                break;
            item = new QTableWidgetItem(names[idx]);
            if(idx==0)
                item->setForeground(QBrush(QColor(Qt::red)));
            tableWidget->setItem(i,j,item);
        }
    }
}

QList<QString> FaultDialog::getFaultNames()
{
    QList<QString> names;
    OperaFile file(":/Resources/fault.xml");
    QDomNodeList nodes = file.getNodeList();
    if(nodes.isEmpty()== true)
        return names;

    for(int i=0;i<nodes.count();i++)
    {
        QDomNodeList fault=nodes.at(i).childNodes();
        for(int j=0;j<fault.count();j++)
        {
            QString str = fault.at(j).toElement().tagName();
            if(str == "name")
            {
                str = fault.at(j).toElement().text();
                names.append(str);
                break;
            }
        }
    }
    return names;
}
