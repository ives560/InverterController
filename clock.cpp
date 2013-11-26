#include "clock.h"

Clock::Clock(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    ui.lb_time->setText(QString("%1:%2:%3").arg(time.hour()).arg(time.minute()).arg(time.second()));
    ui.lb_date->setText(QString("%1年%2月%3日").arg(date.year()).arg(date.month()).arg(date.day()));
    //ui.timeEdit->setTime(QTime::currentTime());
    //ui.dateEdit->setDate(QDate::currentDate());
    startTimer(1000);
}

Clock::~Clock()
{

}

void Clock::timerEvent(QTimerEvent *)
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    ui.lb_time->setText(QString("%1:%2:%3").arg(time.hour()).arg(time.minute()).arg(time.second()));
    ui.lb_date->setText(QString("%1年%2月%3日").arg(date.year()).arg(date.month()).arg(date.day()));
    //ui.timeEdit->setTime(QTime::currentTime());
    //ui.dateEdit->setDate(QDate::currentDate());
}
