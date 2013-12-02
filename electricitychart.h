#ifndef ELECTRICITYCHART_H
#define ELECTRICITYCHART_H

#include <QWidget>
#include "mcontroller.h"

namespace Ui {
class ElectricityChart;
}

class ElectricityChart : public QWidget
{
    Q_OBJECT
    
private:
    Ui::ElectricityChart *ui;
    MController* controller;

public:
    explicit ElectricityChart(QWidget *parent, MController *mc);
    ~ElectricityChart();
    void chartUpData();
    void totleUpData();
};

#endif // ELECTRICITYCHART_H
