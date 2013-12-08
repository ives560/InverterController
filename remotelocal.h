#ifndef REMOTELOCAL_H
#define REMOTELOCAL_H
#include "submenu.h"
#include "ui_remotelocal.h"

class RemoteLocal : public SubMenu
{
    Q_OBJECT

private:
    Ui::RemoteLocal ui_remtl;

public:
    RemoteLocal(QWidget *parent, MController *mc);

private:
    void comboBoxInit();

private slots:
    void comboBox_currentIndexChanged(QString text);
};

#endif // REMOTELOCAL_H
