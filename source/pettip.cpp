/**
 * @file pettip.cpp
 * @brief 精灵技能快查窗口及其相关
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "pettip.h"
#include "ui_pettip.h"
#include <QString>
#include "ext.h"
/**
 * @brief 精灵技能快查窗口构造函数
 * @param parent 父类指针
 * @return 无
 */
Pettip::Pettip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pettip)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);
    //ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件ID
    //ui->axWidget->setProperty("DisplayAlerts",false);//不显示警告信息
    //ui->axWidget->setProperty("DisplayScrollBars",true);//不显示滚动条
    m_manager = new QNetworkAccessManager(this);//新建QNetworkAccessManager对象
    connect(m_manager, SIGNAL(finished(QNetworkReply    *)), this, SLOT(slot_replayFinished(QNetworkReply*))); //关联信号和槽
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(slot_buttonget()));

    QFile file(allpath+"/json/data.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
    jsonObject = document.object();




}
/**
 * @brief 精灵技能查询
 * @return 无
 */
void Pettip::slot_buttonget(){
    petname=ui->textEdit->toPlainText();
    qDebug()<<jsonObject[petname];
    if(jsonObject[petname].isNull())
        emit sendmes("当前精灵不存在，请输入完整名字");
    else{
    if (!(parseJsonErr.error == QJsonParseError::NoError)) {
        qDebug()<<"配置文件错误！";
        return;
    }
    emit sendmes(petname+"的技能查询中");
    m_manager->get(QNetworkRequest(QUrl(jsonObject[petname].toString())));//发送请求
    }
}
/**
 * @brief 读取json中精灵名称对应的图鉴地址
 * @param name 精灵名称
 * @return 无
 */
void Pettip::slot_getname(QString name){

    petname=name;
    qDebug()<<jsonObject[petname];
    if(jsonObject[petname].isNull())
        emit sendmes("当前精灵不存在，请输入完整名字");
    else{
        if (!(parseJsonErr.error == QJsonParseError::NoError)) {
            qDebug()<<"配置文件错误！";
            return;
        }
        m_manager->get(QNetworkRequest(QUrl(jsonObject[petname].toString())));//发送请求
    }
}
/**
 * @brief 精灵技能快查窗口析构函数
 * @return 无
 */
Pettip::~Pettip()
{
    delete ui;
    delete m_manager;
}
/**
 * @brief 展示查询内容（ie控件模式）
 * @return 无
 * 已作废，换用table来展示
 */
void Pettip::slot_tip(){
    //ui->axWidget->setControl(QString::fromUtf8("{d27cdb6e-ae6d-11cf-96b8-444553540000}"));
    //ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件ID
    //QString str=QString("http://news.4399.com/seer/tujian/64106.htm");//设置要打开的网页
    //ui->axWidget->dynamicCall("Navigate(QString)",str);//显示网页


}
/**
 * @brief 读取精灵技能
 * @param reply 网页返回内容
 * @return 无
 */
void Pettip::slot_replayFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
        //使用utf8编码, 这样可以显示中文
    QString str = codec->toUnicode(reply->readAll());
    //qDebug()<<str;
    str.replace(QString("\n"), QString(""));
    str.replace(QString("\t"), QString(""));
    str.replace(QString("\r"), QString(""));

    QString tmp;
    QStringList li=str.split("<tbody>");
    QStringList li1;
    for(int i=0;i<li.length();i++){
        li1=li[i].split("</tbody>");
        if(li1.length()!=0)
            tmp=li1[0];
    }
    //tmp.replace("<td>","");
    //tmp.replace("</td>","");
    ui->tableWidget->clear();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    li=tmp.split("</tr>");
    QStringList header;
    header << QStringLiteral("技能名") << QStringLiteral("攻击类型") << QStringLiteral("威力")<<QStringLiteral("PP")<<QStringLiteral("学习等级")<<"技能效果";
    ui->tableWidget->setRowCount(li.length());
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(5,QHeaderView::ResizeToContents);
    for(int i=0;i<li.length();i++){
        li1=li[i].split("</td>");
        for(int j=0;j<li1.length();j++){
           li1[j].replace("<td>","");
           li1[j].replace("<td style=\"text-align:left\">","");
           li1[j].replace("<tr>","");
           li1[j].replace("<tr class=\"odd\">","");
           if(li1[j].indexOf("check")!=-1 || li1[j].indexOf("rel")!=-1)
               break;
           ui->tableWidget->setItem(i, j, new QTableWidgetItem(li1[j]));
           qDebug()<<li1[j];
        }
    }
    //qDebug()<<str.indexOf("<tbody>");
    //qDebug()<<str.indexOf("</tbody>");
    //qDebug()<<str.mid(str.indexOf("<tbody>"),str.indexOf("</tbody>"));
    //qDebug()<<str;
    //QRegExp rx("<tbody.*?>*</tbody>");
    //QRegExp rx("[a-zA-z]+://[^\\s]*");
    //int pos = rx.indexIn(str);
    //qDebug() << pos;
    //for(int i=0;i<pos;i++)
    //    qDebug()<<rx.cap(i);
    reply->deleteLater();//最后要释放replay对象
}
