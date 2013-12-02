#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "submenu.h"
#include "ui_language.h"

class Language : public SubMenu
{
public:
    Language(QWidget *parent, MController *mc);

private:
    Ui::Language ui_lange;
};

#endif // LANGUAGE_H
