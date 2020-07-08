/**
 * @file form.cpp
 * @brief 脚本窗口及其相关
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "form.h"
#include "ui_form.h"

#include <QDebug>
#include <QThread>
#include <QObject>


/**
 * @brief 脚本窗口析构函数
 * @return 无
 */
Form::~Form()
{
    delete ui;
    delete script_fw;
    delete script_gem;
    delete script_hdblk;
    delete script_jlw;
    delete script_spt;
    delete script_team;
    delete script_tower;
    delete script_vip;
    delete script_wish;
    delete script_xxlzc;

    delete script_auto;
    delete script_top;
    delete script_searles;
    delete script_sixworld;
}
/**
 * @brief 脚本窗口构造函数
 * @param parent 父类指针
 * @return 无
 */
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(test()));//开始运行
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(test2()));//停止运行

    //单选框选中1槽函数
    connect(ui->radio_fw,SIGNAL(clicked(bool)),this,SLOT(fw_selected()));//飞王单选框被选中
    connect(ui->radio_gem,SIGNAL(clicked(bool)),this,SLOT(gem_selected()));//一键宝石单选框被选中
    connect(ui->radio_hdblk,SIGNAL(clicked(bool)),this,SLOT(hdblk_selected()));//混沌布莱克脚本单选框被选中
    connect(ui->radio_jlw,SIGNAL(clicked(bool)),this,SLOT(jlw_selected()));//精灵王大乱斗单选框被选中
    connect(ui->radio_spt,SIGNAL(clicked(bool)),this,SLOT(spt_selected()));//spt徽章单选框被选中
    connect(ui->radio_team,SIGNAL(clicked(bool)),this,SLOT(team_selected()));//一键战队贡献单选框被选中
    connect(ui->radio_tower,SIGNAL(clicked(bool)),this,SLOT(tower_selected()));//勇者之塔单选框被选中
    connect(ui->radio_vip,SIGNAL(clicked(bool)),this,SLOT(vip_selected()));//vip单选框被选中
    connect(ui->radio_wish,SIGNAL(clicked(bool)),this,SLOT(wish_selected()));//许愿单选框被选中
    connect(ui->radio_xxlzc,SIGNAL(clicked(bool)),this,SLOT(xxlzc_selected()));//学习力战场单选框被选中
    //巅峰单选框槽函数
    connect(ui->top_jj,SIGNAL(clicked(bool)),this,SLOT(top_jj_selected()));
    connect(ui->top_ky,SIGNAL(clicked(bool)),this,SLOT(top_ky_selected()));
    connect(ui->top_33,SIGNAL(clicked(bool)),this,SLOT(top_33_selected()));
    //圣瑞
    connect(ui->radio_searles,SIGNAL(clicked(bool)),this,SLOT(searles_selected()));
    //六界
    connect(ui->radio_sixworld,SIGNAL(clicked(bool)),this,SLOT(sixworld_selected()));

    script_fw=NULL;
    script_gem=NULL;
    script_hdblk=NULL;
    script_jlw=NULL;
    script_spt=NULL;
    script_team=NULL;
    script_tower=NULL;
    script_vip=NULL;
    script_wish=NULL;
    script_xxlzc=NULL;

    script_auto=NULL;
    script_top=NULL;
    script_searles=NULL;
    script_sixworld=NULL;

    QString iniFilePath = allpath+"/圣瑞次数统计.ini";  //路径
    qDebug()<<iniFilePath;
    QSettings settings(iniFilePath,QSettings::IniFormat);
    QString searles_cz = settings.value("times/reset").toString();
    searles_reset=searles_cz.toInt();
    ui->label_2->setText("重置次数:"+searles_cz);
    qDebug()<<"重置次数"<<searles_cz;
    QString searles_fi = settings.value("times/fight").toString();
    searles_fight=searles_fi.toInt();
    ui->label_3->setText("挑战次数:"+searles_fi);
    qDebug()<<"挑战次数"<<searles_fi;
    QString searles_lo = settings.value("times/lose").toString();
    searles_lose=searles_lo.toInt();
    ui->label_4->setText("战败次数:"+searles_lo);
    qDebug()<<"战败次数"<<searles_lo;

    //重置次数显示
    settings.setValue("次数统计/重置次数",QString::number(searles_reset,10));

}


/**
 * @brief 脚本说明提示函数
 * @param msg 脚本说明内容
 * @return 无
 */
void Form::showMessageBox(QString msg){
    qDebug()<<msg;
    ui->textEdit->setPlainText(msg);
    //QMessageBox::information(NULL,"this",msg);
}

/**
 * @brief 开启脚本
 * @return 无
 */
void Form::test(){

    qDebug()<<mode;
    if(mode=="fw"){
        if(script_fw==NULL)
            script_fw=new Fw(this);
        script_fw->status=true;
        fw_allactive=false;
        fw_llactive=false;
        fw_lqactive=false;
        fw_cxactive=false;

        script_fw->start();
    }else if(mode=="gem"){
        if(script_gem==NULL)
            script_gem=new Gem(this);
        script_gem->status=true;
        script_gem->now=10;

        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;

        script_gem->start();
        script_auto->start();

    }else if(mode=="hdblk"){
        if(script_hdblk==NULL)
            script_hdblk=new Hdblk(this);
        script_hdblk->status=true;

        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;

        script_hdblk->start();
        script_auto->start();

    }else if(mode=="jlw"){
        if(script_jlw==NULL)
            script_jlw=new Jlw(this);
        script_jlw->status=true;
        qDebug()<<"精灵王脚本初始化成功";
        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;
        qDebug()<<"自动确认初始化成功";

        script_jlw->start();
        qDebug()<<"精灵王脚本开始成功";
        Delay(1000);
        script_auto->start();
        qDebug()<<"自动确认开始成功";

    }else if(mode=="spt"){
        if(script_spt==NULL)
            script_spt=new Spt(this);
        script_spt->status=true;

        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;

        script_spt->start();
        script_auto->start();

    }else if(mode=="team"){
        if(script_team==NULL)
            script_team=new Team(this);
        script_team->status=true;
        connect(script_team,SIGNAL(sendMessage(QString)),this,SLOT(showMessageBox(QString)));

        friend_click=false;
        script_team->now=4;

        script_team->start();
    }else if(mode=="vip"){
        if(script_vip==NULL)
            script_vip=new Vip(this);
        script_vip->status=true;

        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;

        script_vip->now=1;

        script_vip->start();
        script_auto->start();

    }else if(mode=="wish"){
        if(script_wish==NULL)
            script_wish=new Wish(this);
        script_wish->status=true;

        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;

        panel_wish=0;

        script_wish->start();
        script_auto->start();

    }else if(mode=="xxlzc"){
        if(script_xxlzc==NULL)
            script_xxlzc=new Xxlzc(this);
        script_xxlzc->status=true;

        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;

        jinglingjineng="第一";

        script_xxlzc->start();
        script_auto->start();

    }else if(mode=="top_jj" || mode=="top_ky" || mode=="top_33"){
        if(script_top==NULL)
            script_top=new Top(this);
        script_top->status=true;

        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;

        script_top->mode=mode;
        if(ui->checkBox->isChecked())
            script_top->robot=true;
        else
            script_top->robot=false;
        jinglingjineng="第一";
        script_top->start();
        script_auto->start();

    }else if(mode=="searles"){
        if(script_searles==NULL)
            script_searles=new Searles(this);
        script_searles->status=true;

        connect(script_searles,SIGNAL(sendreset(QString)),this,SLOT(showreset(QString)));
        connect(script_searles,SIGNAL(sendlose(QString)),this,SLOT(showlose(QString)));
        connect(script_searles,SIGNAL(sendfight(QString)),this,SLOT(showfight(QString)));

        script_searles->start();

    }else if(mode=="sixworld"){
        if(script_sixworld==NULL)
            script_sixworld=new Sixworld(this);
        script_sixworld->status=true;

        if(script_auto==NULL)
            script_auto=new AutoC(this);
        script_auto->status=true;

        script_sixworld->start();
        script_auto->start();

    }

}

/**
 * @brief 圣瑞脚本重置次数显示
 * @param msg 重置次数
 * @return 无
 */
void Form::showreset(QString msg){
    ui->label_2->setText("重置次数:"+msg);
}
/**
 * @brief 圣瑞脚本战败次数显示
 * @param msg 战败次数
 * @return 无
 */
void Form::showlose(QString msg){
    ui->label_4->setText("战败次数:"+msg);
}
/**
 * @brief 圣瑞脚本挑战次数显示
 * @param msg 挑战次数
 * @return 无
 */
void Form::showfight(QString msg){
    ui->label_3->setText("挑战次数:"+msg);
}
/**
 * @brief 脚本停止函数
 * @return 无
 */
void Form::test2(){
    if(mode=="fw")
        script_fw->status=false;
    else if(mode=="gem"){
        script_gem->status=false;
        script_auto->status=false;
    }else if(mode=="hdblk"){
        script_hdblk->status=false;
        script_auto->status=false;
    }else if(mode=="jlw"){
        script_jlw->status=false;
        script_auto->status=false;
    }else if(mode=="spt"){
        script_spt->status=false;
        script_auto->status=false;
    }else if(mode=="team"){
        script_team->status=false;
    }else if(mode=="vip"){
        script_vip->status=false;
        script_auto->status=false;
    }else if(mode=="wish"){
        script_wish->status=false;
        script_auto->status=false;
    }else if(mode=="xxlzc"){
        script_xxlzc->status=false;
        script_auto->status=false;
    }else if(mode=="top_jj" || mode=="top_ky" || mode=="top_33" || mode=="top_robot"){
        script_top->status=false;
        script_auto->status=false;
    }else if(mode=="xxlzc"){
        script_xxlzc->status=false;
        script_auto->status=false;
    }else if(mode=="searles"){
        script_searles->status=false;
    }else if(mode=="sixworld"){
        script_sixworld->status=false;
        script_auto->status=false;
    }
}

/**
 * @brief 飞王脚本单选框被选中后初始化
 * @return 无
 */
void Form::fw_selected(){
    QString text;
    text=QString("脚本使用说明：首发艾欧，第一个技能有女(带上绿火)\n\n背包带上圣普");
    ui->textEdit->setPlainText(text);
    mode="fw";
}
/**
 * @brief 一键抽宝石/刻印脚本单选框被选中后初始化
 * @return 无
 */
void Form::gem_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="gem";
}
/**
 * @brief 混沌布莱克脚本单选框被选中后初始化
 * @return 无
 */
void Form::hdblk_selected(){
    QString text;
    text=QString("脚本使用说明：\n首发王哈（带先三）\n背包艾欧（带魂魄缠绕）\n索总（带先三）\n幻境（带精神幻灭）");
    ui->textEdit->setPlainText(text);
    mode="hdblk";
}
/**
 * @brief 精灵王大乱斗脚本单选框被选中后初始化
 * @return 无
 */
void Form::jlw_selected(){
    QString text;
    text=QString("脚本使用说明：在竞技天堂（有精灵王装置的地图）运行脚本");
    ui->textEdit->setPlainText(text);
    mode="jlw";
}
/**
 * @brief spt徽章脚本单选框被选中后初始化
 * @return 无
 */
void Form::spt_selected(){
    QString text;
    text=QString("脚本使用说明：首发幻境，第一个技能精神幻灭");
    ui->textEdit->setPlainText(text);
    mode="spt";
}
/**
 * @brief 战队贡献脚本单选框被选中后初始化
 * @return 无
 */
void Form::team_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="team";
}
/**
 * @brief 勇者之塔脚本单选框被选中后初始化
 * @return 无
 */
void Form::tower_selected(){
    QString text;
    text=QString("脚本使用说明：30分钟后再点一次");
    ui->textEdit->setPlainText(text);
    mode="tower";
}
/**
 * @brief vip礼包脚本单选框被选中后初始化
 * @return 无
 */
void Form::vip_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="vip";
}
/**
 * @brief 一键许愿脚本单选框被选中后初始化
 * @return 无
 */
void Form::wish_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="wish";
}
/**
 * @brief 学习力战场脚本单选框被选中后初始化
 * @return 无
 */
void Form::xxlzc_selected(){
    QString text;
    text=QString("脚本使用说明：在学习力战场副本运行脚本，首发艾欧，第一个技能有女");
    ui->textEdit->setPlainText(text);
    mode="xxlzc";
}
/**
 * @brief 巅峰竞技脚本单选框被选中后初始化
 * @return 无
 */
void Form::top_jj_selected(){
    QString text;
    text=QString("脚本使用说明：在巅峰地图运行脚本");
    ui->textEdit->setPlainText(text);
    mode="top_jj";
}
/**
 * @brief 巅峰狂野脚本单选框被选中后初始化
 * @return 无
 */
void Form::top_ky_selected(){
    QString text;
    text=QString("脚本使用说明：在巅峰地图运行脚本");
    ui->textEdit->setPlainText(text);
    mode="top_ky";
}
/**
 * @brief 巅峰33脚本单选框被选中后初始化
 * @return 无
 */
void Form::top_33_selected(){
    QString text;
    text=QString("脚本使用说明：在巅峰地图运行脚本");
    ui->textEdit->setPlainText(text);
    mode="top_33";
}
/**
 * @brief 圣战瑞尔斯脚本单选框被选中后初始化
 * @return 无
 */
void Form::searles_selected(){
    QString text;
    text=QString("脚本使用说明：表姐（天尊）首发， 王哈，毁灭(可选)");
    ui->textEdit->setPlainText(text);
    mode="searles";
}
/**
 * @brief 六界神王脚本单选框被选中后初始化
 * @return 无
 */
void Form::sixworld_selected(){
    QString text;
    text=QString("脚本使用说明：看图");
    ui->textEdit->setPlainText(text);
    mode="sixworld";
}


/**
 * @brief 勇者之塔脚本-线程启动函数
 * @return 无
 */
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

/**
 * @brief 飞王脚本-检查首发
 * @param shoufajingling 要检查的精灵
 * @return 返回当前首发是否与检查相同
 *   @retval true 当前首发与检查相同
 *   @retval false 当前首发与检查不同
 */
bool Fw::jianchashoufa(QString shoufajingling){
    //QVariant x,y;
    Delay(1000);
    QString tmp=dm.Ocr(194,376,293,477,"ffffff-111111",1.0);
    if(tmp.contains(shoufajingling)){
        qDebug()<<shoufajingling;
        qDebug()<<tmp;
        dangqianshoufa=shoufajingling;
        dm.MoveTo(940,28);
        dm.LeftClick();
        return true;
    }else{
        qDebug()<<shoufajingling;
        qDebug()<<tmp;
        return false;
    }
}
/**
 * @brief 飞王脚本-设置首发
 * @param shoufajingling 要设置的精灵
 */
void Fw::shezhishoufa(QString shoufajingling){
    QVariant x,y;
    while(jianchashoufa(shoufajingling)==false){
        if(dm.FindStr(192,377,791,476,shoufajingling,"ffffff-111111",0.9,x,y)!=-1){
            qDebug()<<x.toInt()<<y.toInt();
            dm.MoveTo(x.toInt()+5,y.toInt()+20);
            dm.LeftClick();
            dm.LeftClick();
            dm.LeftClick();
            if(dm.FindStr(0,0,1000,600,"fw-sf.bmp","000000",0.9,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(jianchashoufa(shoufajingling)){
                dangqianshoufa=shoufajingling;
                break;
            }
        }
    }
}
/**
 * @brief 飞王脚本-线程启动函数
 * @return 无
 */
void Fw::run(){
    QVariant x,y;
    while(status==true){
        if(dangqianjingling!="艾欧丽娅" && xy_shibiejifangjingling()=="艾欧丽娅")
            jinglingjineng="有女初长成1";
        dangqianjingling=xy_shibiejifangjingling();
        if(dangqianjingling=="圣灵谱尼")
            jinglingjineng="第五";
        if(dm.FindPic( 0, 0, 1000, 600, "fw-djjh.bmp", "000000", 0.9, 0, x, y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            fw_allactive=false;
        }
        if(dm.FindPic(0,0,1000,600,"fw-djjh.bmp","000000",0.9,0,x,y)==-1 && dm.FindPic( 0, 0, 1000, 600, "fw-pd1.bmp", "000000", 0.9, 0, x, y)!=-1)
            fw_allactive=true;
        if(dm.FindPic(0,0,1000,600,"fw-lq.bmp|fw-lq1.bmp","000000",0.9,0,x,y)!=-1)
            fw_lqactive=true;
        if(dm.FindPic(0,0,1000,600,"fw-ll.bmp|fw-ll1.bmp","000000",0.9,0,x,y)!=-1)
            fw_llactive=true;
        if(dm.FindPic(0,0,1000,600,"fw-cx.bmp|fw-cx.bmp","000000",0.9,0,x,y)!=-1)
            fw_cxactive=true;
        qDebug()<<fw_lqactive<<fw_llactive<<fw_cxactive;
        if(fw_allactive==true && fw_lqactive==true && fw_llactive==true && fw_cxactive==true){
            fw_trueactive=true;
            //QMessageBox::information(NULL,"this","三种效果已成功打完");
            break;
        }else
            fw_trueactive=false;

        if(fw_allactive==true && fw_trueactive==false){
            if(dm.FindPic(0,0,1000,600,"fw-bf.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"fw-wg.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"fw-bs.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"fw-js.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"fw-qz.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
        }

        if(fw_allactive==false || fw_trueactive==false){
            if(dm.FindPic(150,189,329,223,"fw-lj0.bmp","000000",0.9,0,x,y)!=-1 && dangqianshoufa!="艾欧丽娅"){
                if(dm.FindPic(0,0,1000,600,"fw-bb.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                }
            }
            if(dm.FindPic(0,0,1000,600,"fw-zdmb1.bmp","000000",0.9,0,x,y)!=-1 && dangqianshoufa=="艾欧丽娅"){
                dm.MoveTo(169,485);
                dm.LeftClick();
                fw_goal="第一";
            }
            if(dm.FindPic(172,283,295,384,"fw-wc1.bmp","000000",0.9,0,x,y)!=-1 && dangqianshoufa=="艾欧丽娅"){
                dm.MoveTo(415,485);
                dm.LeftClick();
                fw_goal="第二";
            }
            if(dm.FindPic(172,283,295,384,"fw-wc1.bmp","000000",0.9,0,x,y)!=-1 && dm.FindPic(435, 296, 539, 364,"fw-wc2.bmp","000000",0.9,0,x,y)!=-1){
                if(dm.FindPic(679, 184, 800, 231,"fw-30.bmp","000000",0.9,0,x,y)!=-1){
                    if(dangqianshoufa!="艾欧丽娅"){
                        if(dm.FindPic(0,0,1000,600,"fw-bb.bmp","000000",0.9,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                        }
                        if(jianchashoufa("艾欧丽娅")==false)
                            shezhishoufa("艾欧丽娅");
                    }else if(dangqianshoufa=="艾欧丽娅"){
                        dm.MoveTo(689,485);
                        dm.LeftClick();
                        fw_goal="第三0";
                    }
                }else if(dm.FindPic(679, 184, 800, 231,"fw-31.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(689,485);
                    dm.LeftClick();
                    fw_goal="第三1";
                }else if(dm.FindPic(679, 184, 800, 231,"fw-32.bmp","000000",0.9,0,x,y)!=-1){
                    if(dangqianshoufa!="圣灵谱尼"){
                        if(dm.FindPic(0,0,1000,600,"fw-bb.bmp","000000",0.9,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                        }
                        if(jianchashoufa("圣灵谱尼")==false)
                            shezhishoufa("圣灵谱尼");
                    }else if(dangqianshoufa=="圣灵谱尼"){
                        dm.MoveTo(689,485);
                        dm.LeftClick();
                        fw_goal="第三2";
                    }
                }
            }
            if(fw_goal=="第一" || fw_goal=="第二" || fw_goal=="第三0" || fw_goal=="第三1"){
                if(dangqianjingling=="艾欧丽娅")
                    xy_skill("有女初长成1","jn-ynczc.bmp","有女初长成1");

            }else if(fw_goal=="第三2"){
                if(dangqianjingling=="圣灵谱尼")
                    xy_skill("第五","","第五");
            }

        }
        //确认
        if(dm.FindPic(0,0,1000,600,"fw-zdqr.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"fw-sbqr.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"fw-cxjhqr.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(319,180,656,399,"fw-xgqr.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }

        Delay(200);
    }
}

/**
 * @brief 一键刻印/宝石抽奖脚本-线程启动函数
 * @return 无
 */
void Gem::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(1, 46, 105, 135,"rc-scxb.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt()+7,y.toInt()+7);
            dm.LeftClick();
        }

        if(now==10){
            if(dm.FindPic(75, 59, 754, 435,"rc-3-4.bmp|rc-3-4-1.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(888,73);
                dm.LeftClick();
                now=11;
            }else {
                if(dm.FindPic(0,0,1000,600,"rc-ky.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(489,492);
                    dm.LeftClick();
                }
                if(dm.FindPic(0,0,1000,600,"rc-3-3.bmp|rc-3-3-1.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(484,509);
                    dm.LeftClick();
                }
            }
        }
        if(now==11){
            if(dm.FindPic(751, 136, 942, 258,"rc-bsm.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(790,78);
                dm.LeftClick();
                //QMessageBox::information(NULL,"this","宝石/刻印已抽完");
                break;
            }else {
                if(dm.FindPic(0,0,1000,600,"rc-bs.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                }
                if(dm.FindPic(0,0,1000,600,"rc-bsks.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                }
                if(dm.FindPic(0,0,1000,600,"rc-bsqr.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                }
                if(dm.FindPic(0,0,1000,600,"rc-bslq.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                }
                if(dm.FindPic(0,0,1000,600,"rc-bsqr2.bmp","000000",0.9,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                }

            }
        }
        Delay(500);
        qDebug()<<"宝石抽奖中";

    }
}
/**
 * @brief 混沌布莱克脚本-线程启动函数
 * @return 无
 */
void Hdblk::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(0,0,1000,600,"混布-宝箱.bmp","000000",0.8,0,x,y)==-1){
            if(dm.FindPic(0,0,1000,600,"混布-抽取对手.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"混布-开启挑战.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"混布-抽取对手3.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"混布-开启挑战3.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"混布-魔灵王一键.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }if(dm.FindPic(0,0,1000,600,"混布-690，592.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(690,592);
                dm.LeftClick();
            }
            xy_autofight();
            hdblk_scriptset();
            Delay(1000);
        }else
            break;
            //QMessageBox::information(NULL,"this","混布脚本已自动停止");
    }
}
/**
 * @brief 精灵王大乱斗脚本-线程启动函数
 * @return 无
 */
void Jlw::run(){
    QVariant x,y;
    qDebug()<<"进入精灵王脚本";
    while(status==true){
        //qDebug()<<"开始精灵王脚本";
        bool replenishpp=false;
        if(xy_shibiemap()!="竞技天堂" && dm.FindPic(0,0,1000,600,"dfpd11.bmp","000000",0.8,0,x,y)!=-1){
            if(dm.FindPic(0,0,1000,600,"rc-6-1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(489,546);
                dm.LeftClick();
            }
            Delay(300);
        }
        if(dm.FindPic(0,0,1000,600,"rc-6-2.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(454,148);
            dm.LeftClick();
        }
        OpenKingSpirit();
        xy_autofight();
        if(dm.FindPic(0,0,1000,600,"道具.bmp","000000",0.8,0,x,y)!=-1){
            if(dm.FindColorE( 13, 440, 76, 462, "93c1ca-000000", 1, 0)!="-1|-1" || dm.FindPic(14, 327, 971, 570, "0.bmp","000000",0.8,0,x,y)!=-1){
                replenishpp=true;
                if(script_repp==NULL)
                    script_repp=new Repp(this);
                script_repp->start();
            }
            if(replenishpp==false){
                if(dm.FindColor(18,476,89,493,"fffad4-000000",1,0,x,y)!=0){
                    dm.MoveTo(40,506);
                    dm.LeftClick();
                }
            }
        }

        Delay(1000);
    }
}
/**
 * @brief spt徽章脚本-线程启动函数
 * @return 无
 */
void Spt::run(){
    QVariant x,y;
    while(status==true){
        bool replenishpp=false;
        if(dm.FindPic(0,0,1000,600,"sptrespd.bmp|spt-jlbl.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(420,116);
            dm.LeftClick();
        }
        xy_autofight();
        if(dm.FindColorE( 13, 440, 76, 462, "93c1ca-000000", 1, 0)!="-1|-1" || dm.FindPic(14, 327, 971, 570, "0.bmp","000000",0.8,0,x,y)!=-1){
            replenishpp=true;
            if(script_repp==NULL)
                script_repp=new Repp(this);
            script_repp->start();
        }
        if(replenishpp==false){
            if(dm.FindColor(18,476,89,493,"fffad4-000000",1,0,x,y)!=0){
                dm.MoveTo(40,506);
                dm.LeftClick();
            }
        }
        Delay(1000);

    }
}
/**
 * @brief 一键战队贡献脚本-线程启动函数
 * @return 无
 */
void Team::run(){
    QVariant x,y;
    while(status==true){
        if(now==4){
            if(friend_click!=true){
                while(now!=5){
                    if(dm.FindPic(12,388,438,560,"rc-4-1.bmp","000000",0.9,0,x,y)==-1 && now==4){
                        dm.MoveTo(249,546);
                        dm.LeftClick();
                    }
                    Delay(500);
                    if(dm.FindPic(12,388,438,560,"rc-4-1.bmp","000000",0.9,0,x,y)!=-1 && now==4){
                        friend_click=true;
                        break;
                    }
                    Delay(100);
                }
            }
            if(dm.FindPic(0,0,438,560,"rc-4-1.bmp","000000",0.9,0,x,y)!=-1 && now==4){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
                Delay(1000);
            }
            if(dm.FindPic(0,0,438,560,"rc-4-2.bmp","000000",0.9,0,x,y)!=-1 && now==4){
                dm.MoveTo(x.toInt()+5,y.toInt());
                dm.LeftClick();
                now=5;
                panel_open=false;
            }
        }
        if(xy_shibiemap()=="战队总部"){
            now=5;
            panel_open=false;
        }
        if(now==5){
            if(panel_open==false){
                if(dm.FindPic(0,0,1000,600,"rc-4-3.bmp","000000",0.9,0,x,y)!=-1 && now==4){
                    dm.MoveTo(860,213);
                    dm.LeftClick();
                    Delay(100);
                    dm.MoveTo(860,213);
                    dm.LeftClick();
                    if(dm.FindPic(0,0,1000,600,"rc-5-4.bmp|rc-5-1.bmp","000000",0.9,0,x,y)!=-1 && now==4){
                        dm.MoveTo(442,488);
                        dm.LeftClick();
                    }
                }
                if(xy_shibiemap()=="战队总部"){
                    dm.MoveTo(860,213);
                    dm.LeftClick();
                    dm.LeftClick();
                    Delay(500);
                    dm.MoveTo(860,213);
                    dm.LeftClick();
                    dm.LeftClick();
                }
            }
            qDebug()<<"面板已开"<<panel_open;
            if(dm.FindPic(309,15,696,111,"zd-zyzx.bmp","000000",0.9,0,x,y)!=-1)
                panel_open=true;
            if(panel_open==true){
                if(dm.FindPic(0,0,1000,600,"rc-5-2.bmp","000000",0.9,0,x,y)!=-1 && now==5){
                    while(dm.FindPic(0,0,1000,600,"rc-5-3.bmp","000000",0.9,0,x,y)==-1){
                        dm.MoveTo(684,333);
                        dm.LeftClick();
                        Delay(100);
                        qDebug()<<dm.Ocr(718,310,939,371,"996600-444444|ffffff-000000",1);
                        if(dm.Ocr(718,310,939,371,"996600-444444|ffffff-000000",1).contains("今日还能生产0"))
                            break;
                        if(dm.Ocr(825,312,907,361,"ffffff-000000",1).contains("0"))
                            break;
                        if(dm.FindPic(480,300,1000,600,"11.bmp","000000",0.9,0,x,y)!=-1)
                            break;
                    }
                }
            }

            if(now==5 && panel_open==true){
                if(dm.FindPic(480,300,1000,600,"11.bmp","000000",0.9,0,x,y)!=-1
                        || dm.FindPic(480,300,1000,600,"zd-sc0c.bmp","000000",0.9,0,x,y)!=-1
                        || dm.FindPic(0,0,1000,600,"rc-5-3.bmp","000000",0.9,0,x,y)!=-1
                        || dm.FindPic(825,388,1207,540,"rczd0.bmp","000000",0.9,0,x,y)!=-1
                        || dm.FindPic(474,232,848,434,"hkssc.bmp","000000",0.9,0,x,y)!=-1
                        || dm.FindPic(474,232,848,434,"hkssc1.bmp","000000",0.9,0,x,y)!=-1
                        || dm.Ocr(718,310,939,371,"996600-444444|ffffff-000000",1).contains("今日还能生产0")
                        || dm.Ocr(825,312,907,361,"ffffff-000000",1).contains("0")){
                    emit sendMessage(QString("一键战队贡献已完成"));
                    //QMessageBox::information(form_pointer,"this","一键战队贡献已完成");
                    break;
                }
            }
        }
        Delay(500);

    }
}
/**
 * @brief vip礼包领取脚本-线程启动函数
 * @return 无
 */
void Vip::run(){
    QVariant x,y;
    while(status==true){
        if(now==1){
            if(dm.FindPic(0,481,134,596,"rc-1-1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(56,510);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-1-2.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-1-3.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(713,59);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-1-4.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-1-5.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(483,359);
                dm.LeftClick();
                Delay(300);
                dm.MoveTo(855,70);
                dm.LeftClick();
                now=2;
            }
            if(dm.FindPic(0,0,1000,600,"rc-1-6.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(938,33);
                dm.LeftClick();
            }
        }else if(now==2){
            if(dm.FindPic(0,0,1000,600,"rc-2-1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(909,527);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-2-2.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(598,447);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"rc-2-3.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(941,29);
                dm.LeftClick();
                //QMessageBox::information(NULL,"this","礼包领取完毕");
                break;
            }
        }
        Delay(500);

    }
}
/**
 * @brief 一键许愿脚本-线程启动函数
 * @return 无
 */
void Wish::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(677,12,750,82,"rc-xy.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(583,108,949,391,"rc-xy1.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            panel_wish=1;
        }
        if(dm.FindPic(434,95,633,352,"rc-xy2.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(611,202,800,382,"rc-xyk.bmp","000000",0.9,0,x,y)==-1 && panel_wish==1){
            dm.MoveTo(703,476);
            dm.LeftClick();
        }
        Delay(500);


    }
}
/**
 * @brief 学习力战场脚本-线程启动函数
 * @return 无
 */
void Xxlzc::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(129,289,881,383,"jlxxl-kstz.bmp|jlxxl-kstz2.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt()+5,y.toInt()+5);
            dm.LeftClick();
        }else if(dm.FindPic(129,289,881,383,"jlxxl-kstz3.bmp|jlxxl-kstz4.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt()+5,y.toInt()+5);
            dm.LeftClick();
        }

        if(jinglingjineng=="第一"){
            if(dm.FindColor(284,509,297,518,"0388ec-000000",1,0,x,y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
                jinglingjineng="第一";
            }
        }
        Delay(500);

    }
}
/**
 * @brief 自动确认脚本-线程启动函数
 * @return 无
 */
void AutoC::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(0,0,1000,600,"战败确认.bmp|奖章确认.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"防沉迷提示.bmp|防沉迷提示1.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"超时确认.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"战胜确认.bmp|消息盒子x.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"胜利.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(479,425);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"巅峰自动x.bmp|nox.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"sptrespd1.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(943,31);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"bxss.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(431,360);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"rwmb.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(818,56);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"每周登录礼包.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(900,78);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"每周x.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"钻石好礼x.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(946,26);
            dm.LeftClick();
        }
        Delay(1000);
    }
}
/**
 * @brief 补pp-线程启动函数
 * @return 无
 */
void Repp::run(){
    QVariant x,y;
    if(dm.FindPic(0,0,1000,600,"道具.bmp","000000",0.8,0,x,y)!=-1){
        if(dm.FindColorE(13,440,76,462,"93c1ca-000000",1,0)!="-1|-1"){
            dm.MoveTo(923,450);
            dm.LeftClick();
            Delay(500);
            dm.MoveTo(206,450);
            dm.LeftClick();
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"10PP药.bmp|5PP药.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt()+5,y.toInt()+5);
                    dm.LeftClick();
                    break;
                }
            }
        }
        if(dm.FindPic(14,327,971,570,"0.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(923,450);
            dm.LeftClick();
            Delay(500);
            dm.MoveTo(206,450);
            dm.LeftClick();
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"10PP药.bmp|5PP药.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt()+5,y.toInt()+5);
                    dm.LeftClick();
                    break;
                }
            }
        }
    }
}
/**
 * @brief 巅峰脚本-线程启动函数
 * @return 无
 */
void Top::run(){
    QVariant x,y;
    while(status==true){
        bool replenishpp=false;

        jfjl=xy_shibiejifangjingling();
        dmjl=xy_shibieduifangjingling();
        qDebug()<<jfjl<<dmjl;

        if(dm.FindPic(0,0,1000,600,"操作超时.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(489,359);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"表姐自爆.bmp|机器人自爆.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(mode=="top_ky" || mode=="top_jj"){
            qDebug()<<"当前地图"<<xy_shibiemap();
            if(xy_shibiemap()!="圣战之巅" && dm.FindPic(0,0,1000,600,"dfpd11.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(772,35);
                dm.LeftClick();
            }
            if(xy_shibiemap()=="圣战之巅"){
                dm.MoveTo(492,231);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"xdf-szzd.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(492,231);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"巅峰.bmp","000000",0.8,0,x,y)==-1){
                if(dm.FindPic(0,0,1000,600,"圣战图标.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt()+5,y.toInt()+5);
                    dm.LeftClick();
                }
            }
            if(mode=="top_ky"){
                if(dm.FindPic(0,0,1000,600,"xdf-ky.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt()+5,y.toInt()+5);
                    dm.LeftClick();
                }
            }else if(mode=="top_jj"){
                if(dm.FindPic(0,0,1000,600,"xdf-jj.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt()+5,y.toInt()+5);
                    dm.LeftClick();
                }
            }
            if(dm.FindPicE(0,0,1000,600,"巅峰.bmp|狂野.bmp|竞技.bmp|注意.bmp","000000",0.8,0)!="-1|-1|-1"){
                if(script_pdtop==NULL)
                    script_pdtop=new Pdtop(this);
                script_pdtop->mode=mode;
                script_pdtop->start();
            }
            if(dm.FindPicE(0,0,1000,600,"ban.bmp","000000",0.8,0)!="-1|-1|-1"){
                if(script_ban3==NULL)
                    script_ban3=new Ban3(this);
                script_ban3->mode=mode;
                script_ban3->start();
            }
            if(dm.FindPic(0,0,1000,600,"×.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }

        }else if(mode=="top_33"){
            if(xy_shibiemap()=="圣战之巅"){
                dm.MoveTo(492,231);
                dm.LeftClick();
            }
            if(dm.FindPic(0,0,1000,600,"xdf-33.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }
            if(dm.FindPicE(0,0,1000,600,"进入33-1.bmp|进入33-2.bmp|注意.bmp","000000",0.8,0)!="-1|-1|-1"){
                if(script_pdtop==NULL)
                    script_pdtop=new Pdtop(this);
                script_pdtop->mode=mode;
                script_pdtop->start();
            }
            if(dm.FindPicE(0,0,1000,600,"ban.bmp|33ban.bmp","000000",0.8,0)!="-1|-1|-1"){
                if(script_ban3==NULL)
                    script_ban3=new Ban3(this);
                script_ban3->mode=mode;
                script_ban3->start();
            }
            if(dm.FindPic(0,0,1000,600,"×.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }
        }
        //自动克制系出战
        xy_autofight();

        if(mode=="top_ky" || mode=="top_jj" || mode=="top_robot"){
            if(dm.FindPic(0,0,1000,600,"首发.bmp|出战.bmp","000000",0.8,0,x,y)!=-1){
                if(script_explode==NULL)
                    script_explode=new Explode(this);
                script_explode->mode=mode;
                script_explode->start();
            }
        }
        if(mode=="top_33"){
            if(dm.FindPic(0,0,1000,600,"首发33.bmp|dfxzcz.bmp","000000",0.8,0,x,y)!=-1){
                if(script_explode==NULL)
                    script_explode=new Explode(this);
                script_explode->mode=mode;
                script_explode->start();
            }
        }
        if(robot==true){
            //智能出招（）
            Robotfight();

        }else{
            if(dm.FindPic(0,0,1000,600,"道具.bmp","000000",0.8,0,x,y)!=-1){
                if(dm.FindColorE( 13, 440, 76, 462, "93c1ca-000000", 1, 0)!="-1|-1" || dm.FindPic(14, 327, 971, 570, "0.bmp","000000",0.8,0,x,y)!=-1){
                    replenishpp=true;
                    if(script_repp==NULL)
                        script_repp=new Repp(this);
                    script_repp->start();
                }
                if(replenishpp==false){
                    if(dm.FindColor(18,476,89,493,"fffad4-000000",1,0,x,y)!=0){
                        dm.MoveTo(40,506);
                        dm.LeftClick();
                    }
                }
            }
        }



        if(dm.FindPic(0,0,1000,600,"确认1.bmp","000000",0.9,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        Delay(1000);

    }
}
/**
 * @brief 巅峰脚本-精灵智能出招函数
 * @return 无
 */
void Top::Robotfight(){
    QVariant x,y;
    bool replenishpp=false;

    if(dm.FindPic(0,0,1000,600,"道具.bmp","000000",0.8,0,x,y)!=-1){
        if(dm.FindColorE( 13, 440, 76, 462, "93c1ca-000000", 1, 0)!="-1|-1" || dm.FindPic(14, 327, 971, 570, "0.bmp","000000",0.8,0,x,y)!=-1){
            replenishpp=true;
            if(script_repp==NULL)
                script_repp=new Repp(this);
            script_repp->start();
        }
    }
    if(replenishpp==false){
        if(jinglingjineng=="第一"){
            if(dm.FindColor(284,509,297,518,"0388ec-000000",1,0,x,y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
                jinglingjineng="第五";
            }
        }else if(jinglingjineng=="第五"){
            if(dm.FindColor(18,476,89,493,"fffad4-000000",1,0,x,y)!=0){
                dm.MoveTo(40,506);
                dm.LeftClick();
                jinglingjineng="第一";
            }
        }
    }

}
/**
 * @brief 进入巅峰-线程启动函数
 * @return 无
 */
void Pdtop::run(){
    QVariant x,y;
    if(mode=="top_jj" || mode=="top_ky"){
        if(dm.FindPic(0,0,1000,600,"巅峰.bmp","000000",0.8,0,x,y)!=-1){
            qDebug()<<"巅峰";
            Delay(200);
            if(dm.FindPic(0,0,1000,600,"巅峰.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                for(int i=0;i<30;i++){
                    if(mode=="top_jj"){
                        if(dm.FindPic(0,0,1000,600,"竞技.bmp","000000",0.8,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                            break;
                        }
                    }
                    if(mode=="top_ky"){
                        if(dm.FindPic(0,0,1000,600,"狂野.bmp","000000",0.8,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                            break;
                        }
                    }
                    Delay(100);
                }
                for(int i=0;i<30;i++){
                    if(dm.FindPic(0,0,1000,600,"注意.bmp","000000",0.8,0,x,y)!=-1){
                        Delay(500);
                        dm.MoveTo(826,488);
                        dm.LeftClick();
                        qDebug()<<"已点击";
                        break;
                    }else
                        qDebug()<<"找不到";
                    Delay(100);
                }
            }
        }else {
            if(mode=="top_ky"){
                if(dm.FindPic(0,0,1000,600,"狂野.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    qDebug()<<"狂野";
                    for(int i=0;i<30;i++){
                        if(dm.FindPic(0,0,1000,600,"注意.bmp","000000",0.8,0,x,y)!=-1){
                            Delay(500);
                            dm.MoveTo(826,488);
                            dm.LeftClick();
                            qDebug()<<"已点击";
                            break;
                        }else
                            qDebug()<<"找不到";
                        Delay(100);
                    }
                }
            }
            if(mode=="top_jj"){
                if(dm.FindPic(0,0,1000,600,"竞技.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    qDebug()<<"竞技";
                    for(int i=0;i<30;i++){
                        if(dm.FindPic(0,0,1000,600,"注意.bmp","000000",0.8,0,x,y)!=-1){
                            Delay(500);
                            dm.MoveTo(826,488);
                            dm.LeftClick();
                            qDebug()<<"已点击";
                            break;
                        }else
                            qDebug()<<"找不到";
                        Delay(100);
                    }
                }
            }
            if(dm.FindPic(0,0,1000,600,"注意.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(826,488);
                dm.LeftClick();
            }

        }

    }else if(mode=="top_33"){
        if(dm.FindPic(0,0,1000,600,"进入33-1.bmp","000000",0.8,0,x,y)!=-1){
            qDebug()<<"巅峰";
            Delay(200);
            if(dm.FindPic(0,0,1000,600,"进入33-1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                for(int i=0;i<30;i++){
                    if(mode=="top_33"){
                        if(dm.FindPic(0,0,1000,600,"进入33-2.bmp","000000",0.8,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                            break;
                        }
                    }

                    Delay(100);
                }
                for(int i=0;i<30;i++){
                    if(dm.FindPic(0,0,1000,600,"注意.bmp","000000",0.8,0,x,y)!=-1){
                        Delay(500);
                        dm.MoveTo(826,488);
                        dm.LeftClick();
                        qDebug()<<"已点击";
                        break;
                    }else
                        qDebug()<<"找不到";
                    Delay(100);
                }
            }
        }else {
            if(mode=="top_33"){
                if(dm.FindPic(0,0,1000,600,"进入33-2.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    qDebug()<<"狂野";
                    for(int i=0;i<30;i++){
                        if(dm.FindPic(0,0,1000,600,"注意.bmp","000000",0.8,0,x,y)!=-1){
                            Delay(500);
                            dm.MoveTo(826,488);
                            dm.LeftClick();
                            qDebug()<<"已点击";
                            break;
                        }else
                            qDebug()<<"找不到";
                        Delay(100);
                    }
                }
            }

            if(dm.FindPic(0,0,1000,600,"注意.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(826,488);
                dm.LeftClick();
            }

        }
    }

}
/**
 * @brief ban黑屋-线程启动函数
 * @return 无
 */
void Ban3::run(){
    QVariant x,y;
    int ban=0;
    if(mode=="top_ky" || mode=="top_jj"){
        if(dm.FindPic(480,0,1000,600,"大葱.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"光嘤.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"帝姬.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"ban启灵.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"天尊.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"banchongsheng.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(ban>=3){
            for(int i=0;i<60;i++){
                if(dm.FindPic(0,0,1000,600,"确认.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
            }
        }else{
            dm.MoveTo(612,268);
            dm.LeftClick();
            dm.MoveTo(712,268);
            dm.LeftClick();
            dm.MoveTo(812,268);
            dm.LeftClick();
            dm.MoveTo(912,268);
            dm.LeftClick();
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"确认.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
            }
        }
    }else if(mode=="top_33"){
        if(dm.FindPic(480,0,1000,600,"bansp.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"bantl.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"banjg.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"bandz.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"banxh.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"bantz.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(dm.FindPic(480,0,1000,600,"bancs.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            ban++;
        }
        if(ban>=2){
            for(int i=0;i<60;i++){
                if(dm.FindPic(0,0,1000,600,"确认.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
            }
        }else{
            dm.MoveTo(650,309);
            dm.LeftClick();
            dm.MoveTo(770,309);
            dm.LeftClick();
            dm.MoveTo(840,309);
            dm.LeftClick();
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"确认.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
            }
        }
    }
}
/**
 * @brief 首发与出战-线程启动函数
 * @return 无
 */
void Explode::run(){
    QVariant x,y;
    if(mode=="top_33"){
        if(dm.FindPic(0,0,1000,600,"首发33.bmp|33首发.bmp","000000",0.8,0,x,y)!=-1){
            //自动33首发()
            auto33first();
            for(int i=0;i<10;i++){
                if(dm.FindPic(0,0,1000,600,"确认.bmp|确认1.bmp|df33.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt()+10,y.toInt()+10);
                    dm.LeftClick();
                    break;
                }
            }
        }
        //自动33出战（）
        auto33fight();
        for(int i=0;i<10;i++){
            if(dm.FindPic(0,0,1000,600,"确认.bmp|确认1.bmp|df33.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+10,y.toInt()+10);
                dm.LeftClick();
                break;
            }
            if(dm.FindPic(527,253,616,286,"df332.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(423,362);
                dm.LeftClick();
                break;
            }
        }


    }else if(mode=="top_jj" || mode=="top_ky"){
        if(dm.FindPic(0,0,1000,600,"首发.bmp","000000",0.8,0,x,y)!=-1){
            //自动首发（）
            autofirst();
            //自动出战（）
            autofight();
            for(int i=0;i<10;i++){
                if(dm.FindPic(0,0,1000,600,"确认.bmp|确认1.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt()+10,y.toInt()+10);
                    dm.LeftClick();
                    break;
                }
            }
        }
        if(dm.FindPic(0,0,1000,600,"出战.bmp","000000",0.8,0,x,y)!=-1){
            //自动首发（）
            autofirst();
            //自动出战（）
            autofight();
            for(int i=0;i<10;i++){
                if(dm.FindPic(0,0,1000,600,"确认.bmp|确认1.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt()+10,y.toInt()+10);
                    dm.LeftClick();
                    break;
                }
            }
        }
    }

}
/**
 * @brief 首发与出战-自动33首发
 * @return 无
 */
void Explode::auto33first(){
    QVariant x,y;
    if(dm.FindPic(0,0,1000,600,"首发33.bmp|33首发.bmp","000000",0.8,0,x,y)!=-1){
        Delay(1000);
        if(dm.FindPic(0,0,600,559,"wpdn.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt()+5,y.toInt()+5);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,600,559,"wlh.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt()+5,y.toInt()+5);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,600,559,"wsz.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt()+5,y.toInt()+5);
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,600,559,"wzh.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt()+5,y.toInt()+5);
            dm.LeftClick();
        }

    }
}
/**
 * @brief 首发与出战-自动66首发
 * @return 无
 */
void Explode::autofirst(){
    QVariant x,y;
    bool shoufayixuan=false;
    if(dm.FindPic(469,12,958,559,"禁用.bmp","000000",0.8,0,x,y)!=-1){
        Delay(1000);
        if(shoufayixuan!=true){
            if(dm.FindPic(0,0,600,559,"pnsf.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }else if(dm.FindPic(0,0,600,559,"sfkl.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }else if(dm.FindPic(0,0,600,559,"xwsf.bmp|xwsf.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }else if(dm.FindPic(0,0,600,559,"gwsf.bmp|gwsf1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }else if(dm.FindPic(0,0,600,559,"lh.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }else if(dm.FindPic(0,0,600,559,"lhsf.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }else if(dm.FindPic(0,0,600,559,"pdl.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }else if(dm.FindPic(0,0,600,559,"sz.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }else if(dm.FindPic(0,0,600,559,"zh.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt()+5,y.toInt()+5);
                dm.LeftClick();
            }

        }
    }
}
/**
 * @brief 首发与出战-自动33出战
 * @return 无
 */
void Explode::auto33fight(){
    QVariant x,y;
    if(dm.FindPic(11, 232, 85, 317, "df33-jy.bmp|df33-sf.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(70,298);
       dm.LeftClick();
    }
    if(dm.FindPic(140, 232, 211, 337, "df33-jy.bmp|df33-sf.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(198,298);
       dm.LeftClick();
    }
    if(dm.FindPic(270, 232, 340, 337, "df33-jy.bmp|df33-sf.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(345,298);
       dm.LeftClick();
    }
    if(dm.FindPic( 11, 382, 85, 468, "df33-jy.bmp|df33-sf.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(70,468);
       dm.LeftClick();
    }
    if(dm.FindPic( 140, 382, 210, 468, "df33-jy.bmp|df33-sf.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(198,468);
       dm.LeftClick();
    }
    if(dm.FindPic( 270, 382, 340, 468, "df33-jy.bmp|df33-sf.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(345,468);
       dm.LeftClick();
    }
    for(int i=0;i<10;i++){
        if(dm.FindPic(0,0,1000,600,"确认.bmp|确认1.bmp|df33qr.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt()+10,y.toInt()+10);
            dm.LeftClick();
            break;
        }
        if(dm.FindPic(527, 253, 616, 286,"df332.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(423,362);
            dm.LeftClick();
            break;
        }
    }
}
/**
 * @brief 首发与出战-自动66出战
 * @return 无
 */
void Explode::autofight(){
    QVariant x,y;
    if(dm.FindPic(11, 221, 112, 337, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(11+25,246);
       dm.LeftClick();
    }
    if(dm.FindPic(109, 221, 211, 337, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(122+25,246);
       dm.LeftClick();
    }
    if(dm.FindPic(211, 221, 307, 337, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(211+25,246);
       dm.LeftClick();
    }
    if(dm.FindPic(307, 221, 404, 337, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(307+25,246);
       dm.LeftClick();
    }
    if(dm.FindPic(11, 337, 112, 455, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(11+25,362);
       dm.LeftClick();
    }
    if(dm.FindPic(109, 337, 211, 455, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(122+25,362);
       dm.LeftClick();
    }
    if(dm.FindPic(211, 337, 307, 455, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(211+25,362);
       dm.LeftClick();
    }
    if(dm.FindPic(307, 337, 404, 455, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(307+25,362);
       dm.LeftClick();
    }
    if(dm.FindPic(11, 455, 112, 564, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(11+25,480);
       dm.LeftClick();
    }
    if(dm.FindPic(109, 455, 211, 564, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(122+25,480);
       dm.LeftClick();
    }
    if(dm.FindPic(211, 455, 307, 564, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(211+25,480);
       dm.LeftClick();
    }
    if(dm.FindPic(307, 455, 404, 564, "禁用.bmp|首发小图.bmp","000000",0.8,0,x,y)!=-1){
       dm.MoveTo(307+25,480);
       dm.LeftClick();
    }

}

/**
 * @brief 圣瑞脚本-线程启动函数
 * @return 无
 */
void Searles::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(0,0,1000,600,"重置.bmp","000000",0.8,0,x,y)!=-1){
            if(dm.FindPic(0,0,1000,600,"重置.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                searles_reset++;
                QString iniFilePath = allpath+"/圣瑞次数统计.ini";  //路径
                QSettings settings(iniFilePath,QSettings::IniFormat);
                //重置次数显示
                emit sendreset(QString::number(searles_reset,10));
                settings.setValue("times/reset",QString::number(searles_reset,10));
            }
        }else if(dm.FindPic(0,0,1000,600,"胜利.bmp","000000",0.8,0,x,y)!=-1){
            if(dm.FindPic(0,0,1000,600,"战胜确认.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
        }else if(dm.FindPic(0,0,1000,600,"击败.bmp","000000",0.8,0,x,y)!=-1){
            if(dm.FindPic(0,0,1000,600,"战败确认.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                searles_lose++;
                QString iniFilePath = allpath+"/圣瑞次数统计.ini";  //路径
                QSettings settings(iniFilePath,QSettings::IniFormat);
                //重置次数显示
                emit sendlose(QString::number(searles_lose,10));
                settings.setValue("times/lose",QString::number(searles_lose,10));
            }
        }else if(dm.FindPic(0,0,1000,600,"融入圣光.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            searles_fight++;
            QString iniFilePath = allpath+"/圣瑞次数统计.ini";  //路径
            QSettings settings(iniFilePath,QSettings::IniFormat);
            //重置次数显示
            emit sendfight(QString::number(searles_fight,10));
            settings.setValue("times/fight",QString::number(searles_fight,10));
        }else if(dm.FindPic(0,0,1000,600,"天尊.bmp|表姐自爆.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"王哈出战.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"出战按钮.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
                Delay(100);
            }
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"王哈第五.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
                Delay(100);
            }
        }else if(dm.FindPic(0,0,1000,600,"幻境出战.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"出战按钮.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
                Delay(100);
            }
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"幻境第五.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
                Delay(100);
            }
        }else if(dm.FindPic(0,0,1000,600,"毁灭出战.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"出战按钮.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
                Delay(100);
            }
            for(int i=0;i<30;i++){
                if(dm.FindPic(0,0,1000,600,"毁灭.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    break;
                }
                Delay(100);
            }
        }else if(dm.FindPic(0,0,1000,600,"王哈第五.bmp|毁灭.bmp|幻境第五.bmp|重置确认.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        Delay(1000);
    }
}

/**
 * @brief 六界脚本-线程启动函数
 * @return 无
 */
void Sixworld::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(0,0,1000,600,"六界-天玄.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"六界-瀚海.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"六界-地葬.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"六界-混沌.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"六界-时空.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"六界-幻境.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }else if(dm.FindPic(0,0,1000,600,"六界-六界.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        Delay(500);
        god_condition();
        god_condition();
        god_condition();
        god_method(god);
        if(dm.FindPic(0,0,1000,600,"六界-开启认可.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
    }
}
/**
 * @brief 六界脚本-判断当前界王要求
 * @return 无
 */
void Sixworld::god_condition(){
    if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("最后一击使用致命一击战胜"))
        god=1;
    else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("处于满体力时战胜"))
        god=2;
    else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("最后一击使用物理攻击战胜"))
        god=3;
    else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("最后一击使用先制攻击战胜"))
        god=4;
    else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("6个回合以后战胜")){
        god=5;
        explode_death=true;
    }else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("3个回合以内战胜"))
        god=6;
    else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("处于能力提升状态下战胜")){
        god=7;
        jinglingjineng="王哈-强化";
    }else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("最后一击使用特殊攻击战胜"))
        god=8;
    else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("使用<3个精灵战胜"))
        god=9;
    else if(dm.Ocr(343, 538, 542, 563, "ffffff-111111",1).contains("最后一击使用必中攻击战胜"))
        god=10;

}
/**
 * @brief 六界脚本-对战中更换精灵
 * @param sp 要更换出战的精灵
 * @return 无
 */
void Sixworld::god_changesp(QString sp){
    QVariant x,y;
    if(dm.FindPic(7,340,968,569,sp,"000000",0.8,0,x,y)!=-1){
        dm.MoveTo(x.toInt(),y.toInt());
        dm.LeftClick();
        for(int i=0;i<30;i++){
            if(dm.FindPic(0,0,1000,600,"出战按钮.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                break;
            }
        }
    }
}
/**
 * @brief 六界脚本-检查首发
 * @param shoufajingling 要检查的精灵
 * @return 返回当前首发是否与检查相同
 *   @retval true 当前首发与检查相同
 *   @retval false 当前首发与检查不同
 */
bool Sixworld::jianchashoufa(QString shoufajingling){
    //QVariant x,y;
    Delay(1000);
    QString tmp=dm.Ocr(194,376,293,477,"ffffff-111111",1.0);
    if(tmp.contains(shoufajingling)){
        qDebug()<<shoufajingling;
        qDebug()<<tmp;
        dangqianshoufa=shoufajingling;
        dm.MoveTo(940,28);
        dm.LeftClick();
        return true;
    }else{
        qDebug()<<shoufajingling;
        qDebug()<<tmp;
        return false;
    }
}
/**
 * @brief 六界脚本-设置首发
 * @param shoufajingling 要设置的精灵
 * @return 无
 */
void Sixworld::shezhishoufa(QString shoufajingling){
    QVariant x,y;
    while(jianchashoufa(shoufajingling)==false){
        if(dm.FindStr(192,377,791,476,shoufajingling,"ffffff-111111",0.9,x,y)!=-1){
            qDebug()<<x.toInt()<<y.toInt();
            dm.MoveTo(x.toInt()+5,y.toInt()+20);
            dm.LeftClick();
            dm.LeftClick();
            dm.LeftClick();
            if(dm.FindStr(0,0,1000,600,"fw-sf.bmp","000000",0.9,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(jianchashoufa(shoufajingling)){
                dangqianshoufa=shoufajingling;
                break;
            }
        }
    }
}
/**
 * @brief 六界脚本-对战出战设置
 * @param method 界王条件
 * @return 无
 */
void Sixworld::god_method(int method){
    QVariant x,y;
    dangqianjingling=xy_shibiejifangjingling();
    if(method==1 || method==2 || method==3 || method==6 || method==9 || method==10){
        if(dangqianshoufa!="幻影蝶" && dangqianshoufa!="帝皇之御"){
            if(dm.FindPic(25, 497, 208, 572, "六界-bb.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(jianchashoufa("幻影蝶")==false && jianchashoufa("帝皇之御")==false){
                qDebug()<<"进入循环";
                while(jianchashoufa("幻影蝶")==false && jianchashoufa("帝皇之御")==false){
                    if(dm.FindStr(192, 377, 791, 476, "幻影蝶|帝皇之御","ffffff-111111",0.9,x,y)!=-1){
                        dm.MoveTo(x.toInt()+5,y.toInt()+20);
                        dm.LeftClick();
                        dm.LeftClick();
                        dm.LeftClick();
                        if(dm.FindPic(0,0,1000,600, "fw-sf.bmp","000000",0.9,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                        }
                        if(jianchashoufa("幻影蝶")){
                            dangqianshoufa="幻影蝶";
                            break;
                        }else if(jianchashoufa("帝皇之御")){
                            dangqianshoufa="帝皇之御";
                            break;
                        }
                    }
                }
            }
        }
        if(dangqianjingling.contains("幻影蝶")){
            if(dm.FindPic(149, 473, 305, 560, "技能-自爆.bmp|jn-jxcd1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("帝皇之御")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        god_changesp("切精灵-埃尔尼亚.bmp");
        god_changesp("切精灵-六界.bmp");
        god_changesp("切精灵-六界1.bmp");
        god_changesp("切精灵-张飞.bmp");
        god_changesp("六界-切龙妈.bmp|六界-切龙妈1.bmp");
        god_changesp("切精灵-王哈.bmp");
        if(dangqianjingling.contains("埃尔尼亚")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("六界神王")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("六界帝神")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("万人敌")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("乔特鲁德") || dangqianjingling.contains("乔德")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("王之哈莫")){
            if(dm.FindColor(18, 476, 89, 493, "fffad4-000000", 1, 0, x, y)!=0){
                dm.MoveTo(40,506);
                dm.LeftClick();
            }
        }
    }else if(method==4){
        if(dangqianshoufa!="幻影蝶" && dangqianshoufa!="帝皇之御"){
            if(dm.FindPic(25, 497, 208, 572, "六界-bb.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(jianchashoufa("幻影蝶")==false && jianchashoufa("帝皇之御")==false){
                qDebug()<<"进入循环";
                while(jianchashoufa("幻影蝶")==false && jianchashoufa("帝皇之御")==false){
                    if(dm.FindStr(192, 377, 791, 476, "幻影蝶|帝皇之御","ffffff-111111",0.9,x,y)!=-1){
                        dm.MoveTo(x.toInt()+5,y.toInt()+20);
                        dm.LeftClick();
                        dm.LeftClick();
                        dm.LeftClick();
                        if(dm.FindPic(0,0,1000,600, "fw-sf.bmp","000000",0.9,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                        }
                        if(jianchashoufa("幻影蝶")){
                            dangqianshoufa="幻影蝶";
                            break;
                        }else if(jianchashoufa("帝皇之御")){
                            dangqianshoufa="帝皇之御";
                            break;
                        }
                    }
                }
            }
        }
        if(dangqianjingling.contains("幻影蝶")){
            if(dm.FindPic(149, 473, 305, 560, "技能-自爆.bmp|jn-jxcd1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("帝皇之御")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        god_changesp("切精灵-埃尔尼亚.bmp");
        god_changesp("切精灵-六界.bmp");
        god_changesp("切精灵-六界1.bmp");
        god_changesp("切精灵-张飞.bmp");
        god_changesp("六界-切龙妈.bmp|六界-切龙妈1.bmp");
        god_changesp("切精灵-王哈.bmp");
        if(dangqianjingling.contains("埃尔尼亚")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("六界神王")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("六界帝神")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("万人敌")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("乔特鲁德") || dangqianjingling.contains("乔德")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("王之哈莫")){
            if(dm.FindPic(0, 0, 1000, 600, "王哈-先手.bmp", "000000", 0.8, 0, x, y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
        }
    }else if(method==5){
        if(dangqianshoufa!="王之哈莫"){
            if(dm.FindPic(25, 497, 208, 572, "六界-bb.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(jianchashoufa("王之哈莫")==false){
                shezhishoufa("王之哈莫");
            }
        }
        if(dangqianjingling.contains("幻影蝶") && explode_death==true){
            if(dm.FindPic(149, 473, 305, 560, "技能-自爆.bmp|jn-jxcd1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("帝皇之御") && explode_death==true){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("王之哈莫")){
            if(dm.FindPic(149, 473, 1000, 600, "王哈-强化.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(dm.FindPic(149, 473, 1000, 600, "王哈-强化次数0.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(819,533);
                dm.LeftClick();
                Delay(1000);
                if(dm.FindPic(7, 340, 968, 569, "切精灵-幻影蝶.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    for(int i=0;i<30;i++){
                        if(dm.FindPic(0,0, 1000, 600, "出战按钮.bmp","000000",0.8,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                            explode_death=true;
                            break;
                        }
                    }
                }
                if(dm.FindPic(7, 340, 968, 569, "切精灵-表姐.bmp","000000",0.8,0,x,y)!=-1){
                    dm.MoveTo(x.toInt(),y.toInt());
                    dm.LeftClick();
                    for(int i=0;i<30;i++){
                        if(dm.FindPic(0,0, 1000, 600, "出战按钮.bmp","000000",0.8,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                            explode_death=true;
                            break;
                        }
                    }
                }
            }
        }
        if(explode_death==true){
            god_changesp("切精灵-埃尔尼亚.bmp");
            god_changesp("切精灵-六界.bmp");
            god_changesp("切精灵-六界1.bmp");
            god_changesp("切精灵-张飞.bmp");
            god_changesp("六界-切龙妈.bmp|六界-切龙妈1.bmp");
            god_changesp("切精灵-幻境.bmp");
            if(dangqianjingling.contains("埃尔尼亚")){
                if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                    dm.MoveTo(245,516);
                    dm.LeftClick();
                }
            }
            if(dangqianjingling.contains("六界神王")){
                if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                    dm.MoveTo(245,516);
                    dm.LeftClick();
                }
            }
            if(dangqianjingling.contains("六界帝神")){
                if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                    dm.MoveTo(245,516);
                    dm.LeftClick();
                }
            }
            if(dangqianjingling.contains("万人敌")){
                if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                    dm.MoveTo(245,516);
                    dm.LeftClick();
                }
            }
            if(dangqianjingling.contains("乔特鲁德") || dangqianjingling.contains("乔德")){
                if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                    dm.MoveTo(245,516);
                    dm.LeftClick();
                }
            }
            if(dangqianjingling.contains("幻境界皇")){
                if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                    dm.MoveTo(245,516);
                    dm.LeftClick();
                }
            }
        }
    }else if(method==7){
        if(dangqianshoufa!="幻影蝶" && dangqianshoufa!="帝皇之御"){
            if(dm.FindPic(25, 497, 208, 572, "六界-bb.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(jianchashoufa("幻影蝶")==false && jianchashoufa("帝皇之御")==false){
                qDebug()<<"进入循环";
                while(jianchashoufa("幻影蝶")==false && jianchashoufa("帝皇之御")==false){
                    if(dm.FindStr(192, 377, 791, 476, "幻影蝶|帝皇之御","ffffff-111111",0.9,x,y)!=-1){
                        dm.MoveTo(x.toInt()+5,y.toInt()+20);
                        dm.LeftClick();
                        dm.LeftClick();
                        dm.LeftClick();
                        if(dm.FindPic(0,0,1000,600, "fw-sf.bmp","000000",0.9,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                        }
                        if(jianchashoufa("幻影蝶")){
                            dangqianshoufa="幻影蝶";
                            break;
                        }else if(jianchashoufa("帝皇之御")){
                            dangqianshoufa="帝皇之御";
                            break;
                        }
                    }
                }
            }
        }
        if(dangqianjingling.contains("幻影蝶")){
            if(dm.FindPic(149, 473, 305, 560, "技能-自爆.bmp|jn-jxcd1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("帝皇之御")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        god_changesp("切精灵-埃尔尼亚.bmp");
        god_changesp("切精灵-六界.bmp");
        god_changesp("切精灵-六界1.bmp");
        god_changesp("切精灵-张飞.bmp");
        god_changesp("六界-切龙妈.bmp|六界-切龙妈1.bmp");
        god_changesp("切精灵-王哈.bmp");
        if(dangqianjingling.contains("埃尔尼亚")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("六界神王")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("六界帝神")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("万人敌")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("乔特鲁德") || dangqianjingling.contains("乔德")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("王之哈莫")){
            if(jinglingjineng=="王哈-强化")
                xy_skill("王哈-强化","王哈-强化.bmp","第五");
            else if(jinglingjineng=="第五")
                xy_skill("第五","","王哈-强化");
        }

    }else if(method==8){
        if(dangqianshoufa!="幻影蝶" && dangqianshoufa!="帝皇之御"){
            if(dm.FindPic(25, 497, 208, 572, "六界-bb.bmp","000000",0.9,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
            if(jianchashoufa("幻影蝶")==false && jianchashoufa("帝皇之御")==false){
                qDebug()<<"进入循环";
                while(jianchashoufa("幻影蝶")==false && jianchashoufa("帝皇之御")==false){
                    if(dm.FindStr(192, 377, 791, 476, "幻影蝶|帝皇之御","ffffff-111111",0.9,x,y)!=-1){
                        dm.MoveTo(x.toInt()+5,y.toInt()+20);
                        dm.LeftClick();
                        dm.LeftClick();
                        dm.LeftClick();
                        if(dm.FindPic(0,0,1000,600, "fw-sf.bmp","000000",0.9,0,x,y)!=-1){
                            dm.MoveTo(x.toInt(),y.toInt());
                            dm.LeftClick();
                        }
                        if(jianchashoufa("幻影蝶")){
                            dangqianshoufa="幻影蝶";
                            break;
                        }else if(jianchashoufa("帝皇之御")){
                            dangqianshoufa="帝皇之御";
                            break;
                        }
                    }
                }
            }
        }
        if(dangqianjingling.contains("幻影蝶")){
            if(dm.FindPic(149, 473, 305, 560, "技能-自爆.bmp|jn-jxcd1.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("帝皇之御")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        god_changesp("切精灵-埃尔尼亚.bmp");
        god_changesp("切精灵-六界.bmp");
        god_changesp("切精灵-六界1.bmp");
        god_changesp("切精灵-张飞.bmp");
        god_changesp("六界-切龙妈.bmp|六界-切龙妈1.bmp");
        god_changesp("切精灵-幻境.bmp");
        if(dangqianjingling.contains("埃尔尼亚")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("六界神王")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("六界帝神")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("万人敌")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("乔特鲁德") || dangqianjingling.contains("乔德")){
            if(dm.FindColor(284, 509, 297, 518, "0388ec-000000", 1, 0, x, y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
            }
        }
        if(dangqianjingling.contains("幻境界皇")){
            if(dm.FindColor(18, 476, 89, 493, "fffad4-000000", 1, 0, x, y)!=0){
                dm.MoveTo(40,506);
                dm.LeftClick();
            }
        }
    }
}












