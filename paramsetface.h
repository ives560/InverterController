#ifndef PARAMSETFACE_H
#define PARAMSETFACE_H
#include "submenu.h"
#include <QMessageBox>
#include "ui_password.h"
#include "ui_paraset.h"
class paramSetFace : public SubMenu
{
    Q_OBJECT

private:
    Ui::PassWord ui_pwd;
    Ui::ParaSet ui_paraset;

public:
    paramSetFace(QWidget *parent, MController *mc);

private:
    void setupUi();
    void setupPassWordUi();
    void setupParaSetUi();
    bool checkPassWord();

private slots:
    void tbtn_ok_clicked();
    void tbtn_system_clicked();
    void tbtn_run_clicked();
    void tbtn_protect_clicked();
    void tbtn_comm_clicked();
};

#endif // PARAMSETFACE_H
