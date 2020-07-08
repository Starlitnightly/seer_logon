/**
 * @file speed.cpp
 * @brief 变速窗口及其相关
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "speed.h"
#include "ui_speed.h"

QLibrary lib("SpeedControl.dll");
typedef void(*Fun)(float a);
Fun Setrange;
/**
 * @brief 设置游戏速度
 * @param speed 游戏速度
 * @return 无
 */
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
/**
 * @brief 变速窗口构造函数
 * @param parent 父类指针
 * @return 无
 */
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
/**
 * @brief 变速窗口析构函数
 * @return 无
 */
Speed::~Speed()
{
    delete ui;
}
/**
 * @brief 自定义速度
 * @return 无
 */
void Speed::Changespeed(){
    QString text = ui->speedtext->toPlainText();
    setspeed(text.toFloat());
}
/**
 * @brief 滑块条更改速度
 * @return 无
 */
void Speed::sliderspeed(){
    int a=ui->speedslider->sliderPosition();
    float speed=qPow(2,a);
    setspeed(speed);
}
