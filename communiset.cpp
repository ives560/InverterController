#include "communiset.h"

CommuniSet::CommuniSet(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    ui_comset.setupUi(ui.showArea);
}
