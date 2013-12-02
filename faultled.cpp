#include "faultled.h"
#include "ui_faultled.h"

FaultLed::FaultLed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaultLed)
{
    ui->setupUi(this);

    cur_mode = NONE;
    green = OFF;
    red = OFF;

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

void FaultLed::setLedState(LedMode mode)
{
    QString green_png;
    QString red_png;
    QString show_txt;
    faultimer.stop();
    cur_mode = mode;
    switch(cur_mode)
    {
        case GREEN:
            {
                green_png = GREEN_ON_PNG;
                red_png = RED_OFF_PNG;
                show_txt ="运行";
            }
            break;
        case RED:
            {
                green_png = GREEN_OFF_PNG;
                red_png = RED_ON_PNG;
                show_txt = "故障";
            }
            break;
        case GREENFLASH:
            {
                green_png = GREEN_ON_PNG;
                red_png = RED_OFF_PNG;
                show_txt = "运行";
                green = ON;
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
    if(cur_mode == GREENFLASH)
    {
        if(green == ON)
        {
            green = OFF;
            ui->lab_green->setPixmap(QPixmap(GREEN_OFF_PNG));
            this->update();
        }
        else if(green == OFF)
        {
            green = ON;
            ui->lab_green->setPixmap(QPixmap(GREEN_ON_PNG));
            this->update();
        }
    }
}
