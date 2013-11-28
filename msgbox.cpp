#include "msgbox.h"
#include "ui_msgbox.h"

MsgBox::MsgBox(QWidget *parent,Icon icon,QString text) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::MsgBox)
{
    ui->setupUi(this);
    switchIcon(icon);
    setText(text);
    connect(ui->tbtn_ok,SIGNAL(clicked()),this,SLOT(ok_button_clicked()));
    connect(ui->tbtn_cancel,SIGNAL(clicked()),this,SLOT(cancel_button_clicked()));
}

MsgBox::~MsgBox()
{
    delete ui;
}

void MsgBox::switchIcon(Icon icon)
{
    switch(icon)
    {
        case Question:
            {
                setQuestionIcon();
            }
            break;
        case Critical:
            {
                setCriticalIcon();
            }
            break;
    }
}

void MsgBox::setQuestionIcon()
{
    ui->lab_icon->setStyleSheet(QString::fromUtf8("image: url(:/images/querenwenhao.png);"));
    ui->tbtn_cancel->show();
    ui->tbtn_cancel->setFocus();
}

void MsgBox::setCriticalIcon()
{
    ui->lab_icon->setStyleSheet(QString::fromUtf8("image: url(:/images/error.png);"));
    ui->tbtn_cancel->hide();
    ui->tbtn_ok->setFocus();
}

void MsgBox::setText(QString text)
{
    ui->lab_text->setText(text);
}
void MsgBox::ok_button_clicked()
{
    close();
    setResult(Ok);
}
void MsgBox::cancel_button_clicked()
{
    close();
    setResult(Cancel);
}

//画StyleSheet
void MsgBox::paintEvent(QPaintEvent *)
{
    //QStyleOption opt;
    //opt.init(this);
    //QPainter p(this);
    //style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
