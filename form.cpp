#include "form.h"
#include "ui_form.h"

#include <QDebug>
#include <QThread>
#include <QObject>

void Delay(int time){
    QEventLoop loop;
    QTimer::singleShot(time, &loop, SLOT(quit()));
    loop.exec();
}

Form::~Form()
{
    delete ui;
}

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

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

}






void Form::test(){
    //connect(test,, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    /*
    test1=new Tower(this);
    test1->status=true;
    test1->now=6;
    test1->start();
    //test.wait();
    */
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

    }

}

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
    }
}



/*
单选框槽函数集合
*/
void Form::fw_selected(){
    QString text;
    text=QString("脚本使用说明：首发艾欧，第一个技能有女(带上绿火)\n\n背包带上圣普");
    ui->textEdit->setPlainText(text);
    mode="fw";
}
void Form::gem_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="gem";
}
void Form::hdblk_selected(){
    QString text;
    text=QString("脚本使用说明：\n首发王哈（带先三）\n背包艾欧（带魂魄缠绕）\n索总（带先三）\n幻境（带精神幻灭）");
    ui->textEdit->setPlainText(text);
    mode="hdblk";
}
void Form::jlw_selected(){
    QString text;
    text=QString("脚本使用说明：在竞技天堂（有精灵王装置的地图）运行脚本");
    ui->textEdit->setPlainText(text);
    mode="jlw";
}
void Form::spt_selected(){
    QString text;
    text=QString("脚本使用说明：首发幻境，第一个技能精神幻灭");
    ui->textEdit->setPlainText(text);
    mode="spt";
}
void Form::team_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="team";
}
void Form::tower_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="tower";
}
void Form::vip_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="vip";
}
void Form::wish_selected(){
    QString text;
    text=QString("脚本使用说明：无");
    ui->textEdit->setPlainText(text);
    mode="wish";
}
void Form::xxlzc_selected(){
    QString text;
    text=QString("脚本使用说明：在学习力战场副本运行脚本，首发艾欧，第一个技能有女");
    ui->textEdit->setPlainText(text);
    mode="xxlzc";
}

/*
脚本实现
*/
//一键勇者之塔
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

//飞王脚本
//检查首发函数
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
//设置首发函数
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
//飞王
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
            QMessageBox::information(NULL,"this","三种效果已成功打完");
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

//一键刻印/宝石脚本
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
                QMessageBox::information(NULL,"this","宝石/刻印已抽完");
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
            QMessageBox::information(NULL,"this","混布脚本已自动停止");
    }
}
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
                        if(dm.Ocr(718,310,939,371,"996600-444444|ffffff-000000",1)=="今日还能生产0")
                            break;
                        if(dm.Ocr(825,312,907,361,"ffffff-000000",1)=="0")
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
                        || dm.Ocr(718,310,939,371,"996600-444444|ffffff-000000",1)=="今日还能生产0"
                        || dm.Ocr(825,312,907,361,"ffffff-000000",1)=="0"){
                    QMessageBox::information(NULL,"this","一键战队贡献已完成");
                    break;
                }
            }
        }
        Delay(500);

    }
}
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
                QMessageBox::information(NULL,"this","礼包领取完毕");
                break;
            }
        }
        Delay(500);

    }
}
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
void Xxlzc::run(){
    QVariant x,y;
    while(status==true){

    }
}

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


