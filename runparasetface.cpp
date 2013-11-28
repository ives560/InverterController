#include "runparasetface.h"

RunParaSetFace::RunParaSetFace(QWidget *parent, MController *mc)
                    : SubMenu(parent,mc)
{
    setupUi();
    bindData();
    paraDialog  = new SetParaDialog(this,mc);
    qRegisterMetaType<ParaList>("ParaList");
    connect(controller,SIGNAL(writeDataDone(ParaList,bool)),this,SLOT(writeDoneSlot(ParaList,bool)));

}

void RunParaSetFace::setupUi()
{
    setTitle("运行设定",":/images/yunxingshezhi.png");
    QString clumNames[]={"输出功率上限","输出无功设置","功率因数设置","无功控制模式选择","控制方式"};

    tableWidget=new ParaTableWidget(ui.showArea);

    tableWidget->setObjectName("runParaSet");
    tableWidget->setGeometry(200,20,200*2,260);

    /*--------------设置表格数据--------------------------------*/
    tableWidget->setRowCount(5);
    tableWidget->setColumnCount(2);
    QStringList labels;
    labels<<"名称"<<"设置值";
    tableWidget->setHorizontalHeaderLabels(labels);
    tableWidget->horizontalHeader()->show();
    QTableWidgetItem* item;
    for(int i=0;i<tableWidget->rowCount();i++)
    {
        item = new QTableWidgetItem(clumNames[i]);
        item->setForeground(QBrush(QColor(Qt::blue)));
        tableWidget->setItem(i,0,item);
    }

    //当前页面槽
    qRegisterMetaType<ParaList>("ParaList");
    connect(tableWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(tableWidget_clicked(QModelIndex)));
//    connect(controller,SIGNAL(writeDataDone(ParaList,bool)),tableWidget,SLOT(writeDoneSlot(ParaList,bool)));

}

void RunParaSetFace::bindData()
{
    int clum[5]={PARA::kw_set,       PARA::kvar_set,     PARA::pf_set,
                PARA::pf_mode,      PARA::contro_mode};

    for(int i=0;i<tableWidget->rowCount();i++)
    {
        tableWidget->bindData(i,1,controller->paralist[clum[i]]);
    }
    tableWidget->setAllValToTable();
}

//
void RunParaSetFace::tableWidget_clicked(QModelIndex index)
{
    int clum=index.column();
    if((clum==0)||(clum==2))
        return;

    int row = index.row();
    QTableWidgetItem* item_n = tableWidget->item(row,clum-1);
    QString name=item_n->data(Qt::DisplayRole).toString();

    QTableWidgetItem* item = tableWidget->item(row,clum);
    ParaItem* para = tableWidget->getPara(item);

    paraDialog->getPara(name,para);
    paraDialog->show();


//    QMessageBox msg;
//    msg.setText("确定修改参数!");
//    msg.setIcon(QMessageBox::Warning);
//    msg.exec();
}

void RunParaSetFace::writeDoneSlot(ListParaItem list,bool succeed)
{
    if(succeed==true)
    {
        for(int i=0;i<list.count();i++)
        {
            list[i]->values = list[i]->val_w;
            tableWidget->setValToTable(list[i]);
        }
    }
    else
    {
        qDebug()<<"writeError";
        QMessageBox* msgBox=new QMessageBox(this);
        QString str;
        for(int i=0;i<list.count();i++)
        {
            str +=QString("写地址%1值%2失败！\n").arg(list[i]->address).arg(list[i]->val_w);
        }
        msgBox->setText(str);
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setStandardButtons( QMessageBox::Ok);
        msgBox->show();
    }
}
