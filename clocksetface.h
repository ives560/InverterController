#ifndef CLOCKSETFACE_H
#define CLOCKSETFACE_H

#include "submenu.h"
#include "common.h"

#include "ui_clocksetface.h"

class ClockSetFace : public SubMenu
{
    Q_OBJECT

public:
    ClockSetFace(QWidget *parent=0,MController* mc=0);
    void setupUi();

private:
    void setCurrentTime();
    void writeClockData();
    void setLineEditValidator();
private:
    Ui::ClockSetFace ui_clock;

private slots:
    void tbtn_ok_clicked();
    void tbtn_cancel_clicked();

    void writeDoneSlot(ListParaItem,bool);

};

#endif // CLOCKSETFACE_H
