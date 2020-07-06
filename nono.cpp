#include "nono.h"
#include "ui_nono.h"

Nono::Nono(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nono)
{
    ui->setupUi(this);

    this->setWindowOpacity(1);//设置窗体不透明
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);//设置窗体无边框,允许任务栏按钮右键菜单
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    //vipfire
    QPixmap pixmap("F:/untitled/buff_VIP_5.png");
    ui->label_2->setPixmap(pixmap);
    ui->label_2->show();

    QFont font ( "Microsoft YaHei", 10, 75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    //QFont font1("Microsoft YaHei", 15,75);
    ui->label_3->setFont(font);
    //ui->label_6->setFont(font1);

    int fontId = QFontDatabase::addApplicationFont(QDir::currentPath() + "/font/RuiZiZhenYanTiMianFeiShangYong-2.ttf");
    qDebug() << "fontId = "<< fontId;
    QString nonot = QFontDatabase::applicationFontFamilies(fontId).at(0);
    qDebug() <<"fontname = " <<nonot;
    QFont font1(nonot,12);
    ui->label_6->setFont(font1);//设置控件自定义字体


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

    //nonogif
    mouseMovePos = QPoint(0, 0);
    movie = new QMovie("F:/untitled/nono3.gif");
    movie1 = new QMovie("F:/untitled/nono_1_1.gif");
    movie2 = new QMovie("F:/untitled/nono_2_1.gif");
    movie3 = new QMovie("F:/untitled/nono_3_1.gif");
    movie4 = new QMovie("F:/untitled/nono_4_1.gif");
    ui->label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
    movie->start(); // 2. 启动动画
    ui->label->show();

    //cap
    clabel =new ClickedLabel(this);
    clabel->setGeometry(50,0,396,345);
    connect(clabel,SIGNAL(Clicked(ClickedLabel*)),this,SLOT(slot_hidecap()));

    //定时更换nono
    time1->restart();
    timer1->start(1000);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}


void Nono::slot_startedTimer_clicked(bool)
{
    qDebug()<<tr("开启计时器");
    time->restart();
    timer->start(1000);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
}

void Nono::slot_stopedTimer_clicked(bool)
{
    qDebug()<<tr("停止计时器");
    timer->stop();
}

void Nono::slot_nono_change(){
    int t=time1->elapsed()/1000;
    int k=qrand()%4;
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


Nono::~Nono()
{
    delete ui;
}

void Nono::slot_capture(bool tmp){
    dm.Capture( 564, 223, 960, 568,QDir::currentPath()+"/screen.bmp");
    QPixmap pixmap(QDir::currentPath()+"/screen.bmp");
    ui->label_4->setPixmap(pixmap);
    ui->label_4->show();
    ui->label_4->setVisible(true);
    hidecap=false;

}

//鼠标按下并移动则移动不规则窗体
void  Nono::mouseMoveEvent(QMouseEvent *event)
{

    if(mouseMovePos != QPoint(0, 0))
    {

        move(geometry().x() + event->globalPos().x() - mouseMovePos.x(),
              geometry().y() + event->globalPos().y() - mouseMovePos.y());
        mouseMovePos = event->globalPos();



    }
}



void  Nono::mousePressEvent(QMouseEvent *event)
{
    mouseMovePos = event->globalPos();
}
void  Nono::mouseReleaseEvent(QMouseEvent *event)
{
    mouseMovePos = QPoint(0, 0);
}

void Nono::slot_tip(QString content){
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_6->setText(content);
    Delay(5000);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);

}

void Nono::slot_hidecap(){
    if(hidecap==true){
        hidecap=false;
        ui->label_4->setVisible(true);
    }else{
        hidecap=true;
        ui->label_4->setVisible(false);
    }
}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *evt)
{
    emit Clicked(this);
}

void Nono::slot_Fresh(){
    emit signal_fresh();
}

void Nono::slot_shibie(){
    //
}
