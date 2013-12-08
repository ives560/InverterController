#include "clocksetface.h"
#include "msgbox.h"

#include <QProcess>

ClockSetFace::ClockSetFace(QWidget *parent, MController *mc)
    : SubMenu(parent,mc)
{
    setupUi();
    qRegisterMetaType<ListParaItem>("ListParaItem");
    connect(controller,SIGNAL(writeDataDone(ListParaItem,bool)),this,SLOT(writeDoneSlot(ListParaItem,bool)));
    connect(ui_clock.tbtn_ok,SIGNAL(clicked()),this,SLOT(tbtn_ok_clicked()));
    connect(ui_clock.tbtn_cancel,SIGNAL(clicked()),this,SLOT(tbtn_cancel_clicked()));

}

void ClockSetFace::setupUi()
{
    setTitle("日期&时间",":/images/time.png");
    ui_clock.setupUi(ui.showArea);
    setCurrentTime();
    setLineEditValidator();
}

void ClockSetFace::tbtn_ok_clicked()
{
    qDebug()<<"tbtn_ok_clicked";
    MsgBox msg(this,MsgBox::Question,"确定要修改系统时间?");
    if(msg.exec()==MsgBox::Ok)
    {
       writeClockData();
    }
}

//
void ClockSetFace::writeClockData()
{
    QString str;
    ListParaItem list;
    ParaItem* para;

    QLineEdit* edits[5] = {ui_clock.ldt_s,ui_clock.ldt_tm,ui_clock.ldt_h,
                           ui_clock.ldt_d,ui_clock.ldt_m};
    int names[5] = {PARA::ss,       PARA::mm,       PARA::hh,       PARA::dd,       PARA::MM};

    para = controller->paralist[PARA::set_clock];
    para->val_w = 2;
    list.append(para);

    for(int i=0;i<5;i++)
    {
        para = controller->paralist[names[i]];
        para->val_w = edits[i]->text().toInt();
        list.append(para);
    }

    para = controller->paralist[PARA::yyl];
    str = ui_clock.ldt_y->text();
    str = str.mid(2,2);
    para->val_w = str.toInt();
    list.append(para);

    para = controller->paralist[PARA::yyh];
    str = ui_clock.ldt_y->text();
    str = str.mid(0,2);
    para->val_w = str.toInt();
    list.append(para);

    controller->userWriteData(list);
}

void ClockSetFace::tbtn_cancel_clicked()
{
    qDebug()<<"tbtn_cancel_clicked";
    setCurrentTime();
}

void ClockSetFace::writeDoneSlot(ListParaItem list, bool success)
{
    if(success == true)
    {
        QDate d =QDate(ui_clock.ldt_y->text().toInt(),ui_clock.ldt_m->text().toInt(),ui_clock.ldt_d->text().toInt());
        QTime t =QTime(ui_clock.ldt_h->text().toInt(),ui_clock.ldt_tm->text().toInt(),ui_clock.ldt_s->text().toInt());
        QDateTime dt = QDateTime(d,t);
        time_t tt =dt.toTime_t();
        int error = stime(&tt);
#ifdef AM335x_BOARD
        QProcess::execute("hwclock -w");//系统时钟和硬件时钟同步
#endif
        if(error != 0)
            qDebug()<<"error:stime";
    }
    else
        setCurrentTime();
    //QProcess::execute(cmd);
    //system("hwclock -w");
    //QProcess::execute("hwclock -w");
}

void ClockSetFace::setCurrentTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QLineEdit* edits[6] = {ui_clock.ldt_y,      ui_clock.ldt_m,     ui_clock.ldt_d,
                           ui_clock.ldt_h,      ui_clock.ldt_tm,    ui_clock.ldt_s};
    int vals[6] = {date.year(),date.month(),date.day(),
                 time.hour(),time.minute(),time.second()};
    for(int i=0;i<6;i++)
    {
        QString str = QString("%1").arg(vals[i]);
        edits[i]->setText(str);
    }

}
//设置编辑框能输入的取值范围
void ClockSetFace::setLineEditValidator()
{
    QRegExp regExp("[0-9]+$");

    QLineEdit* edits[6] = {ui_clock.ldt_y,ui_clock.ldt_m,ui_clock.ldt_d,
                           ui_clock.ldt_h,ui_clock.ldt_tm,ui_clock.ldt_s};

    QValidator* vadatrs[6] ={new QIntValidator(1900,2999,edits[0]),new QIntValidator(0,12,edits[1]),new QIntValidator(0,31,edits[2]),
                           new QIntValidator(0,24,edits[3]),new QIntValidator(0,60,edits[4]),new QIntValidator(0,60,edits[5])};
    for(int i=0;i<6;i++)
    {
        QValidator *vadatr = new QRegExpValidator(regExp,edits[i]);
        edits[i]->setValidator(vadatr);
        edits[i]->setValidator(vadatrs[i]);
    }
}


