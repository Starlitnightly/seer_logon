#include "speed.h"
#include "ui_speed.h"

QLibrary lib("SpeedControl.dll");
typedef void(*Fun)(float a);
Fun Setrange;

void setspeed(float speed){

    if (lib.load())
    {
        if (!Setrange)
        {
            qDebug()<<"failed";
        }
        else
        {
            Setrange(speed);
            qDebug()<<"变速成功";
        }
    }
    else
    {
        qDebug()<<"failed";
    }
}

Speed::Speed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Speed)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);
    game_speed=1.0;
    Setrange=(Fun)lib.resolve("SetRange");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Changespeed()));
    //connect(ui->speedslider,SIGNAL(sliderMoved(int)),this,SLOT(sliderspeed()));
    connect(ui->speedslider,SIGNAL(valueChanged(int)),this,SLOT(sliderspeed()));

}

Speed::~Speed()
{
    delete ui;
}

void Speed::Changespeed(){
    QString text = ui->speedtext->toPlainText();
    setspeed(text.toFloat());
}
void Speed::sliderspeed(){
    int a=ui->speedslider->sliderPosition();
    float speed=qPow(2,a);
    setspeed(speed);
}
