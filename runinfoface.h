#ifndef RUNINFOFACE_H
#define RUNINFOFACE_H

#include "submenu.h"
#include "chart.h"
#include "paratablewidget.h"
#include "rltimdttable.h"
class RunInfoFace : public SubMenu
{
	Q_OBJECT

public:
    RunInfoFace(QWidget *parent,MController* mc);
	~RunInfoFace();

private:
    void setupUi();
    void setupButton(QPushButton *button,QString text,int x,int y,
                     QString iconPath,const char* member);
    void showRealTimePage();
    void showPowerNetPage();
    void powerNetInit();
    void chartUpData();
    void setFastReadType(bool en);

private:
    enum Pages{RealTime,PowerNet,PowerCln};
    int page;
	QPushButton* pbtn_realTime;
	QPushButton* pbtn_powerNet;
	QPushButton* pbtn_powerColumn;
    ParaTableWidget* tableWidget;
    Chart* chartWidget;
    RlTimDtTable* realtimePage;

public slots:
    void realTime_clicked();
    void powerNet_clicked();
    void powerColumn_clicked();
	
    void readDataDone();
};

#endif // RUNINFOFACE_H
