#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mediamute.h"
#include <QLibrary>
#include "hookapi.h"
#include<qprocess.h>
#include<qmessagebox.h>
#include <Windows.h>
#include <QKeyEvent>
#include <qcoreapplication.h>
#include <qevent.h>
#include <QKeyEventTransition>
#include<Qt>
#include <QtGui/QMouseEvent>

#include <QProcess>
#include<Qdir>
#include<QApplication>
#include<QDebug>
#include <QList>
#include <QVariantList>




void AutoRegDm()
{
    QString path;
    path=QCoreApplication::applicationDirPath();//获取程序运行路径
    QString cmdStr="Regsvr32"+path+"/dm.dll /s";
    QProcess process(0);
    process.start("cmd",QStringList()<<"/c"<<cmdStr);
    process.waitForStarted();
    process.waitForFinished();
}


HWND Getpid(){
    HWND test;
    HWND hq=FindWindow(L"Qt5QWindowIcon",L"seer");
    test=GetWindow(hq,5);
    test=GetWindow(test,2);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    return test;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //设置ui
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);
      //  this->setStyleSheet("QDialog{border:2px solid green;}");
    //setWindowFlags(Qt::FramelessWindowHint);//无边框
    //setAttribute(Qt::WA_TranslucentBackground);//背景透明
    ui->setupUi(this);
    //setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint);






    //载入赛尔号游戏
    ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件ID
    ui->axWidget->setProperty("DisplayAlerts",false);//不显示警告信息
    ui->axWidget->setProperty("DisplayScrollBars",true);//不显示滚动条
    QString webstr=QString("http://seer.61.com/play.shtml");//设置要打开的网页
    ui->axWidget->dynamicCall("Navigate(const QString&)",webstr);//显示网页
    Mute();


    //信号连接
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(FreshSeer()));
    //connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Mute()));
    //connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(OptimizingMemory()));
    //connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(ChangeSpeed()));
    connect(ui->action,SIGNAL(triggered()),this,SLOT(FreshSeer()));
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(Mute()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(unMute()));
    //connect(ui->action_4,SIGNAL(triggered()),this,SLOT(open()));
    //connect(ui->action_5,SIGNAL(triggered()),this,SLOT(speedopen()));

    connect(ui->action_ie,SIGNAL(triggered()),this,SLOT(ClearCache()));

    qDebug()<<(int)Getpid();
    f.show();

    //初始化大漠插件
    /*
    QAxWidget *dm=new QAxWidget();
    dm->setControl(QString::fromUtf8("{26037A0E-7CBD-4FFF-9C63-56F2D0770214}"));
    //QMessageBox::information(this,"this",dm->dynamicCall("Ver()").toString());//测试是否成功
    AutoRegDm();
    //dm->dynamicCall("BindWindow(int,QString,QString,QString,int)",pid,"dx2", "windows","windows",1)
    */

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Binddm(){
    int pid=(int)Getpid();
    AutoRegDm();
    dm.setControl("dm.dmsoft");
    if(dm.BindWindow(pid,"dx2", "windows","windows",1)==0){
        if(dm.GetLastError()==-18){
            QMessageBox::information(this,"this","关于绑定失败，请在群公告内查找解决方法[记得关闭杀毒软件]，若不看公告，私聊星夜大概率会被拉黑");
        }else if(dm.GetLastError()==0)
            QMessageBox::information(this,"this","错误代码：0，本错误请关闭所有杀毒软件，并用管理员模式启动");
        else{
            QString tmp="错误代码："+QString::number(dm.GetLastError())+"，可发送错误代码给星夜咨询错误问题";
            QMessageBox::information(this,"this",tmp);
        }
    }
    QString path=QDir::currentPath()+"/pic";
    dm.SetPath(path);
    QVariant x,y;
    dm.FindPic(0,0,1000,600,"test.bmp","000000",0.8,0,x,y);
    qDebug()<<x.toInt()<<y.toInt();
}

void MainWindow::FreshSeer()//刷新游戏
{
    QString webstr=QString("http://seer.61.com/play.shtml");//设置要打开的网页
    ui->axWidget->dynamicCall("Navigate(const QString&)",webstr);//显示网页
}

void MainWindow::Mute()//静音
{
    Cmute.SetMute(true);
}

void MainWindow::unMute()//解除静音
{
    Cmute.SetMute(false);
}

void MainWindow::OptimizingMemory()//内存优化
{
    SetProcessWorkingSetSize(GetCurrentProcess(),-1,-1);
}

void MainWindow::ReleaseMemory(){
    //内存释放
}

void MainWindow::ClearCache(){
    //清理ie缓存
    Binddm();



    /*
    QProcess p(0);
    p.start("cmd");
    p.waitForStarted();
    p.write("RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 8");
    p.closeWriteChannel();
    p.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(p.readAllStandardOutput());
    */
}

void MainWindow::Opence(){
    //打开ce
}

void MainWindow::Openfd(){
    //打开fd
}

void MainWindow::OpenKeyandMouse(){
    //打开键鼠录制器
}

void MainWindow::OpenMousepoint(){
    //打开鼠标连点器
}

void MainWindow::ChangeSpirit(){
    //一键换精灵窗口
}

void MainWindow::ChangeBag(){
    //一键换背包
}

void MainWindow::Gemsynthesis(){
    //宝石合成
}

void MainWindow::Inputcdk(){
    //一键输入cdk
}

void MainWindow::GreenfireTimer(){
    //绿火计时器
}

void MainWindow::PeakMode(){
    //巅峰模式
}

void MainWindow::Openscript(){
    //打开脚本
}

void MainWindow::ChangeSpeedPrepare()
{
}

void MainWindow::ChangeSpeed()
{


}

void MainWindow::open()
{
    f.show();

    //QProcess pro;
    //QString strPath = QDir::currentPath()+"\\tools.exe";
    //pro.startDetached(strPath);
}

void MainWindow::speedopen()
{
    QLibrary lib("SpeedControl.dll");
    if (lib.load())
    {
        typedef void(*Fun)(float a);
        Fun Setrange=(Fun)lib.resolve("SetRange");
        if (!Setrange)
        {
            qDebug()<<"failed";
        }
        else
        {
            Setrange(4.0);
            qDebug()<<"变速成功";
        }
    }
    else
    {
        qDebug()<<"failed";
    }

}







