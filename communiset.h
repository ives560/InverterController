#ifndef COMMUNISET_H
#define COMMUNISET_H

#include "submenu.h"
#include "ui_communiset.h"

class CommuniSet : public SubMenu
{
public:
    CommuniSet(QWidget *parent, MController *mc);

private:
    Ui::CommuniSet ui_comset;
};

#endif // COMMUNISET_H
