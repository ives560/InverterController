#include "remotelocal.h"

RemoteLocal::RemoteLocal(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    setTitle("现场/远程控制设定",":/images/yuanchengshezhi.png");
    ui_remtl.setupUi(ui.showArea);
    comboBoxInit();
}

void RemoteLocal::comboBoxInit()
{
    connect(ui_remtl.comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(comboBox_currentIndexChanged(QString)));
    ui_remtl.comboBox->insertItem(0,"本地");
    ui_remtl.comboBox->insertItem(1,"远程");
    ui_remtl.comboBox->setCurrentIndex(0);
}

void RemoteLocal::comboBox_currentIndexChanged(QString text)
{

}
