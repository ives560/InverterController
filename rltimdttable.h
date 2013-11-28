#ifndef RLTIMDTTABLE_H
#define RLTIMDTTABLE_H

#include <QWidget>
#include "mcontroller.h"
#include "paramodel.h"

namespace Ui {
class RlTimDtTable;
}

class RlTimDtTable : public QWidget
{
    Q_OBJECT
    
private:
    Ui::RlTimDtTable *ui;
    MController* controller;
    ParaModel* model_realtime;
    int currentPage;
    QList<int> itemNames;
    QList<int> nextItemNames;

public:
    explicit RlTimDtTable(QWidget *parent, MController *mc);
    ~RlTimDtTable();

private:
   void TableInit();
   void itemNamesInit();
   void setTablePageShow(int star, int rows);

private slots:
   void tbtn_left_clicked();
   void tbtn_right_clicked();

};

#endif // RLTIMDTTABLE_H
