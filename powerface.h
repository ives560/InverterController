#ifndef POWERFACE_H
#define POWERFACE_H

#include "submenu.h"
#include "mcontroller.h"

class PowerFace : public SubMenu
{
	Q_OBJECT

public:
    PowerFace(QWidget *parent,MController* mc);
	~PowerFace();

private:
	void setupButton(QToolButton *button,QString text,int x,int y,QString iconPath,const char* member);
    int showMessageBox(QString text);

private:
	QToolButton *shutdown;
	QToolButton *reset;
	QToolButton *start;
	QToolButton *stop;

private slots:
	void shutdown_Clickde();
	void reset_Clickde();
	void start_Clickde();
	void stop_Clickde();
    void writeDoneSlot(ParaList,bool);
};

#endif // POWERFACE_H
