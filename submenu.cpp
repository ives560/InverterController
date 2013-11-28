#include "submenu.h"

SubMenu::SubMenu(QWidget *parent, MController *mc)
	: QWidget(parent)
{
	ui.setupUi(this);
    isready=false;
	lastOne=NULL;
    controller=mc;
	inverter=(InverterController*)parent;
    show_width=ui.showArea->width();
    show_height=ui.showArea->height();
}

SubMenu::~SubMenu()
{

}
//设在快速读取
void SubMenu::setReadType(int* names,int len,int type,bool en)
{
    ParaInfo* para;
    for(int i=0;i<len;i++)
    {
        para = controller->paraArray[names[i]];
        if(para!=NULL)
        {
            if(en == true)
                ParaInfo::seType(para,type);
            else
                ParaInfo::clearType(para,type);
        }
    }
}
void SubMenu::setTitle(QString text,QString pathIco)
{
    ui.label_title->setText(text);

    ui.label_icon->setPixmap(QPixmap(pathIco));
}

void SubMenu::setWidgetChildren(QWidget* widget, bool en)
{
    QObjectList list= widget->children();
    QWidget* wgt;
    for(int i=0;i<list.count();i++)
    {
        wgt = (QWidget*)list.at(i);
        if(en==false)
            wgt->deleteLater();
        else if(en==true)
            wgt->show();
    }
}

void SubMenu::setupMenuButton(QToolButton *button, QString text,
                              QPoint point,QString iconPath)
{
    setupButton(button,text,QRect(point.x(),point.y(),100,100),iconPath,
                QSize(60, 60),Qt::ToolButtonTextUnderIcon);
}

void SubMenu::setupChooseButton(QToolButton *button, QString text,
                                QPoint point,QString iconPath)
{
    setupButton(button,text,QRect(point.x(),point.y(),100,50),iconPath,
                QSize(50, 50),Qt::ToolButtonTextBesideIcon);

}

void SubMenu::setupButton(QToolButton *button, QString text, QRect rect, QString iconPath,
                              QSize iconSize ,Qt::ToolButtonStyle style)
{
    button->setStyleSheet("background:transparent;color:white;font-Weight:bold;");
    button->setText(text);
    button->setGeometry(rect);
    button->setFocusPolicy(Qt::StrongFocus);
    button->setToolButtonStyle(style);

    QIcon icon;
    icon.addFile(iconPath, QSize(), QIcon::Normal, QIcon::Off);
    button->setIcon(icon);
    button->setIconSize(iconSize);
    button->show();
}

