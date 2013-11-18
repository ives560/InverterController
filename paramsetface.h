#ifndef PARAMSETFACE_H
#define PARAMSETFACE_H
#include "submenu.h"
#include <QMessageBox>

class paramSetFace : public SubMenu
{
    Q_OBJECT
public:
    paramSetFace(QWidget *parent, MController *mc);

private:
    QLineEdit *ledit_pwd;
private:
    void setupUi();
    void setupPassWordUi();
    void setupParamSetUi();

private:
    bool checkPassWord();

private slots:
    void tbtn_ok_clicked();
    void tbtn_system_clicked();
    void tbtn_run_clicked();
    void tbtn_protect_clicked();
    void tbtn_comm_clicked();
};

#endif // PARAMSETFACE_H
