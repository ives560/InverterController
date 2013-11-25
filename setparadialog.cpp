#include "setparadialog.h"
#include "ui_setparadialog.h"

SetParaDialog::SetParaDialog(QWidget *parent, MController *mc) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::SetParaDialog)
{
    ui->setupUi(this);
    controller=mc;
    para=NULL;
    connect(ui->pbtn_cancel,SIGNAL(clicked()),this,SLOT(hide()));
    connect(ui->pbtn_OK,SIGNAL(clicked()),this,SLOT(pbtn_OK_clicked()));
}

SetParaDialog::~SetParaDialog()
{
    delete ui;
}

void SetParaDialog::getPara(QString name, ParaInfo *p)
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
    QMessageBox msg(this);
    msg.setWindowTitle("警告！");
    msg.setText("确定要写入当前值!");
    msg.setIcon(QMessageBox::Warning);
    msg.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Cancel);
    if(msg.exec()==QMessageBox::Ok)
    {
        double val_f = ui->lineEdit->text().toDouble();
        short int val_i =(short int)(val_f*para->scaling);
        if(val_i>32767)
        {
            msg.setText("设定值超出允许范围!");
            msg.exec();
            return;
        }
        controller->userWriteData(para,val_i);
    }

}

