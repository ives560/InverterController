#ifndef RUNINFOFACE_H
#define RUNINFOFACE_H

#include "submenu.h"
#include "chart.h"
#include "paratablewidget.h"
#include "rltimdttable.h"
#include "ui_runinfo.h"
class RunInfoFace : public SubMenu
{
	Q_OBJECT

private:
    Ui::RunInfo ui_runinfo;

private:
    enum Pages{None,RealTime,PowerNet,PowerCln};
    Pages page;
    QPushButton* pbtn_realTime;
    QPushButton* pbtn_powerNet;
    QPushButton* pbtn_powerColumn;
    ParaTableWidget* tableWidget;
    Chart* chartWidget;
    RlTimDtTable* realtimePage;

public:
    RunInfoFace(QWidget *parent,MController* mc);
	~RunInfoFace();

private:
    void setupUi();
    void showRealTimePage(QWidget *widget);
    void showPowerNetPage();
    void powerNetInit();
    void chartUpData();
    void setFastReadType(bool en);

public slots:
    void realTime_clicked();
    void powerNet_clicked();
    void powerColumn_clicked();
	
    void readDataDone();
};

#endif // RUNINFOFACE_H
