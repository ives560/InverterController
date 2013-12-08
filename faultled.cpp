#include "faultled.h"
#include "ui_faultled.h"

FaultLed::FaultLed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaultLed)
{
    ui->setupUi(this);

    cur_mode = NONE;
    green.state = OFF;
    green.label = ui->lab_green;
    green.off = GREEN_OFF_PNG;
    green.on = GREEN_ON_PNG;
    red.state = OFF;
    red.label = ui->lab_red;
    red.off = RED_OFF_PNG;
    red.on = RED_ON_PNG;

    connect(&faultimer,SIGNAL(timeout()),this,SLOT(faultTimerOut()));
}

FaultLed::~FaultLed()
{
    delete ui;
}

void FaultLed::setText(QString text)
{
    ui->lab_text->setText(text);
}

void FaultLed::setStateText(const int state)
{
    switch(state)
    {
        case 0:
            setText("Power up");
        break;
        case 1:
            setText("Shutdown");
        break;
        case 2:
            setText("Reset");
        break;
        case 3:
            setText("Ready to start");
        break;
        case 4:
            setText("WaitPrecharge");
        break;
        case 5:
            setText("Match AC");
        break;
        case 6:
            setText("Start Wait");
        break;
        case 7:
            setText("Inverter run");
        break;
        case 8:
            setText("Stop");
        break;
        case 9:
            setText("test");
        break;
    }
}

void FaultLed::setLedState(int led)
{
    bool g = led&0x02;
    bool r = led&0x04;

    if(g==true)
        ui->lab_green->setPixmap(QPixmap(GREEN_OFF_PNG));
    else
        ui->lab_green->setPixmap(QPixmap(GREEN_ON_PNG));


    if(r==true)
        ui->lab_red->setPixmap(QPixmap(RED_OFF_PNG));
    else
        ui->lab_red->setPixmap(QPixmap(RED_ON_PNG));
}

void FaultLed::setLedState(LedMode mode)
{
    QString green_png;
    QString red_png;
    QString show_txt;
    faultimer.stop();
    cur_mode = mode;
    switch(cur_mode)
    {
        case STANDBY:
            {
                green_png = GREEN_ON_PNG;
                red_png = RED_OFF_PNG;
                show_txt ="需要启动";
            }
            break;
        case SHUTDOWN:
            {
                green_png = GREEN_ON_PNG;
                red_png = RED_ON_PNG;
                show_txt = "需要复位";
            }
            break;
        case RUN:
            {
                green_png = GREEN_ON_PNG;
                red_png = RED_OFF_PNG;
                show_txt = "不需操作";
                faultimer.start(1000);
            }
            break;
        case FAULT:
            {
                green_png = GREEN_OFF_PNG;
                red_png = RED_ON_PNG;
                show_txt = "需要排除";
            }
            break;
        case WARNING:
            {
                green_png = GREEN_OFF_PNG;
                red_png = RED_ON_PNG;
                show_txt = "电网不正常";
                faultimer.start(1000);
            }
            break;
        default:
            {

            }
            break;
    }
    ui->lab_text->setText(show_txt);
    ui->lab_green->setPixmap(QPixmap(green_png));
    ui->lab_red->setPixmap(QPixmap(red_png));
}
//定时器
void FaultLed::faultTimerOut()
{
    if(cur_mode==RUN)
        switchState(&green);
    else if(cur_mode == WARNING)
        switchState(&red);

}

void FaultLed::switchState(Led* led)
{
    if(led->state == ON)
    {
        led->state = OFF;
        led->label->setPixmap(QPixmap(led->off));
    }
    else if(led->state == OFF)
    {
        led->state = ON;
        led->label->setPixmap(QPixmap(led->on));
    }
}


