#ifndef RUNPARASETFACE_H
#define RUNPARASETFACE_H
#include "submenu.h"
#include "setparadialog.h"
#include "paratablewidget.h"

class RunParaSetFace : public SubMenu
{
        Q_OBJECT
public:
    RunParaSetFace(QWidget *parent,MController* mc);
    void setupUi();
    void TableInit();
    void bindData();

private:
    ParaTableWidget* tableWidget;
    SetParaDialog* paraDialog;


private slots:
    void tableWidget_clicked(QModelIndex);
    void writeDoneSlot(ListParaItem,bool);

};

#endif // RUNPARASETFACE_H
