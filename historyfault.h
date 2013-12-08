#ifndef HISTORYFAULT_H
#define HISTORYFAULT_H
#include "submenu.h"
#include "ui_historyfault.h"

#define ONE_PAGE_ROWS          5
#define TABLE_PARA_CLUM        1

class HistoryFault : public SubMenu
{
    Q_OBJECT
public:
    HistoryFault(QWidget *parent,MController* mc);
    void tableViewInit();
    void setTablePageShow(int star);
private:
    Ui::HistoryFault ui_hstyflt;
    QTableView* tableView;
    QStandardItemModel* model;
    int currentPage;
    int totalPage;

private slots:
    void tbtn_left_clicked();
    void tbtn_right_clicked();
};

#endif // HISTORYFAULT_H
