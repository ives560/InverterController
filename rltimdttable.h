#ifndef RLTIMDTTABLE_H
#define RLTIMDTTABLE_H

#include <QWidget>
#include "mcontroller.h"
#include "paratablewidget.h"
#include <QTableWidget>
namespace Ui {
class RlTimDtTable;
}

class RlTimDtTable : public QWidget
{
    Q_OBJECT
    
public:
    explicit RlTimDtTable(QWidget *parent, MController *mc);
    ~RlTimDtTable();

private:
   void TableInit();
   void bindTableData();
private:
    Ui::RlTimDtTable *ui;
    MController* controller;
    ParaTableWidget* table1;
    ParaTableWidget* table2;

};

#endif // RLTIMDTTABLE_H
