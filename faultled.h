#ifndef FAULTLED_H
#define FAULTLED_H

#include <QWidget>
#include <QTimer>

#define GREEN_ON_PNG        ":/images/lianggreen.png"
#define GREEN_OFF_PNG       ":/images/bulianggreen.png"
#define RED_ON_PNG          ":/images/liangred.png"
#define RED_OFF_PNG         ":/images/buliangred.png"

namespace Ui {
class FaultLed;
}

class FaultLed : public QWidget
{
    Q_OBJECT
    
public:
    enum LedMode{NONE,GREEN,RED,GREENFLASH};
    enum LedState{ON,OFF};

private:
    Ui::FaultLed *ui;
    QTimer faultimer;
    LedMode cur_mode;
    LedState green;
    LedState red;


public:
    explicit FaultLed(QWidget *parent = 0);
    ~FaultLed();
    
    void setText(QString text);
    void setLedState(LedMode mode);

private slots:
    void faultTimerOut();
};

#endif // FAULTLED_H
