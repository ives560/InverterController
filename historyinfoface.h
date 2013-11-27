#ifndef HISTORYINFOFACE_H
#define HISTORYINFOFACE_H

#include "submenu.h"
#include "ui_historyinfo.h"
class HistoryInfoFace : public SubMenu
{
    Q_OBJECT

public:
    HistoryInfoFace(QWidget *parent=0,MController *mc=0);

private:
    void setupUi();

private:
    Ui::HistoryInfo ui_history;

public slots:
    void tbtn_event_Clicked();
    void tbtn_fault_Clicked();
    void tbtn_record_Clicked();


};

#endif // HISTORYINFOFACE_H
