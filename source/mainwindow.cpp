/**
 * @file mainwindow.cpp
 * @brief 游戏主窗口及其相关
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mediamute.h"
#include <QLibrary>
#include<qprocess.h>
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
#include <QDesktopServices>
#include <QMessageBox>



/**
 * @brief 自动注册大漠插件函数
 * @return 无
 */
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

/**
 * @brief 获取程序pid
 * @return 返回程序pid（由于窗口名可变所以此函数作废）
 */
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
/**
 * @brief 脚本窗口析构函数
 * @return 无
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete n;
    delete csp;
}
/**
 * @brief 游戏主窗口构造函数
 * @param parent 父类指针
 * @return 无
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //设置ui
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);
      //  this->setStyleSheet("QDialog{border:2px solid green;}");
    //setWindowFlags(Qt::FramelessWindowHint);//无边框
    //setAttribute(Qt::WA_TranslucentBackground);//背景透明
    allpath=QCoreApplication::applicationDirPath();
    qDebug()<<allpath;
    ato=NULL;

    QSettings *configIniWrite = new QSettings(allpath+"/set.ini", QSettings::IniFormat);
    //向ini文件中写入内容,setValue函数的两个参数是键值对
    qDebug()<<"agree"<<configIniWrite->value("agree").toString();
    if(configIniWrite->value("agree").toString()!="true")
    {
        if(ato==NULL)
            ato=new Atoken();
        ato->show();
    }
    delete configIniWrite;

    ui->setupUi(this);
    qDebug()<<"atosuccess";

    //setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint);
    //qDebug()<<"test"<<this->winId();





    //载入赛尔号游戏
    ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件ID
    ui->axWidget->setProperty("DisplayAlerts",false);//不显示警告信息
    ui->axWidget->setProperty("DisplayScrollBars",true);//不显示滚动条
    QString webstr=QString("http://seer.61.com/play.shtml");//设置要打开的网页
    ui->axWidget->dynamicCall("Navigate(const QString&)",webstr);//显示网页

    cd=NULL;

    Mute();

    qDebug()<<"载入无问题";


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
    //清理缓存
    connect(ui->action_ie,SIGNAL(triggered()),this,SLOT(ClearCache()));
    //脚本
    connect(ui->action_8,SIGNAL(triggered()),this,SLOT(script_open()));
    connect(ui->action_9,SIGNAL(triggered()),this,SLOT(Openscript()));

    //工具信号
    connect(ui->action_ce,SIGNAL(triggered()),this,SLOT(Opence()));
    connect(ui->action_fd,SIGNAL(triggered()),this,SLOT(Openfd()));
    connect(ui->action_cdk,SIGNAL(triggered()),this,SLOT(Inputcdk()));
    connect(ui->action_4,SIGNAL(triggered()),this,SLOT(PeakMode()));
    connect(ui->action_21,SIGNAL(triggered()),this,SLOT(seer_cal()));
    connect(ui->action_7,SIGNAL(triggered()),this,SLOT(slot_shiyongshuoming()));
    connect(ui->action_12,SIGNAL(triggered()),this,SLOT(slot_xiangmuyuanma()));
    connect(ui->action_20,SIGNAL(triggered()),this,SLOT(slot_mianzexieyi()));
    connect(ui->action_22,SIGNAL(triggered()),this,SLOT(slot_author()));


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

    //一键换精灵窗口信号
    connect(ui->actionyijian,SIGNAL(triggered()),this,SLOT(show_csp()));

    qDebug()<<"信号连接无问题";
    //f.show();

    //nono窗口
    //巅峰模式

    n=new Nono();
    connect(ui->action_13,SIGNAL(triggered(bool)),n,SLOT(slot_startedTimer_clicked(bool)));
    connect(ui->action_14,SIGNAL(triggered()),this,SLOT(dianfeng()));
    connect(this,SIGNAL(sendcap(bool)),n,SLOT(slot_capture(bool)));
    connect(this,SIGNAL(sendtip(QString)),n,SLOT(slot_tip(QString)));
    connect(n,SIGNAL(signal_fresh()),this,SLOT(FreshSeer()));
    connect(n,SIGNAL(signal_sb()),this,SLOT(slot_sb()));
    connect(this,SIGNAL(signal_openskill()),n,SLOT(showskill()));
    qDebug()<<"nono信号无问题";
    n->show();
    //QDesktopWidget* desktopWidget = QApplication::desktop();
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;
    int screen_width = mm.width();
    int screen_height = mm.height();
    n->move(50,screen_height-n->height()-50);
    this->setAttribute(Qt::WA_QuitOnClose,true);




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
    /*
    QFile file("F:/seer/test.json");
    //qDebug()<<allpath+"/json/new.json";
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();
    //value.replace("\n","");
    //value.replace("\t","");
    qDebug()<<value.mid(0,100);
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
    QJsonObject jsonObject = document.object();
    if(jsonObject["newversion"]!=current_version)
        qDebug()<<"有新版本";
    */
    nam = new QNetworkAccessManager(this);
    connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_new(QNetworkReply*)));
    QUrl url;
    url.setUrl("http://jlhsmuseum.cn/news/test.json");
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    QNetworkReply* reply = nam->get(request);
    qDebug()<<"此处无问题";

    QFile::link(allpath+"/星小夜的seer登录器.exe", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).append("/").append("星小夜的seer登录器.lnk"));
}
/**
 * @brief 检测更新-返回槽函数
 * @param reply 网页返回内容
 */
void MainWindow::slot_new(QNetworkReply *reply){
    QNetworkReply::NetworkError err = reply->error();
    //qDebug()<<reply->readAll();
    if(err != QNetworkReply::NoError) {
        qDebug() << "accFailed: " << reply->errorString();
    }else {
        // 获取返回内容
        QString str = reply->readAll();//读取接收到的数据
        //parse_UpdateJSON(str);
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(str.toUtf8(), &json_error);
        QJsonObject obj = parse_doucment.object();
        new_version=obj.take("newversion").toString();
        new_content=obj.take("content").toString();
        new_error=obj.take("error").toString();
        new_time=obj.take("time").toString();
        new_upurl=obj.take("upurl").toString();
        new_news=obj.take("news").toString();
        new_guanggao=obj.take("guanggao").toString();


    }
    if(new_error!="667"){
        QMessageBox::about(NULL,"tip","抱歉，星小夜登录器停止使用，如果非公告停止那么请检查网络连接");
        exit(0);
    }
    if(new_time!="假"){
        QMessageBox::about(NULL,"tip",new_news);
        if(new_guanggao!=" ")
            QDesktopServices::openUrl(QUrl(new_guanggao));
    }
    if(new_version!=current_version){
        emit sendtip("发现新版本！版本号："+new_version);
        QDesktopServices::openUrl(QUrl(new_upurl));
    }

}
/**
 * @brief 打开一键换背包窗口
 * @return 无
 */
void MainWindow::show_csp(){
    if(bind_status==false)
        Binddm();
    csp=new Changesp();
    csp->show();

}
/**
 * @brief 绑定大漠插件函数
 * @return 无
 */
void MainWindow::slot_sb(){
    if(bind_status==false)
        Binddm();
}
/**
 * @brief 截取对面阵容函数-巅峰
 * @return 无
 */
void MainWindow::dianfeng(){
    if(bind_status==false)
        Binddm();
    emit sendcap(true);
    emit sendtip("精灵阵容已截图完毕");
}

/**
 * @brief 绑定大漠插件到游戏窗口
 * @return 无
 */
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
    QString path=allpath+"/pic";
    dm.SetPath(path);
    //测试识图效果
    QVariant x,y;
    dm.FindPic(0,0,1000,600,"test.bmp","000000",0.8,0,x,y);
    qDebug()<<x.toInt()<<y.toInt();
    //设置字库
    dm.SetDict(0,path+"/ziku.txt");
    bind_status=true;
}
/**
 * @brief 刷新游戏
 * @return 无
 */
void MainWindow::FreshSeer()//刷新游戏
{
    qDebug()<<"通信无异常";
    //QString webstr=QString("http://seer.61.com/play.shtml");//设置要打开的网页
    ui->axWidget->dynamicCall("Refresh(void)");//显示网页
}
/**
 * @brief 游戏静音
 * @return 无
 */
void MainWindow::Mute()//静音
{
    Cmute.SetMute(true);
    emit sendtip("小赛尔，游戏静音成功啦，如果没有成功再按一次");
}
/**
 * @brief 游戏接触静音
 * @return 无
 */
void MainWindow::unMute()//解除静音
{
    Cmute.SetMute(false);
    emit sendtip("小赛尔，游戏成功解除静音了");
}
/**
 * @brief 内存优化
 * @return 无
 */
void MainWindow::OptimizingMemory()//内存优化
{
    SetProcessWorkingSetSize(GetCurrentProcess(),-1,-1);
    emit sendtip("内存优化成功，如果还是卡顿建议刷新");
}
/**
 * @brief 内存释放
 * @return 无
 */
void MainWindow::ReleaseMemory(){
    //内存释放(之后有空再写，暂时用内存优化代替下)
    SetProcessWorkingSetSize(GetCurrentProcess(),-1,-1);
    emit sendtip("内存释放成功，如果还是卡顿建议刷新");
}
/**
 * @brief 清理ie缓存
 * @return 无
 */
void MainWindow::ClearCache(){
    //清理ie缓存
    QProcess process(0);
    process.start("cmd",QStringList()<<"/c"<<"RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 8");
    process.waitForStarted();
    process.waitForFinished();
    emit sendtip("ie缓存清理成功，如果还是卡顿建议刷新");

}
/**
 * @brief 打开ce
 * @return 无
 */
void MainWindow::Opence(){
    //打开ce
    QProcess pro;
    QString strPath = allpath+"/工具/ce6.8.exe";
    pro.startDetached(strPath);
    emit sendtip("Cheatengine正在加载中，请不要用此工具做出不允许的事情哦");
}
/**
 * @brief 打开fd
 * @return 无
 */
void MainWindow::Openfd(){
    //打开fd
    QProcess pro;
    QString strPath = allpath+"/工具/Fiddler/Fiddlerh.exe";
    pro.startDetached(strPath);
    emit sendtip("fiddler正在加载中，请不要用此工具做出不允许的事情哦");
}
/**
 * @brief 打开鼠标录制工具
 * @return 无
 */
void MainWindow::OpenKeyandMouse(){
    //打开键鼠录制器
    QProcess pro;
    QString strPath = allpath+"/工具/录制/星小夜的键鼠录制工具.exe";
    pro.startDetached(strPath);
    emit sendtip("鼠标录制器启动中，可以开始做你的脚本啦");
}
/**
 * @brief 打开鼠标连点器
 * @return 无
 */
void MainWindow::OpenMousepoint(){
    //打开鼠标连点器
    QMessageBox::information(NULL,"this","开发中");
    emit sendtip("此功能还在开发中，敬请期待");
}

/**
 * @brief 宝石合成
 * @return 无
 */
void MainWindow::Gemsynthesis(){
    //宝石合成
    emit sendtip("此功能还在开发中，敬请期待");
}


/**
 * @brief 打开脚本窗口
 * @return 无
 */
void MainWindow::script_open()
{
    if(bind_status==false)
        Binddm();
    f.show();
    emit sendtip("脚本已打开，本功能搜集自网络，星夜对本功能带来的一切后果概不负责");

}
/**
 * @brief 打开变速窗口
 * @return 无
 */
void MainWindow::speedopen()
{
    s.show();
    s.move(this->x(),this->y()+this->height());
    emit sendtip("变速功能已开启，请正确合理地使用该功能哦");

}
/**
 * @brief 一键换装备-时空
 * @return 无
 */
void MainWindow::Changebag_sk(){
    if(bind_status==false)
        Binddm();
    Changebag("时空");
    emit sendtip("一键更换时空成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-腐蚀者
 * @return 无
 */
void MainWindow::Changebag_fs(){
    if(bind_status==false)
        Binddm();
    Changebag("腐蚀者");
    emit sendtip("一键更换腐蚀者成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-零度
 * @return 无
 */
void MainWindow::Changebag_ld(){
    if(bind_status==false)
        Binddm();
    Changebag("零度");
    emit sendtip("一键更换零度成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-皇帝
 * @return 无
 */
void MainWindow::Changebag_hd(){
    if(bind_status==false)
        Binddm();
    Changebag("皇帝");
    emit sendtip("一键更换皇帝成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-毒液
 * @return 无
 */
void MainWindow::Changebag_dy(){
    if(bind_status==false)
        Binddm();
    Changebag("毒液");
    emit sendtip("一键更换毒液成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-笑傲
 * @return 无
 */
void MainWindow::Changebag_xa(){
    if(bind_status==false)
        Binddm();
    Changebag("笑傲");
    emit sendtip("一键更换笑傲成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-未来
 * @return 无
 */
void MainWindow::Changebag_wl(){
    if(bind_status==false)
        Binddm();
    Changebag("未来");
    emit sendtip("一键更换未来成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-元神
 * @return 无
 */
void MainWindow::Changebag_ys(){
    if(bind_status==false)
        Binddm();
    Changebag("元神");
    emit sendtip("一键更换元神成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-天尊
 * @return 无
 */
void MainWindow::Changebag_tz(){
    if(bind_status==false)
        Binddm();
    Changebag("天尊");
    emit sendtip("一键更换天尊成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-银翼骑士
 * @return 无
 */
void MainWindow::Changebag_yy(){
    if(bind_status==false)
        Binddm();
    Changebag("银翼骑士");
    emit sendtip("一键更换银翼成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-天启
 * @return 无
 */
void MainWindow::Changebag_tq(){
    if(bind_status==false)
        Binddm();
    Changebag("天启");
    emit sendtip("一键更换天启成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-浴火
 * @return 无
 */
void MainWindow::Changebag_yh(){
    if(bind_status==false)
        Binddm();
    Changebag("浴火");
    emit sendtip("一键更换浴火成功啦，快看看换好的套装吧");
}
/**
 * @brief 一键换装备-主函数
 * @param name 要换的装备名
 * @return 无
 */
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
/**
 * @brief 一键换装备-打开装备背包
 * @return 无
 */
void Openbag(){
    QVariant x,y;
    while(dm.FindPic(18,11,526,316,"查看个人信息.bmp","000000",0.8,0,x,y)==-1){
        dm.MoveTo(670,293);
        dm.LeftClick();
        Delay(500);
    }
}
/**
 * @brief 一键换装备-搜索装备
 * @param pid 窗口id
 * @param name 要换的装备名
 * @return 无
 */
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
/**
 * @brief 一键换装备-穿上装备
 * @return 无
 */
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
/**
 * @brief 打开自定义脚本
 * @return 无
 */
void MainWindow::Openscript(){
    //打开脚本
    QProcess pro;
    QString strPath = allpath+"/工具/自定义脚本工具.exe";
    pro.startDetached(strPath);
    emit sendtip("自定义脚本工具加载中，发挥你的创意吧");
}

/**
 * @brief 一键输入cdk
 * @return 无
 */
void MainWindow::Inputcdk(){
    //一键输入cdk
    if(cd==NULL)
        cd=new CdkForm();
    if(bind_status==false)
        Binddm();
    cd->show();
}
/**
 * @brief 打开橙汁赛尔数值计算器
 * @return 无
 */
void MainWindow::seer_cal(){
    QProcess pro;
    QString strPath = allpath+"/工具/赛尔数据计算器/赛尔数据计算器.exe";
    pro.startDetached(strPath);
    emit sendtip("赛尔数值计算器正在加载中（by橙汁）");
}
/**
 * @brief 打开精灵技能快查窗口
 * @return 无
 */
void MainWindow::PeakMode(){
    //精灵技能快查
    emit signal_openskill();
}
/**
 * @brief 打开登录器使用说明介绍
 * @return 无
 */
void MainWindow::slot_shiyongshuoming(){
    QDesktopServices::openUrl(QUrl("https://www.bilibili.com/video/BV1qz411B7En"));
}
/**
 * @brief 打开项目源码仓库
 * @return 无
 */
void MainWindow::slot_xiangmuyuanma(){
    QDesktopServices::openUrl(QUrl("https://github.com/Starlitnightly/seer_logon"));
}
/**
 * @brief 查看免责协议
 * @return 无
 */
void MainWindow::slot_mianzexieyi(){
    if(ato==NULL)
        ato=new Atoken();
    ato->show();

}
/**
 * @brief 查看作者与鸣谢信息
 * @return 无
 */
void MainWindow::slot_author(){
    QMessageBox::about(NULL,"help","作者：星夜\n"
                                         "联系QQ：2681686121\n"
                                         "\n"
                                         "-\n "
                                         "用户鸣谢:\n"
                                         "小鸽子 \n"
                                         "潜水人员\n"
                                         "於城\n"
                                         "对本登录器的开发提出的建议与帮助\n"
                                         "\n-\n"
                                         );
}
/**
 * @brief 主窗口关闭重载函数
 * @param event 关闭活动
 * @return 无
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    exit(0);
}
/*以下函数作废*/
void MainWindow::GreenfireTimer(){
    //绿火计时器
}
void MainWindow::ChangeSpirit(){
    //一键换精灵窗口
}
void MainWindow::ChangeBag(){
    //一键换背包
}
void MainWindow::ChangeSpeedPrepare()
{
}
void MainWindow::ChangeSpeed()
{


}









