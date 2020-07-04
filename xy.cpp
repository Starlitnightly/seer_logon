#include "xy.h"


//星夜_识别己方精灵（战斗中）
QString xy_shibiejifangjingling(){
    return dm.Ocr(16,91,101,106,"ffffff-111111",1.0);
}

//释放技能
void xy_skill(QString jn,QString jnbmp,QString nextjn){
    QVariant x,y;
    if(jn=="第五" || jn=="第五1" || jn=="第五2"){
        if(jinglingjineng==jn){
            if(dm.FindColor(18,476,89,493,"fffad4-000000",1,0,x,y)!=0){
                dm.MoveTo(40,506);
                dm.LeftClick();
                jinglingjineng=nextjn;
                qDebug()<<"已释放";
            }
        }
    }else if(jn=="第一"){
        if(jinglingjineng==jn){
            if(dm.FindColor(284,509,297,518,"0388ec-000000",1,0,x,y)!=0){
                dm.MoveTo(245,516);
                dm.LeftClick();
                jinglingjineng=nextjn;
                qDebug()<<"已释放";
            }
        }
    }else if(jinglingjineng==jn){
        if(dm.FindPic(66,417,836,565,jnbmp,"000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
            jinglingjineng=nextjn;
            qDebug()<<"已释放";
        }
    }
}

//自动克制系出战（战斗中）
void xy_autofight(){
    QVariant x,y;
    if(dm.FindPic(0,0,1000,600,"克制图片.bmp","000000",0.8,2,x,y)!=-1){
        dm.MoveTo(x.toInt(),y.toInt()+10);
        dm.LeftClick();
        for(int i=0;i<30;i++){
            if(dm.FindPic(0,0,1000,600,"出战按钮.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                break;
            }
        }
    }else if(dm.FindPic(0,0,1000,600,"普通.bmp","000000",0.8,2,x,y)!=-1){
        dm.MoveTo(x.toInt(),y.toInt()+10);
        dm.LeftClick();
        for(int i=0;i<30;i++){
            if(dm.FindPic(0,0,1000,600,"出战按钮.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                break;
            }
        }
    }else if(dm.FindPic(0,0,1000,600,"微弱.bmp","000000",0.8,2,x,y)!=-1){
        dm.MoveTo(x.toInt(),y.toInt()+10);
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

//混布脚本出战设置
void hdblk_scriptset(){
    QVariant x,y;
    /*
    if(dm.FindPic(0,0,1000,600,"克制图片.bmp","000000",0.8,2,x,y)!=-1){
        dm.MoveTo(x.toInt(),y.toInt()+10);
        dm.LeftClick();
    }*/
    if(dm.FindPic(83, 9, 212, 100,"dqwh.bmp","000000",0.8,0,x,y)!=-1){
        if(dangqianjingling!="王之哈莫")
            jinglingjineng="狂龙击杀1";
        dangqianjingling="王之哈莫";
        if(jinglingjineng=="狂龙击杀1"){
            if(dm.FindPic(66, 417, 836, 565,"jn-kljs.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                jinglingjineng="狂龙击杀2";
            }
        }else if(jinglingjineng=="狂龙击杀2"){
            if(dm.FindPic(66, 417, 836, 565,"jn-kljs.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                jinglingjineng="第五1";
            }
        }else if(jinglingjineng=="第五1"){
            if(dm.FindColor(18, 476, 89, 493,"fffad4-000000",1,0,x,y)!=0){
                dm.MoveTo(40,506);
                dm.LeftClick();
                jinglingjineng="第五2";
            }
        }else if(jinglingjineng=="第五2"){
            if(dm.FindColor(18, 476, 89, 493,"fffad4-000000",1,0,x,y)!=0){
                dm.MoveTo(40,506);
                dm.LeftClick();
                jinglingjineng="狂龙击杀2";
            }
        }

    }else if(dm.FindPic(83, 9, 212, 100,"dqao1.bmp","000000",0.8,0,x,y)!=-1){
        if(dangqianjingling!="艾欧")
            jinglingjineng="魂魄缠绕";
        dangqianjingling="艾欧";
        if(jinglingjineng=="魂魄缠绕"){
            if(dm.FindPic(66, 417, 836, 565,"jn-hpcr.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                jinglingjineng="魂魄缠绕";
            }
        }
    }else if(dm.FindPic(83, 9, 212, 100,"dqsz.bmp","000000",0.8,0,x,y)!=-1){
        if(dangqianjingling!="混沌魔君索伦森")
            jinglingjineng="第五";
        dangqianjingling="混沌魔君索伦森";
        if(jinglingjineng=="诸雄之主"){
            if(dm.FindPic(66, 417, 836, 565,"jn-zxzz.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                jinglingjineng="诸雄之主";
            }
        }else if(jinglingjineng=="第五"){
            if(dm.FindColor(18, 476, 89, 493,"fffad4-000000",1,0,x,y)!=0){
                dm.MoveTo(40,506);
                dm.LeftClick();
                jinglingjineng="诸雄之主";
            }
        }
    }else if(dm.FindPic(83, 9, 212, 100,"dqjh.bmp","000000",0.8,0,x,y)!=-1){
        if(dangqianjingling!="幻境界皇")
            jinglingjineng="精神幻灭";
        dangqianjingling="幻境界皇";
        if(jinglingjineng=="精神幻灭"){
            if(dm.FindPic(66, 417, 836, 565,"jn-jshm.bmp","000000",0.8,0,x,y)!=-1){
                dm.MoveTo(x.toInt(),y.toInt());
                dm.LeftClick();
                jinglingjineng="精神幻灭";
            }
        }
    }else
        dangqianjingling="";
}

QString xy_shibiemap(){
    return dm.Ocr( 419, 6, 556, 96, "ffff00-111111", 1);
}

void OpenKingSpirit(){
    QVariant x,y;
    if(dm.FindPic(0,0,1000,600,"jlwzz.bmp","000000",0.8,0,x,y)!=-1){
        dm.MoveTo(x.toInt()+20,y.toInt()+10);
        dm.LeftClick();
    }
    if(dm.FindPic(0,0,1000,600,"jlwksld.bmp","000000",0.8,0,x,y)!=-1){
        dm.MoveTo(x.toInt(),y.toInt());
        dm.LeftClick();
    }
}
