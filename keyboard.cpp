#include "keyboard.h"

KeyBoard::KeyBoard(QWidget *parent)
    : QDialog(parent,Qt::Tool|Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint),
      lastFocusedWidget(0)
{
	ui.setupUi(this);
    this->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_0->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_1->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_2->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_3->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_4->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_5->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_6->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_7->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_8->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_9->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_ce->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_dot->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_enter->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_esc->setFocusPolicy(Qt::NoFocus);
    ui.pushButton_line->setFocusPolicy(Qt::NoFocus);

    setAttribute(Qt::WA_ShowWithoutActivating,true);

    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(saveFocusWidget(QWidget*,QWidget*)));

	singnalMapperInit();

}

KeyBoard::~KeyBoard()
{

}
//虚拟键盘单击槽
void KeyBoard::keyClicked(int key)
{
    emit characterGenerated(key);
}

bool KeyBoard::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::WindowActivate:
        if (lastFocusedWidget)
            lastFocusedWidget->activateWindow();

        break;
    default:
        break;
    }

    return QWidget::event(e);
}

void KeyBoard::saveFocusWidget(QWidget * /*oldFocus*/, QWidget *newFocus)
{
    if (newFocus != 0 && !this->isAncestorOf(newFocus)) {
        lastFocusedWidget = newFocus;
    }
}

void KeyBoard::mousePressEvent(QMouseEvent *event)
{

}

void KeyBoard::singnalMapperInit()
{
	mapper=new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(keyClicked(int)));

    mapper->setMapping(ui.pushButton_0,Qt::Key_0);
	connect(ui.pushButton_0,SIGNAL(clicked()),mapper,SLOT(map()));//0
    mapper->setMapping(ui.pushButton_1,Qt::Key_1);
	connect(ui.pushButton_1,SIGNAL(clicked()),mapper,SLOT(map()));//1
    mapper->setMapping(ui.pushButton_2,Qt::Key_2);
	connect(ui.pushButton_2,SIGNAL(clicked()),mapper,SLOT(map()));//2
    mapper->setMapping(ui.pushButton_3,Qt::Key_3);
	connect(ui.pushButton_3,SIGNAL(clicked()),mapper,SLOT(map()));//3
    mapper->setMapping(ui.pushButton_4,Qt::Key_4);
	connect(ui.pushButton_4,SIGNAL(clicked()),mapper,SLOT(map()));//4
    mapper->setMapping(ui.pushButton_5,Qt::Key_5);
	connect(ui.pushButton_5,SIGNAL(clicked()),mapper,SLOT(map()));//5
    mapper->setMapping(ui.pushButton_6,Qt::Key_6);
	connect(ui.pushButton_6,SIGNAL(clicked()),mapper,SLOT(map()));//6
    mapper->setMapping(ui.pushButton_7,Qt::Key_7);
	connect(ui.pushButton_7,SIGNAL(clicked()),mapper,SLOT(map()));//7
    mapper->setMapping(ui.pushButton_8,Qt::Key_8);
	connect(ui.pushButton_8,SIGNAL(clicked()),mapper,SLOT(map()));//8
    mapper->setMapping(ui.pushButton_9,Qt::Key_9);
	connect(ui.pushButton_9,SIGNAL(clicked()),mapper,SLOT(map()));//9
    mapper->setMapping(ui.pushButton_dot,Qt::Key_Period);
    connect(ui.pushButton_dot,SIGNAL(clicked()),mapper,SLOT(map()));//.
    mapper->setMapping(ui.pushButton_line,Qt::Key_Minus);
	connect(ui.pushButton_line,SIGNAL(clicked()),mapper,SLOT(map()));//-
    mapper->setMapping(ui.pushButton_ce,Qt::Key_Backspace);
    connect(ui.pushButton_ce,SIGNAL(clicked()),mapper,SLOT(map()));//CE
    mapper->setMapping(ui.pushButton_esc,Qt::Key_Escape);
	connect(ui.pushButton_esc,SIGNAL(clicked()),mapper,SLOT(map()));//ESC
    mapper->setMapping(ui.pushButton_enter,Qt::Key_Enter);
	connect(ui.pushButton_enter,SIGNAL(clicked()),mapper,SLOT(map()));//ENTER
}
