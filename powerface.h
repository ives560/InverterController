#ifndef POWERFACE_H
#define POWERFACE_H

#include "submenu.h"
#include "mcontroller.h"
#include "ui_powerface.h"
class PowerFace : public SubMenu
{
	Q_OBJECT

public:
    PowerFace(QWidget *parent,MController* mc);
	~PowerFace();

private:
    int showMessageBox(QString text);

private:
    Ui::PowerFace ui_power;
    QWidget* m_parent;

private slots:
	void shutdown_Clickde();
	void reset_Clickde();
	void start_Clickde();
	void stop_Clickde();
    void writeDoneSlot(ParaList,bool);
};

#endif // POWERFACE_H
