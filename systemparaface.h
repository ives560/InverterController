#ifndef SYSTEMPARAFACE_H
#define SYSTEMPARAFACE_H

#include "submenu.h"

class SystemParaFace : public SubMenu
{
    Q_OBJECT

public:
    SystemParaFace(QWidget *parent,MController* mc);
    void setupUi();
private slots:
    void tbtn_language_clicked();
    void tbtn_clock_clicked();
    void tbtn_protect_clicked();
    void tbtn_comm_clicked();

};

#endif // SYSTEMPARAFACE_H
