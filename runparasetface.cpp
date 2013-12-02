#include "runparasetface.h"
#include "msgbox.h"
RunParaSetFace::RunParaSetFace(QWidget *parent, MController *mc)
                    : SubMenu(parent,mc)
{
    setTitle("运行设定",":/images/yunxingshezhi.png");
    ui_runset.setupUi(ui.showArea);
    TableInit();

    paraDialog  = new SetParaDialog(this,mc);
    qRegisterMetaType<ParaList>("ParaList");
    connect(controller,SIGNAL(writeDataDone(ParaList,bool)),this,SLOT(writeDoneSlot(ParaList,bool)));
    connect(ui_runset.tbtn_left,SIGNAL(clicked()),this,SLOT(tbtn_left_clicked()));
    connect(ui_runset.tbtn_right,SIGNAL(clicked()),this,SLOT(tbtn_right_clicked()));

    currentPage=2;
    if(totalPage>1)
        ui_runset.tbtn_left->click();
    else
    {
        currentPage=1;

        ui_runset.tbtn_left->hide();
        ui_runset.tbtn_right->hide();

        setTablePageShow(0);
        ui_runset.lab_page->setText(QString("%1/%2").arg(currentPage).arg(totalPage));
    }
}

RunParaSetFace::~RunParaSetFace()
{

}

void RunParaSetFace::TableInit()
{
    itemNames<<PARA::kw_set     <<PARA::kvar_set        <<PARA::pf_set      <<PARA::pf_mode     <<PARA::contro_mode;

    int row = itemNames.count();
    row = row/TABLE_PARA_CLUM;
    int page = row/ONE_PAGE_ROWS;
    if((row%ONE_PAGE_ROWS)>0)
        page++;
    totalPage =  page;
    /*--------------设置表格数据--------------------------------*/
    ui_runset.tableWidget->setRowCount(ONE_PAGE_ROWS);
    ui_runset.tableWidget->setColumnCount(TABLE_PARA_CLUM*2);
    ui_runset.tableWidget->horizontalHeader()->show();
    //当前页面槽
    qRegisterMetaType<ParaList>("ParaList");
    connect(ui_runset.tableWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(tableWidget_clicked(QModelIndex)));

}

void RunParaSetFace::setTablePageShow(int star)
{
    ui_runset.tableWidget->clear();

    QStringList labels;
    labels<<"名称"<<"设置值";
    ui_runset.tableWidget->setHorizontalHeaderLabels(labels);

    QTableWidgetItem* item;
    int count = itemNames.count();
    for(int i=0;i<ONE_PAGE_ROWS;i++)
    {
        for(int j=0;j<TABLE_PARA_CLUM;j++)
        {
            if(star>=count)
                break;
            ParaItem* para = controller->paralist[itemNames[star++]];
            item = new QTableWidgetItem(para->name);
            item->setForeground(QBrush(QColor(Qt::blue)));
            ui_runset.tableWidget->setItem(i,j*2,item);
            ui_runset.tableWidget->bindData(i,j*2+1,para);
        }
    }

    ui_runset.tableWidget->setAllValToTable();
}

void RunParaSetFace::tbtn_left_clicked()
{
    currentPage--;
    if(currentPage==1)
    {
        ui_runset.tbtn_left->hide();
        ui_runset.tbtn_right->show();
    }
    setTablePageShow((currentPage-1)*ONE_PAGE_ROWS);
    ui_runset.lab_page->setText(QString("%1/%2").arg(currentPage).arg(totalPage));
}

void RunParaSetFace::tbtn_right_clicked()
{
    currentPage++;
    if(currentPage==totalPage)
    {
        ui_runset.tbtn_left->show();
        ui_runset.tbtn_right->hide();
    }
    setTablePageShow((currentPage-1)*ONE_PAGE_ROWS);
    ui_runset.lab_page->setText(QString("%1/%2").arg(currentPage).arg(totalPage));
}

//
void RunParaSetFace::tableWidget_clicked(QModelIndex index)
{
    int clum=index.column();
    if((clum==0)||(clum==2))
        return;

    int row = index.row();
    QTableWidgetItem* item_n = ui_runset.tableWidget->item(row,clum-1);
    QString name=item_n->data(Qt::DisplayRole).toString();

    QTableWidgetItem* item = ui_runset.tableWidget->item(row,clum);
    ParaItem* para = ui_runset.tableWidget->getPara(item);

    paraDialog->getPara(name,para);
    paraDialog->show();

}

void RunParaSetFace::writeDoneSlot(ListParaItem list,bool succeed)
{
    if(succeed==true)
    {
        for(int i=0;i<list.count();i++)
        {
            list[i]->values = list[i]->val_w;
            ui_runset.tableWidget->setValToTable(list[i]);
        }
    }
    else
    {
        qDebug()<<"writeError";

        QString str;
        for(int i=0;i<list.count();i++)
        {
            str +=QString("写地址%1值%2失败！\n").arg(list[i]->address).arg(list[i]->val_w);
        }
        MsgBox* msgBox=new MsgBox(this,MsgBox::Critical,str);
        msgBox->show();
    }
}
