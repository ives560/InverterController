#include "invertercontroller.h"
#include "submenu.h"
#include "mainface.h"
#include "functiontable.h"
#include "powerface.h"
#include "language.h"

InverterController::InverterController(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
    ui.setupUi(this);
    //controller=NULL;
    controller=new MController();
    connect(controller, SIGNAL(readFastDataDone()),this, SLOT(readFastDataSlot()));
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

void InverterController::readFastDataSlot()
{
    int state = controller->paralist[PARA::op_state]->values;
    int led = controller->paralist[PARA::digi_out1]->values;
   // qDebug()<<"readFastDataSlot:"<<"op_state:"<<state<<"digi_out1:"<<led;

    ui.wgt_led->setLedState(led);
    ui.wgt_led->setStateText(state);
}

void InverterController::load_mainface()
{
    layout = ui.verticalLayout;

    MainFace* mainface=new MainFace(this,controller);
    mainface->setObjectName("mainface");
    layout->addWidget(mainface);
}

void InverterController::setupBackButton()
{
//    tBtn_back=new QToolButton(this);
//    //tBtn_back->setStyleSheet("border-image: url(:/images/fanhui.png)");
//    tBtn_back->setGeometry(QRect(700, 0, 100, 80));
//    tBtn_back->setFocusPolicy(Qt::StrongFocus);
    connect(ui.tBtn_back,SIGNAL(clicked()),this,SLOT(pBtn_back_clicked()));
//    tBtn_back->hide();
}

//切换时钟和返回按钮的显示
void InverterController::changeUi(bool change)
{
    if(change==true)
    {
        ui.tBtn_back->setText("返回上层");
    }
    else if(change==false)
    {
        ui.tBtn_back->setText("语言选择");
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

    if(layout->itemAt(0)->widget()->objectName()!="mainface")
    {
        changeUi(false);
        removeAllInterface();
        MainFace* mainface=new MainFace(this,controller);
        mainface->setObjectName("mainface");
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
    if(layout->itemAt(0)->widget()->objectName()!="mainface")
    {
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
            layout->addWidget(mainface);
        }
    }
    else//语言切换界面
    {
        changeUi(true);
        removeAllInterface();
        Language* lge = new Language(this,controller);
        lge->setObjectName("language");
        layout->addWidget(lge);
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

//画StyleSheet
void InverterController::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
