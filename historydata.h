#ifndef HISTORYDATA_H
#define HISTORYDATA_H
#include "submenu.h"
#include "ui_historydata.h"
class HistoryData : public SubMenu
{
public:
    HistoryData(QWidget *parent=0,MController* mc=0);
    void setupUi();

private:
    Ui::HistoryData ui_htydt;
private:
    void removeRepeadItem(QStringList *list,int idex,int len);
    QStringList getDateList();
    QStringList getParaList();
    void chartInit();
    void chartUpData();

};

#endif // HISTORYDATA_H
