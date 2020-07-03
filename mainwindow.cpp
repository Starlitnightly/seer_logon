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

    //自动注册大漠插件
    //AutoRegDm();

    //初始化大漠插件
    //QAxWidget *dm=new QAxWidget();
    //dm->setControl(QString::fromUtf8("{26037A0E-7CBD-4FFF-9C63-56F2D0770214}"));
    //QMessageBox::information(this,"this",dm->dynamicCall("Ver()").toString());//测试是否成功

    //AutoRegDm();



   // QLibrary mylib("speedhack-i386.dll");


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
    connect(ui->action_4,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->action_5,SIGNAL(triggered()),this,SLOT(speedopen()));

}


MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::ChangeSpeedPrepare()
{
/*
    speedhackhw=LoadLibraryA("speedhack-i386.dll");
    const char* s1="speedhackversion_GetTickCount";
    LPCSTR z1;
    z1=s1;
    speedhook[0].InHook("kernel32","GetTickCount",GetProcAddress(speedhackhw,z1),7);
    const char* s2="speedhackversion_QueryPerformanceCounter";
    LPCSTR z2;
    z2=s2;
    speedhook[1].InHook("kernel32","QueryPerformanceCounter",GetProcAddress(speedhackhw,z2),5);
    const char* s3="speedhackversion_GetTickCount";
    LPCSTR z3;
    z3=s3;
    speedhook[2].InHook("winmm","timeGetTime",GetProcAddress(speedhackhw,z3),5);

    /*
    LPVOID getick=new LPVOID;
    LPVOID query=new LPVOID;
    BYTE tbyte1[5],tbyte2[5];
    DWORD dwWriteByte;
    tbyte1[0]=0xE9;
    tbyte1[1]=speedhook[0].bOldByte[1];
    *(&(tbyte1[1]))+=*(Jmp((LPVOID)(getick+7),(LPVOID)(speedhook[0].pOldFunEntry+7)));
    WriteProcessMemory( GetCurrentProcess(), getick, tbyte1, 5, &dwWriteByte );
    tbyte2[0]=0xE9;
    tbyte2[1]=speedhook[1].bOldByte[1];
    *(&(tbyte2[1]))+=*(Jmp((LPVOID)(query+5),(LPVOID)(speedhook[1].pOldFunEntry+5)));
    WriteProcessMemory( GetCurrentProcess(), query, tbyte2, 5, &dwWriteByte );
    
    WriteProcessMemory( GetCurrentProcess(), (LPVOID)GetProcAddress(speedhackhw,"realGetTickCount"), getick, 5, &dwWriteByte );
    WriteProcessMemory( GetCurrentProcess(), (LPVOID)GetProcAddress(speedhackhw,"realQueryPerformanceCounter"), query, 5, &dwWriteByte );

    speedhook[0].Hook(7);
    speedhook[1].Hook(5);
    speedhook[2].Hook(5);
*/



}

void MainWindow::ChangeSpeed()
{
    ui->axWidget->setFocus();
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_WHEEL,0,0, 200, 0);

}

void MainWindow::open()
{
    QProcess pro;
    QString strPath = QDir::currentPath()+"\\tools.exe";
    pro.startDetached(strPath);
}

void MainWindow::speedopen()
{
    QProcess pro;
    QString strPath = QDir::currentPath()+"\\speed\\speed.exe";
    pro.startDetached(strPath);
}





