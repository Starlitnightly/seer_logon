/**
 * @file nono.cpp
 * @brief nono主窗口及其相关
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "nono.h"
#include "ui_nono.h"
/**
 * @brief nono窗口构造函数
 * @param parent 父类指针
 * @return 无
 */
Nono::Nono(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nono)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);

    this->setWindowOpacity(1);//设置窗体不透明
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);//设置窗体无边框,允许任务栏按钮右键菜单
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    //vipfire
    QPixmap pixmap(allpath+"/gif/buff_VIP_5.png");
    ui->label_2->setPixmap(pixmap);
    ui->label_2->show();
    qDebug()<<"绿火初始化无问题";
    QFont font ( "Microsoft YaHei", 10, 75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    //QFont font1("Microsoft YaHei", 15,75);
    ui->label_3->setFont(font);
    //ui->label_6->setFont(font1);

    int fontId = QFontDatabase::addApplicationFont(allpath + "/font/RuiZiZhenYanTiMianFeiShangYong-2.ttf");
    qDebug()<<allpath + "/font/RuiZiZhenYanTiMianFeiShangYong-2.ttf";
    qDebug() << "fontId = "<< fontId;
    QString nonot = QFontDatabase::applicationFontFamilies(fontId).at(0);
    qDebug() <<"fontname = " <<nonot;
    QFont font1(nonot,12);
    ui->label_6->setFont(font1);//设置控件自定义字体
    qDebug()<<"nono字体无问题";


    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    hidecap=true;

    /*初始化时间*/
    time = new QTime();
    timer = new QTimer();

    time1 = new QTime();
    timer1 = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_timer_timeout()));
    connect(timer1,SIGNAL(timeout()),this,SLOT(slot_nono_change()));
    freshlabel=new ClickedLabel(this);
    freshlabel->setGeometry(120,420,50,50);
    connect(freshlabel,SIGNAL(Clicked(ClickedLabel*)),this,SLOT(slot_Fresh()));
    shibielabel=new ClickedLabel(this);
    shibielabel->setGeometry(120,530,50,50);
    connect(shibielabel,SIGNAL(Clicked(ClickedLabel*)),this,SLOT(slot_shibie()));
    //connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(slot_startedTimer_clicked(bool)));
    qDebug()<<"nono时间无问题";
    //nonogif
    mouseMovePos = QPoint(0, 0);
    movie = new QMovie(allpath+"/gif/nono3.gif");
    movie1 = new QMovie(allpath+"/gif/nono_1_1.gif");
    movie2 = new QMovie(allpath+"/gif/nono_2_1.gif");
    movie3 = new QMovie(allpath+"/gif/nono_3_1.gif");
    movie4 = new QMovie(allpath+"/gif/nono_4_1.gif");
    ui->label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
    movie->start(); // 2. 启动动画
    ui->label->show();
    qDebug()<<"nonogif无问题";
    //cap
    clabel =new ClickedLabel(this);
    clabel->setGeometry(50,0,396,345);
    connect(clabel,SIGNAL(Clicked(ClickedLabel*)),this,SLOT(slot_hidecap()));

    //定时更换nono
    time1->restart();
    timer1->start(1000);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    tmp1=GetCurrentProcessId();
    //识别
    pt=new Pettip();
    connect(pt,SIGNAL(sendmes(QString)),this,SLOT(slot_tip(QString)));
    connect(this,SIGNAL(signal_pet(QString)),pt,SLOT(slot_getname(QString)));
}

/**
 * @brief 绿火计时器开启函数
 * @param bool 信号传递
 * @return 无
 */
void Nono::slot_startedTimer_clicked(bool)
{
    qDebug()<<tr("开启计时器");
    time->restart();
    timer->start(1000);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
}
/**
 * @brief 绿火计时器停止函数
 * @param bool 信号传递
 * @return 无
 */
void Nono::slot_stopedTimer_clicked(bool)
{
    qDebug()<<tr("停止计时器");
    timer->stop();
}
/**
 * @brief nono状态改变
 * @note 此函数控制nono的自动提示、自动动作
 * @return 无
 */
void Nono::slot_nono_change(){


    int t=time1->elapsed()/1000;
    int k=qrand()%4;
    if(t%15==0){
        double t2=xy_memory(tmp1);
        if(t2>600)
            slot_tip("当前内存使用:"+QString::number(t2)+"MB(内存占用较大及时刷新避免卡顿)");
        else
            slot_tip("当前内存使用:"+QString::number(t2)+"MB");
    }

    if(t%30==0){
        if(k==0){
            ui->label->setMovie(movie1); // 1. 设置要显示的 GIF 动画图片
            movie1->start(); // 2. 启动动画
            Delay(4000);
            ui->label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
            movie->start(); // 2. 启动动画
        }else if(k==2){
            ui->label->setMovie(movie3); // 1. 设置要显示的 GIF 动画图片
            movie3->start(); // 2. 启动动画
            Delay(3000);
            ui->label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
            movie->start(); // 2. 启动动画
        }else if(k==1){
            ui->label->setMovie(movie2); // 1. 设置要显示的 GIF 动画图片
            movie2->start(); // 2. 启动动画
            Delay(3500);
            ui->label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
            movie->start(); // 2. 启动动画
        }else if(k==3){
            ui->label->setMovie(movie4); // 1. 设置要显示的 GIF 动画图片
            movie4->start(); // 2. 启动动画
            Delay(3000);
            ui->label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
            movie->start(); // 2. 启动动画
        }

    }
    if(this->underMouse()){
        ui->label_7->setVisible(true);
        ui->label_8->setVisible(true);
        ui->label_9->setVisible(true);
        ui->label_10->setVisible(true);
        ui->label_11->setVisible(true);
        ui->label_12->setVisible(true);
    }else{
        ui->label_7->setVisible(false);
        ui->label_8->setVisible(false);
        ui->label_9->setVisible(false);
        ui->label_10->setVisible(false);
        ui->label_11->setVisible(false);
        ui->label_12->setVisible(false);
    }

}
/**
 * @brief 绿火计时器每秒处理动作
 * @return 无
 */
void Nono::slot_timer_timeout(){
    firetime=1800-(time->elapsed()/1000);
    //qDebug()<<firetime;
    firetime_min=firetime/60;
    //qDebug()<<firetime_min;
    firetime_sec=firetime-firetime_min*60;
    //qDebug()<<firetime_sec;
    QString tmp=QString::number(firetime_min,10)+":"+QString::number(firetime_sec,10);
    //qDebug()<<tmp;
    if(firetime<10){
        timer->stop();
    }
    ui->label_3->setText(tmp);
}

/**
 * @brief nono窗口析构函数
 * @return 无
 */
Nono::~Nono()
{
    delete ui;
    delete movie;
    delete movie1;
    delete movie2;
    delete movie3;
    delete movie4;

    delete time;
    delete timer;

    delete time1;
    delete timer1;
    delete clabel;
    delete freshlabel;
    delete shibielabel;

    delete nam;
    delete pt;
}
/**
 * @brief 显示对面巅峰阵容-nono举牌
 * @param tmp 信号传递
 * @return 无
 */
void Nono::slot_capture(bool tmp){
    dm.Capture( 564, 223, 960, 568,QDir::currentPath()+"/screen.bmp");
    QPixmap pixmap(QDir::currentPath()+"/screen.bmp");
    ui->label_4->setPixmap(pixmap);
    ui->label_4->show();
    ui->label_4->setVisible(true);
    hidecap=false;

}

/**
 * @brief 鼠标按下nono窗口并移动重载
 * @param event 鼠标活动
 * @return 无
 */
void  Nono::mouseMoveEvent(QMouseEvent *event)
{

    if(mouseMovePos != QPoint(0, 0))
    {

        move(geometry().x() + event->globalPos().x() - mouseMovePos.x(),
              geometry().y() + event->globalPos().y() - mouseMovePos.y());
        mouseMovePos = event->globalPos();



    }
}


/**
 * @brief 鼠标按下nono窗口重载
 * @param event 鼠标活动
 * @return 无
 */
void  Nono::mousePressEvent(QMouseEvent *event)
{
    mouseMovePos = event->globalPos();
}
/**
 * @brief 鼠标离开nono窗口重载
 * @param event 鼠标活动
 * @return 无
 */
void  Nono::mouseReleaseEvent(QMouseEvent *event)
{
    mouseMovePos = QPoint(0, 0);
}
/**
 * @brief nono窗口提示信息
 * @param content nono提示内容
 * @return 无
 */
void Nono::slot_tip(QString content){
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_6->setText(content);
    Delay(4000);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);

}
/**
 * @brief 巅峰阵容截图隐藏
 * @return 无
 */
void Nono::slot_hidecap(){
    if(hidecap==true){
        hidecap=false;
        ui->label_4->setVisible(true);
    }else{
        hidecap=true;
        ui->label_4->setVisible(false);
    }
}
/**
 * @brief 鼠标释放重载-带点击事件label类
 * @param evt 鼠标活动
 * @return 无
 */
void ClickedLabel::mouseReleaseEvent(QMouseEvent *evt)
{
    emit Clicked(this);
}
/**
 * @brief 刷新按钮按下
 * @note 向主窗口发送刷新信号
 * @return 无
 */
void Nono::slot_Fresh(){
    emit signal_fresh();
}
/**
 * @brief 识别对战精灵
 * @note 调用了百度ocr的ai，每日50000次，按理说是无问题的，毕竟登录器使用量没那么大
 * @return 无
 */
void Nono::slot_shibie(){
    emit signal_sb();
    Delay(100);
    getAccessToken("RwoxBEWTWXq1rKhiWGQT3UD3","X1TGKuGKClEmP6MAMg5Nw61G2yTBHtMt");
    recognition();
}
/**
 * @brief 获取百度ocr的accesstoken
 * @note 每30天获取一次
 * @param key 百度ocr的key
 * @param secret 百度ocr的secret
 * @return 无
 */
void Nono::getAccessToken(QString key, QString secret)
{

    QSettings *configIniWrite = new QSettings("set.ini", QSettings::IniFormat);
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();

    if((configIniWrite->value("tokenTime").toInt() + 30*24*3600) < timeT){
        nam = new QNetworkAccessManager(this);
        QString parm = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id="+key+"&client_secret="+secret+"&";
        QUrl url(parm);
        connect(nam, &QNetworkAccessManager::finished,this, &Nono::getAccessTokenRequestFinished);
        QNetworkReply* reply = nam->get(QNetworkRequest(url));
    }else{
        accessToken = configIniWrite->value("accessToken").toString();
    }
    qDebug()<<"access"<<accessToken;
}
/**
 * @brief 识别对面精灵的名字
 * @note 带点的精灵识别不一定成功
 * @return 无
 */
void Nono::recognition(){
    dm.Capture(893,90,965,108,QDir::currentPath()+"/shi.bmp");
    QImage image(QDir::currentPath()+"/shi.bmp");
    QByteArray ba;
    QBuffer buf(&ba);
    image.save(&buf, "bmp");
    QByteArray hexed = ba.toBase64();
    buf.close();
    //qDebug()<<"hexed"<<hexed;
    QString parm = QString(hexed);
    if(parm.isEmpty()){
        QMessageBox::information(NULL, "错误", "图像数据不能为空");
        return;
    }
    nam = new QNetworkAccessManager(this);
    QUrl url;
    url.setUrl("https://aip.baidubce.com/rest/2.0/ocr/v1/general_basic?access_token="+accessToken);

    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    QByteArray byteArr;

    byteArr.append("image=");
    byteArr.append(QUrl::toPercentEncoding(parm));
    connect(nam, &QNetworkAccessManager::finished,this, &Nono::recognitionRequestFinished);
    QNetworkReply* reply = nam->post(request,byteArr);
}
/**
 * @brief 获取accesstoken网页返回内容处理
 * @param reply 网页返回内容指针
 * @return 无
 */
void Nono::getAccessTokenRequestFinished(QNetworkReply* reply) {
    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "accFailed: " << reply->errorString();
    }else {
        // 获取返回内容
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(reply->readAll(), &json_error);
        if(parse_doucment.isObject()){
             QJsonObject obj = parse_doucment.object();
             accessToken = obj.take("access_token").toString();
             QSettings *configIniWrite = new QSettings("set.ini", QSettings::IniFormat);
            //向ini文件中写入内容,setValue函数的两个参数是键值对
            configIniWrite->setValue("accessToken", accessToken);
            QDateTime time = QDateTime::currentDateTime();   //获取当前时间
            int timeT = time.toTime_t();   //将当前时间转为时间戳
            configIniWrite->setValue("tokenTime", timeT);
            //写入完成后删除指针
            delete configIniWrite;
        }
    }
    nam->deleteLater();
}

/**
 * @brief Nono::recognitionRequestFinished
 * @param reply
 * 文字识别的信号槽
 */
void Nono::recognitionRequestFinished(QNetworkReply* reply){
    QNetworkReply::NetworkError err = reply->error();
    //qDebug()<<reply->readAll();
    if(err != QNetworkReply::NoError) {
        qDebug() << "ocrFailed: " << reply->errorString();
    }else {
        // 获取返回内容
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(reply->readAll(), &json_error);
        if(parse_doucment.isObject()){
            QJsonObject obj = parse_doucment.object();
            int wordsNum = obj.take("words_result_num").toInt();
            if(wordsNum > 0){
                QString res;
                QJsonArray jsonArr = obj.take("words_result").toArray();
                for(int i=0;i<wordsNum;i++){
                   res.append(jsonArr[i].toObject().take("words").toString());

                }
                pt->show();
                qDebug()<<res;
                emit signal_pet(res);
                slot_tip(res);

            }else{
                slot_tip("未检测到精灵");
            }
        }
    }
    nam->deleteLater();
}
/**
 * @brief 打开精灵技能快查窗口
 * @return 无
 */
void Nono::showskill(){
    pt->show();

}
