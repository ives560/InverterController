#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
//#include <QTimerEvent>
#include "ui_clock.h"
class Clock : public QWidget
{
	Q_OBJECT

public:
	Clock(QWidget *parent = 0);
	~Clock();

private:
	Ui::Clock ui;

private:
    void timerEvent(QTimerEvent *);

};

#endif // CLOCK_H
