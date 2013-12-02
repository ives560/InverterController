#ifndef RUNPARASETFACE_H
#define RUNPARASETFACE_H
#include "submenu.h"
#include "setparadialog.h"
#include "paratablewidget.h"
#include "ui_runparaset.h"

#define ONE_PAGE_ROWS          5
#define TABLE_PARA_CLUM        1

class RunParaSetFace : public SubMenu
{
        Q_OBJECT
private:
    Ui::RunParaSet ui_runset;
   // ParaTableWidget* tableWidget;
    SetParaDialog* paraDialog;
    QList<int> itemNames;
    int currentPage;
    int totalPage;

public:
    RunParaSetFace(QWidget *parent,MController* mc);
    ~RunParaSetFace();
    void TableInit();
    void setTablePageShow(int star);

private slots:
    void tableWidget_clicked(QModelIndex);
    void writeDoneSlot(ListParaItem,bool);
    void tbtn_left_clicked();
    void tbtn_right_clicked();

};

#endif // RUNPARASETFACE_H
