#include "language.h"

Language::Language(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    ui_lange.setupUi(ui.showArea);
}
