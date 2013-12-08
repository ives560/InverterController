#ifndef FAULTLED_H
#define FAULTLED_H

#include <QWidget>
#include <QTimer>
#include <QLabel>

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
    enum LedMode{NONE=-1,STANDBY,SHUTDOWN=1,RUN=3,FAULT,WARNING};
    enum LedState{ON,OFF};

    struct Led{
        LedState state;
        QLabel* label;
        QString on;
        QString off;
    };

private:
    Ui::FaultLed *ui;
    QTimer faultimer;
    LedMode cur_mode;
    Led green;
    Led red;


public:
    explicit FaultLed(QWidget *parent = 0);
    ~FaultLed();
    
    void setText(QString text);
    void setLedState(LedMode mode);
    void setLedState(int led);
    void setStateText(const int state);

    void switchState(Led* led);
private slots:
    void faultTimerOut();
};

#endif // FAULTLED_H
