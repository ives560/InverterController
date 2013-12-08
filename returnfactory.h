#ifndef RETURNFACTORY_H
#define RETURNFACTORY_H

#include "submenu.h"
#include "ui_returnfactory.h"

class ReturnFactory : public SubMenu
{

private:
    Ui::ReturnFactory ui_rtfty;

public:
    ReturnFactory(QWidget *parent, MController *mc);

private slots:
    void  tbtn_fault_clicked();
    void tbtn_power_clicked();
    void tbtn_run_clicked();

};

#endif // RETURNFACTORY_H
