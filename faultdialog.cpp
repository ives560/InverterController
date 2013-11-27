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
    //setStyleSheet("QDialog{background:transparent;image: url(:/images/faultbeijing.png);}");
    setStyleSheet("QDialog{background:rgb(86,197,255);}");
    /*--------------------------------------------*/
    tableInit();
    setTableVal();
    /*--------------------*/
    lb_title = new QLabel(this);
    lb_title->setObjectName("lb_title");
    lb_title->setGeometry(300,10,100,50);
    lb_title->setText("故障信息");
    lb_title->setStyleSheet("color:red;font:bold;font-size:15px;");
    /*--------------*/

    tbtn_cancel = new QToolButton(this);
    tbtn_cancel->setObjectName(QString::fromUtf8("tbtn_cancel"));
    tbtn_cancel->setGeometry(QRect(200, 300, 100, 50));
    tbtn_cancel->setText("关闭");
    tbtn_cancel->setStyleSheet(QString::fromUtf8("background:transparent;"));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/error.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbtn_cancel->setIcon(icon);
    tbtn_cancel->setIconSize(QSize(50, 50));
    tbtn_cancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(tbtn_cancel,SIGNAL(clicked()),this,SLOT(close()));
    /*--------------*/
    tbtn_ok = new QToolButton(this);
    tbtn_ok->setObjectName("tbtn_ok");
    tbtn_ok->setGeometry(400,300,100,50);
    tbtn_ok->setText("确定");
    tbtn_ok->setStyleSheet("background:transparent;");
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/images/okbutton.png"), QSize(), QIcon::Normal, QIcon::Off);
    tbtn_ok->setIcon(icon1);
    tbtn_ok->setIconSize(QSize(50, 50));
    tbtn_ok->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(tbtn_ok,SIGNAL(clicked()),this,SLOT(close()));

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

//画StyleSheet
void FaultDialog::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
