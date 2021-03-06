#include "electricitychart.h"
#include "ui_electricitychart.h"

ElectricityChart::ElectricityChart(QWidget *parent, MController *mc) :
    QWidget(parent),
    ui(new Ui::ElectricityChart)
{
    ui->setupUi(this);
    controller = mc;
    ui->colmchart->CoordDataInit();
    ui->colmchart->setAxis(ColumChart::X,0,31,31,"");
    ui->colmchart->setAxis(ColumChart::Y,0,100,5,"E");
    ui->colmchart->show();
    ui->colmchart->paint(true);
    chartUpData();
    totleUpData();

    QDate date = QDate::currentDate();
    ui->lab_date->setText(date.toString("yyyy-MM"));
}

ElectricityChart::~ElectricityChart()
{
    delete ui;
}

//更新图表
void ElectricityChart::chartUpData()
{
    QSqlQuery query;
    if(controller->database!=NULL)
    {
        QDate date =QDate::currentDate();
        date.setDate(date.year(),date.month(),1);
        query= controller->database->readMonthTable(date);
    }

    ui->colmchart->setQuery(query);
    ui->colmchart->paint(true);
}

void ElectricityChart::totleUpData()
{
    double totle = controller->paralist.countTotal(PARA::Gwh_nv,PARA::Mwh_nv,PARA::kwh_nv);
    QString unit = controller->paralist[PARA::Mwh_nv]->unit;
    QString text = QString("%1%2").arg(totle,0, 'f', 3).arg(unit);
    ui->lab_total->setText(text);
    ui->lab_total->adjustSize();
}
