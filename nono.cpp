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
    ui->label_3->setFont(font);

    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);


    /*初始化时间*/
    time = new QTime();
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_timer_timeout()));
    //connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(slot_startedTimer_clicked(bool)));

    //nonogif
    mouseMovePos = QPoint(0, 0);
    QMovie *movie = new QMovie("F:/untitled/nono3.gif");
    ui->label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
    movie->start(); // 2. 启动动画
    ui->label->show();
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
