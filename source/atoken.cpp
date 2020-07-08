/**
 * Created by Starlitnightly
 * @file atoken.cpp
 * @brief 免责协议窗口及其相关函数
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "atoken.h"
#include "ui_atoken.h"
/**
 * @brief 免责协议窗口构造函数
 * @param parent 父类指针
 * @return 无
 */
Atoken::Atoken(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Atoken)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);
    QSettings *configIniWrite = new QSettings(allpath+"/set.ini", QSettings::IniFormat);

    //向ini文件中写入内容,setValue函数的两个参数是键值对
    uu=configIniWrite->value("agree").toString();
    if(configIniWrite->value("agree").toString()!="true")
    {
        ui->pushButton->setEnabled(false);
    }else
        ui->pushButton->setEnabled(true);
    delete configIniWrite;

    time = new QTime();
    timer = new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(slot_timer_timeout()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(slot_agree()));
    time->start();
    timer->start(1000);
    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    show();
}
/**
 * @brief 免责协议窗口析构函数
 * @return 无
 */
Atoken::~Atoken()
{
    delete ui;
    delete time;
    delete timer;
}
/**
 * @brief 免责协议窗口关闭重载函数
 * @param event 关闭活动
 * @return 无
 */
void Atoken::closeEvent(QCloseEvent *event)
{
    //QMessageBox::about(NULL,"tip","本窗口禁止关闭哦");
    show();
    qDebug()<<"???";
}
/**
 * @brief 免责协议窗口槽函数-定时器处理内容
 * @note 30s后同意按钮才可按下
 * @return 无
 */
void Atoken::slot_timer_timeout(){
    int firetime=30-(time->elapsed()/1000);
    //qDebug()<<firetime;
    //qDebug()<<firetime_sec;
    //qDebug()<<tmp;

    if(firetime<3){
        ui->pushButton->setEnabled(true);
        setAttribute(Qt::WA_DeleteOnClose);
    }else if(firetime>=3 && uu!="true"){
        Qt::WindowFlags m_flags = windowFlags();
        setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
        show();
    }   
    ui->label->setText("等待"+QString::number(firetime)+"s后才能确认");
}
/**
 * @brief 免责协议窗口槽函数-同意按钮按下处理内容
 * @note 写配置下一次窗口不会自动弹出
 * @return 无
 */
void Atoken::slot_agree(){
    this->hide();
    QSettings *configIniWrite = new QSettings(allpath+"/set.ini", QSettings::IniFormat);
    //向ini文件中写入内容,setValue函数的两个参数是键值对
    configIniWrite->setValue("agree", "true");
    delete configIniWrite;

}
