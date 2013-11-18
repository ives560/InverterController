#include "clock.h"

Clock::Clock(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    ui.timeEdit->setTime(QTime::currentTime());
    ui.dateEdit->setDate(QDate::currentDate());
    startTimer(1000);
}

Clock::~Clock()
{

}

void Clock::timerEvent(QTimerEvent *)
{
    ui.timeEdit->setTime(QTime::currentTime());
    ui.dateEdit->setDate(QDate::currentDate());
}
