#include "setparadialog.h"
#include "ui_setparadialog.h"
#include "msgbox.h"
SetParaDialog::SetParaDialog(QWidget *parent, MController *mc) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::SetParaDialog)
{
    ui->setupUi(this);
    controller=mc;
    para=NULL;
    connect(ui->tbtn_cancel,SIGNAL(clicked()),this,SLOT(hide()));
    connect(ui->tbtn_ok,SIGNAL(clicked()),this,SLOT(pbtn_OK_clicked()));
}

SetParaDialog::~SetParaDialog()
{
    delete ui;
}

void SetParaDialog::getPara(QString name, ParaItem *p)
{
    if(p==NULL)
        return;
    para=p;
    ui->label_name->setText(name);
    double val = para->values;
    val = val/(para->scaling);
    ui->lineEdit->setText(QString("%1").arg(val));
    ui->label_unit->setText(para->unit);
}

//
void SetParaDialog::pbtn_OK_clicked()
{
    hide();
    MsgBox msg(this,MsgBox::Question,"确定要写入当前值?");
    if(msg.exec()==MsgBox::Ok)
    {
        double val_f = ui->lineEdit->text().toDouble();
        short int val_i =(short int)(val_f*para->scaling);
//        if(val_i>32766)
//        {
//            msg.setText("设定值超出允许范围!");
//            msg.exec();
//            return;
//        }
        controller->userWriteData(para->address,val_i);
        MsgBox msg(this,MsgBox::Question,"是否写入保持寄存器?");
        if(msg.exec()==MsgBox::Ok)
        {
            controller->userWriteData(PARA::Initial_cmd,3);
            MsgBox msg(this,MsgBox::Question,"是否更新写入数据?");
            if(msg.exec()==MsgBox::Ok)
            {
                controller->userWriteData(PARA::Initial_cmd,7);
            }

        }
        close();
    }
    else
        show();

}

