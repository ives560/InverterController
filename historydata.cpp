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
    ui_htydt.cbox_data->adjustSize();

    list = getParaList();
    ui_htydt.cbox_para->addItems(list);
    //ui_htydt.cbox_para->adjustSize();

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
//曲线图初始化
void HistoryData::chartInit()
{
    ui_htydt.chart->CoordDataInit();
    ui_htydt.chart->setAxis(Chart::X,0,24,6,"t");
    ui_htydt.chart->setAxis(Chart::Y,0,100,5,"E");
    ui_htydt.chart->paint(true);
}
//更新图表
void HistoryData::chartUpData()
{
    QSqlQuery query;
    if(controller->database!=NULL)
        query= controller->database->readTodayTable("kw");

    ui_htydt.chart->setQuery(query);
    ui_htydt.chart->paint(true);
}
