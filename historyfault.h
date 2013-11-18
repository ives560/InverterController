#ifndef HISTORYFAULT_H
#define HISTORYFAULT_H
#include "submenu.h"
class HistoryFault : public SubMenu
{
public:
    HistoryFault(QWidget *parent,MController* mc);
    void setupUi();
    void sqlTableModelInit();
    void tableViewInit();

private:
    QTableView* tableView;
    QSqlTableModel* model;
};

#endif // HISTORYFAULT_H
