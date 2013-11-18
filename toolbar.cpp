#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupBackButton();
}

ToolBar::~ToolBar()
{

}
void ToolBar::setupBackButton()
{
	pBtn_back=new QPushButton(this);
	pBtn_back->setGeometry(QRect(660, 0, 50, 50));
	connect(pBtn_back,SIGNAL(clicked()),this,SLOT(pBtn_back_clicked()));
	pBtn_back->hide();
}


void ToolBar::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ToolBar::on_tBtn_power_clicked()
{
	qDebug()<<"on_tBtn_power_clicked";
	emit button_clicked(POWER);
	changeUi(true);
}

void ToolBar::on_tBtn_main_clicked()
{
	qDebug()<<"on_tBtn_main_clicked";
	emit button_clicked(MAIN);
	changeUi(false);
}

void ToolBar::on_tBtn_function_clicked()
{
	qDebug()<<"on_tBtn_function_clicked";
	emit button_clicked(FUNCTION);
	changeUi(true);
}

void ToolBar::pBtn_back_clicked()
{
	qDebug()<<"on_pBtn_back_clicked";
	emit button_clicked(BACK);
}

//切换时钟和返回按钮的显示
void ToolBar::changeUi(bool change)
{
	if(change==true)
	{
		ui.widget_time->hide();
		pBtn_back->show();

	}
	else if(change==false)
	{
		ui.widget_time->show();
		pBtn_back->hide();
	}
}