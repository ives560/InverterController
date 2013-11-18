#include "invertercontroller.h"
#include "mainface.h"
#include "functiontable.h"
#include "powerface.h"

InverterController::InverterController(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
    ui.setupUi(this);
    //controller=NULL;
    controller=new MController();
    //connect(controller, SIGNAL(enReadData()),this, SIGNAL(enReadData()));

    //this->showFullScreen();
    setWindowFlags(Qt::FramelessWindowHint);
    move(0,0);
    load_mainface();
    setupBackButton();
}

InverterController::~InverterController()
{
    if(controller!=NULL)
        controller->deleteLater();
}

void InverterController::load_mainface()
{
    layout = ui.verticalLayout;

    MainFace* mainface=new MainFace((QWidget*)this,controller);
    mainface->setObjectName("mainface");
    mainface->setStyleSheet("#mainface{border-image: url(:/images/mainpic.png);}");
    layout->addWidget(mainface);
}

void InverterController::toolBar_Buttons_Clickde(int button)
{
	qDebug()<<"toolBar_Buttons_Clickde"<<button;

	//FunctionTable* table;
	//switch(button)
	//{
	//	case ToolBar::POWER:
	//		break;
	//	case ToolBar::MAIN:
	//		layout->itemAt(0)->widget()->close();
	//		mainface->show();
	//		break;
	//	case ToolBar::FUNCTION:
	//		mainface->close();
	//		table=new FunctionTable(this);
	//		layout->addWidget(table);
	//		break;
	//	case ToolBar::BACK:
	//		break;
	//}
}

void InverterController::setupBackButton()
{
    tBtn_back=new QToolButton(ui.widget);
    tBtn_back->setStyleSheet("border-image: url(:/images/fanhui.png)");
    tBtn_back->setGeometry(QRect(700, 0, 100, 80));
    tBtn_back->setFocusPolicy(Qt::StrongFocus);
    connect(tBtn_back,SIGNAL(clicked()),this,SLOT(pBtn_back_clicked()));
    tBtn_back->hide();
}

//切换时钟和返回按钮的显示
void InverterController::changeUi(bool change)
{
    if(change==true)
    {
        ui.widget_time->hide();
        tBtn_back->show();

    }
    else if(change==false)
    {
        ui.widget_time->show();
        tBtn_back->hide();
    }
}
//开关机按钮单击槽
void InverterController::on_tBtn_power_clicked()
{
	qDebug()<<"on_tBtn_power_clicked";

	if(layout->itemAt(0)->widget()->objectName()!="power")
	{
        PowerFace* power=new PowerFace(this,controller);
		power->setObjectName("power");
        if(power->isready==true)
        {
            changeUi(true);
            removeAllInterface();
            layout->addWidget(power);
            qDebug()<<"new PowerFace";
        }
        else
            power->deleteLater();
	}
}
//主页面按钮单击槽
void InverterController::on_tBtn_main_clicked()
{
    qDebug()<<"on_tBtn_main_clicked";
    //controller->runGetAlwaysData();
    if(layout->itemAt(0)->widget()->objectName()!="mainface")
    {
        changeUi(false);
        removeAllInterface();
        MainFace* mainface=new MainFace(this,controller);
        mainface->setObjectName("mainface");
        mainface->setStyleSheet("#mainface{border-image: url(:/images/mainpic.png);}");
        layout->addWidget(mainface);
        qDebug()<<"new MainFace";
    }

}
//功能表按钮单击槽
void InverterController::on_tBtn_function_clicked()
{
	qDebug()<<"on_tBtn_function_clicked";

	if(layout->itemAt(0)->widget()->objectName()!="table")
	{
        changeUi(true);
		removeAllInterface();
        FunctionTable* table=new FunctionTable(this,controller);
		table->setObjectName("table");
		layout->addWidget(table);
		qDebug()<<"new FunctionTable";
	}
}
//返回按钮单击槽,返回上一个界面
void InverterController::pBtn_back_clicked()
{
	qDebug()<<"on_pBtn_back_clicked";
	SubMenu* w= (SubMenu*)layout->itemAt(0)->widget();
	layout->removeWidget(w);
	w->deleteLater();
	if(w->lastOne!=NULL)
	{
		layout->addWidget(w->lastOne);
		w->lastOne->show();	
	}
	else
	{
		changeUi(false);
        MainFace* mainface=new MainFace(this,controller);
		mainface->setObjectName("mainface");
        mainface->setStyleSheet("#mainface{border-image: url(:/images/mainpic.png);}");
		layout->addWidget(mainface);
	}
}

//隐藏顶层界面
void InverterController::hideTopInterface()
{
	QWidget* w= layout->itemAt(0)->widget();
	layout->removeWidget(w);
	w->hide();
}

//添加新界面到顶层
void InverterController::addTopInterface(QWidget* w)
{
	if(layout->count()>0)
	{
		QWidget* odw= layout->itemAt(0)->widget();
		layout->removeWidget(odw);
		odw->hide();
	}
	layout->addWidget(w);
}
//删除所有页面
void InverterController::removeAllInterface()
{
    QString name;
	if(layout->count()>0)
	{
        name=layout->itemAt(0)->widget()->objectName();
        if(name!="mainface")
		{
			SubMenu* w= (SubMenu*)layout->itemAt(0)->widget();
			layout->removeWidget(w);
            removeWidget(w);
		}
		else
		{
			QWidget* w=layout->itemAt(0)->widget();
            layout->removeWidget(w);
            w->deleteLater();
		}

	}
}
//递归删除所有创建的页面
void InverterController::removeWidget(SubMenu* sub)
{
    if(sub->lastOne!=NULL)
		removeWidget(sub->lastOne);
    sub->deleteLater();
}
