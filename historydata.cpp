#include "historydata.h"
#include <QTabWidget>
#include <QComboBox>
HistoryData::HistoryData(QWidget *parent,MController* mc)
    :SubMenu(parent,mc)
{
    setupUi();
}
void HistoryData::setupUi()
{
    //用下拉列表选择，日期，功率，电压，电流等
    setTitle("历史记录",":/images/lishijilu.png");
    ui_htydt.setupUi(ui.showArea);
    chartInit();

    QStringList list;
    list = getDateList();
    ui_htydt.cbox_data->addItems(list);
    //ui_htydt.cbox_data->adjustSize();

    //connect(ui_htydt.tbtn_left,SIGNAL(clicked()),this,SLOT(tbtn_left_clicked()));
    //connect(ui_htydt.tbtn_right,SIGNAL(clicked()),this,SLOT(tbtn_right_clicked()));
    connect(ui_htydt.cbox_data,SIGNAL(currentIndexChanged(QString)),this,SLOT(cbox_data_currentIndexChanged(QString)));

    ui_htydt.tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(86,197,255);color: rgb(255, 255, 255);}");
    ui_htydt.tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui_htydt.tableView->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    ui_htydt.cbox_data->setCurrentIndex(-1);
    ui_htydt.cbox_data->setCurrentIndex(0);
}

QStringList HistoryData::getDateList()
{
    QStringList list;
    if(controller->database!=NULL)
    {
        list = controller->database->getTables();
        int i=0;
        while(i<list.count())
        {
            if(list.at(i).length()!=11)
            {
                list.removeAt(i);
                continue;
            }
            QString str = list.at(i);
            str.remove("tb_");
            list.replace(i,str);
            i++;
        }
    }
    return list;
}

QStringList HistoryData::getParaList()
{
    QStringList list;
    list <<"功率"<<"直流电压"<<"直流电流"<<"交流电压"<<"交流电流";
    return list;
}

void HistoryData::removeRepeadItem(QStringList *list,int idex,int len)
{
    QString str;
    QString strl;
    int i=0;
    while(i<list->count())
    {
        if(list->at(i).length()!=10)
        {
            list->removeAt(i);
            continue;
        }
        strl = list->at(i).mid(idex,len);

        if(str==strl)
            list->removeAt(i);
        else
        {
            list->replace(i,str);
            str = strl;
            i++;
        }
    }

}

void HistoryData::tbtn_left_clicked()
{

}

void HistoryData::tbtn_right_clicked()
{

}

void HistoryData::cbox_data_currentIndexChanged(QString text )
{
    qDebug()<<"cbox_data_currentIndexChanged"<<text;

    if(controller->database!=NULL)
    {
        QSqlQueryModel *model = new QSqlQueryModel(ui_htydt.tableView);


        QSqlQuery query = controller->database->readTodayAllParaTable(text);
        model->setQuery(query);
        const int count = controller->database->tb_td_paras.count();
        model->setHeaderData(0,Qt::Horizontal,"时间");
        for(int i=0;i<count;i++)
        {
            int index = controller->database->tb_td_paras[i];
            ParaItem* para = controller->paralist[index];
            QString name = para->name;
            if(para->unit!=NULL)
                name = name + QString("\n(%1)").arg(para->unit);
            model->setHeaderData(i+1,Qt::Horizontal,name);

        }
        ui_htydt.tableView->setModel(model);
    }

}
//曲线图初始化
void HistoryData::chartInit()
{
//    ui_htydt.chart->CoordDataInit();
//    ui_htydt.chart->setAxis(Chart::X,0,24,6,"t");
//    ui_htydt.chart->setAxis(Chart::Y,0,100,5,"E");
//    ui_htydt.chart->paint(true);
}
//更新图表
void HistoryData::chartUpData()
{
//    QSqlQuery query;
//    if(controller->database!=NULL)
//        query= controller->database->readTodayTable("kw");

//    ui_htydt.chart->setQuery(query);
//    ui_htydt.chart->paint(true);
}
