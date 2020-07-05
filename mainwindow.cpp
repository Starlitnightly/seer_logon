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
#include <Qdir>
#include <QApplication>
#include <QDebug>
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
    qDebug()<<"hq"<<(int)hq;
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
    //qDebug()<<"test"<<this->winId();





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
    connect(ui->action_5,SIGNAL(triggered()),this,SLOT(speedopen()));

    connect(ui->action_ie,SIGNAL(triggered()),this,SLOT(ClearCache()));
    connect(ui->action_8,SIGNAL(triggered()),this,SLOT(script_open()));

    //工具信号
    connect(ui->action_ce,SIGNAL(triggered()),this,SLOT(Opence()));
    connect(ui->action_fd,SIGNAL(triggered()),this,SLOT(Openfd()));

    //一键换装备信号
    connect(ui->bag_sk,SIGNAL(triggered()),this,SLOT(Changebag_sk()));
    connect(ui->bag_fs,SIGNAL(triggered()),this,SLOT(Changebag_fs()));
    connect(ui->bag_ld,SIGNAL(triggered()),this,SLOT(Changebag_ld()));
    connect(ui->bag_hd,SIGNAL(triggered()),this,SLOT(Changebag_hd()));
    connect(ui->bag_dy,SIGNAL(triggered()),this,SLOT(Changebag_dy()));
    connect(ui->bag_xa,SIGNAL(triggered()),this,SLOT(Changebag_xa()));
    connect(ui->bag_wl,SIGNAL(triggered()),this,SLOT(Changebag_wl()));
    connect(ui->bag_ys,SIGNAL(triggered()),this,SLOT(Changebag_ys()));
    connect(ui->bag_tz,SIGNAL(triggered()),this,SLOT(Changebag_tz()));
    connect(ui->bag_yy,SIGNAL(triggered()),this,SLOT(Changebag_yy()));
    connect(ui->bag_tq,SIGNAL(triggered()),this,SLOT(Changebag_tq()));
    connect(ui->bag_yh,SIGNAL(triggered()),this,SLOT(Changebag_yh()));
    //f.show();

    //nono窗口
    n=new Nono();
    connect(ui->action_13,SIGNAL(triggered(bool)),n,SLOT(slot_startedTimer_clicked(bool)));
    connect(ui->action_14,SIGNAL(triggered()),this,SLOT(dianfeng()));
    connect(this,SIGNAL(sendcap(bool)),n,SLOT(slot_capture(bool)));
    n->show();
    //初始化大漠插件
    /*
    QAxWidget *dm=new QAxWidget();
    dm->setControl(QString::fromUtf8("{26037A0E-7CBD-4FFF-9C63-56F2D0770214}"));
    //QMessageBox::information(this,"this",dm->dynamicCall("Ver()").toString());//测试是否成功
    AutoRegDm();
    //dm->dynamicCall("BindWindow(int,QString,QString,QString,int)",pid,"dx2", "windows","windows",1)
    */
    //wPid=(HWND)this->winId();
    //Bind *bdm=new Bind(this);
    //bdm->start();
    bind_status=false;


}


void MainWindow::dianfeng(){
    if(bind_status==false)
        Binddm();
    emit sendcap(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete n;
}

void MainWindow::Binddm(){
    //获取游戏窗口pid
    int pid;
    HWND test;
    HWND hq=(HWND)this->winId();
    qDebug()<<"hq"<<(int)hq;
    test=GetWindow(hq,5);
    test=GetWindow(test,2);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    test=GetWindow(test,5);
    pid=(int)test;
    Pid=test;
    //自动注册大漠
    AutoRegDm();
    //初始化大漠
    dm.setControl("dm.dmsoft");
    //绑定窗口
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
    //设置识图目录
    QString path=QDir::currentPath()+"/pic";
    dm.SetPath(path);
    //测试识图效果
    QVariant x,y;
    dm.FindPic(0,0,1000,600,"test.bmp","000000",0.8,0,x,y);
    qDebug()<<x.toInt()<<y.toInt();
    //设置字库
    dm.SetDict(0,path+"/ziku.txt");
    bind_status=true;
}

void MainWindow::FreshSeer()//刷新游戏
{
    qDebug()<<"通信无异常";
    //QString webstr=QString("http://seer.61.com/play.shtml");//设置要打开的网页
    ui->axWidget->dynamicCall("Refresh(void)");//显示网页
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
    QProcess pro;
    QString strPath = QDir::currentPath()+"/工具/ce6.8.exe";
    pro.startDetached(strPath);
}

void MainWindow::Openfd(){
    //打开fd
    QProcess pro;
    QString strPath = QDir::currentPath()+"/Fiddler/Fiddlerh.exe";
    pro.startDetached(strPath);
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

void MainWindow::script_open()
{
    if(bind_status==false)
        Binddm();
    f.show();

}

void MainWindow::speedopen()
{
    s.show();
    s.move(this->x(),this->y()+this->height());

}
void MainWindow::Changebag_sk(){
    if(bind_status==false)
        Binddm();
    Changebag("时空");
}
void MainWindow::Changebag_fs(){
    if(bind_status==false)
        Binddm();
    Changebag("腐蚀");
}
void MainWindow::Changebag_ld(){
    if(bind_status==false)
        Binddm();
    Changebag("零度");
}
void MainWindow::Changebag_hd(){
    if(bind_status==false)
        Binddm();
    Changebag("皇帝");
}
void MainWindow::Changebag_dy(){
    if(bind_status==false)
        Binddm();
    Changebag("毒液");
}
void MainWindow::Changebag_xa(){
    if(bind_status==false)
        Binddm();
    Changebag("笑傲");
}
void MainWindow::Changebag_wl(){
    if(bind_status==false)
        Binddm();
    Changebag("未来");
}
void MainWindow::Changebag_ys(){
    if(bind_status==false)
        Binddm();
    Changebag("元神");
}
void MainWindow::Changebag_tz(){
    if(bind_status==false)
        Binddm();
    Changebag("天尊");
}
void MainWindow::Changebag_yy(){
    if(bind_status==false)
        Binddm();
    Changebag("银翼骑士");
}
void MainWindow::Changebag_tq(){
    if(bind_status==false)
        Binddm();
    Changebag("天启");
}
void MainWindow::Changebag_yh(){
    if(bind_status==false)
        Binddm();
    Changebag("浴火");
}

void MainWindow::Changebag(QString name){
    Delay(100);
    //非法确认按钮
    ffAutoC *tmp=new ffAutoC(this);
    tmp->status=true;
    tmp->start();
    dm.MoveTo(582,487);
    dm.LeftClick();
    Openbag();
    Searchbag(Pid,name);
    Wearbag();
    tmp->status=false;
    Delay(1000);
    delete tmp;
    //QMessageBox::information(NULL,"this","小铁皮换装成功");
}

void Openbag(){
    QVariant x,y;
    while(dm.FindPic(18,11,526,316,"查看个人信息.bmp","000000",0.8,0,x,y)==-1){
        dm.MoveTo(670,293);
        dm.LeftClick();
        Delay(500);
    }
}

void Searchbag(HWND pid,QString name){
    dm.MoveTo(736,382);
    dm.LeftClick();
    QString s=name;
    foreach(QChar c, s)
        PostMessage(pid, WM_CHAR, c.unicode(), 0);
    Delay(500);
    dm.MoveTo(797,380);
    dm.LeftClick();
}

void Wearbag(){
    QVariant x,y;
    while(dm.FindPic(0,0,1000,600,"装备选完.bmp","000000",0.8,0,x,y)==-1){
        dm.MoveTo(202,445);
        dm.LeftClick();
        Delay(100);
        qDebug()<<"装备选完中";
    }
    qDebug()<<"装备选完";
    dm.MoveTo(357,314);
    dm.LeftClick();
    Delay(100);
}

void ffAutoC::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(406, 322, 562, 402,"放入背包确认.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(400, 200, 600, 300, "数据非法.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"消息盒子x.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }

        Delay(1000);
    }
}








