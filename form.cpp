#include "form.h"
#include "ui_form.h"

#include <QDebug>
#include <QThread>
#include <QObject>



Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(test()));

}

void Tower::run(){
    QVariant x,y;
    while(status==true){
        if(now==6){
            if(dm.FindPic(0,0,1000,600,"rc-6-1.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(489,546);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-6-2.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(485,419);
                dm.LeftClick();
                now=7;
            }
        }else if(now==7){
            if(dm.FindPic(0,0,1000,600,"rc-6-3.bmp|rc-6-3-1.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(192,178);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-6-3-10.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-7-1.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-7-2.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"yzztlj.bmp|yzztlj2.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"yzztlj3.bmp|yzztlj4.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-7-3.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(913,55);
                dm.LeftClick();
                status=false;
                qDebug()<<"finish";
            }
        }
    }
}

void Work::run(){
        int i=0;
        for (i = 0; i < 1000000000; i++)
        {qDebug()<<i;sleep(1);}
}

void Form::test(){

    Tower *test=new Tower(this);
    //connect(test,, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    test->status=true;
    test->now=6;
    test->start();
    //test.wait();
}

Form::~Form()
{
    delete ui;
}


