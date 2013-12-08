#ifndef SYSTEMPARAFACE_H
#define SYSTEMPARAFACE_H

#include "submenu.h"
#include "ui_systempara.h"
class SystemParaFace : public SubMenu
{
    Q_OBJECT

private:
    Ui::SystemPara ui_system;

public:
    SystemParaFace(QWidget *parent,MController* mc);
    void setupUi();
private slots:
    void tbtn_language_clicked();
    void tbtn_clock_clicked();
    void tbtn_revise_clicked();
    void tbtn_restore_clicked();
    void tbtn_remote_clicked();

};

#endif // SYSTEMPARAFACE_H
