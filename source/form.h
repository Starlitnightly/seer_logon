/**
 * @file form.h
 * @brief 脚本窗口头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QDir>

#include "ext.h"
#include "xy.h"



namespace Ui {
class Form;
class Fw;
class Gem;
class Hdblk;
class Jlw;
class Spt;
class Team;
class Tower;
class Vip;
class Wish;
class Xxlzc;

class AutoC;
class Repp;
class Top;
}
/**
 * @brief 补pp-多线程类
 * 对战中0pp时启动此线程可以自动补pp，（bug）如果网速过慢可能点不到药
 */
class Repp: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Repp(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 自动确认-多线程类
 * 用于自动按下赛尔号的确认按钮的多线程
 */
class AutoC: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    AutoC(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 飞王脚本-多线程类
 * 飞王脚本相关的函数配置
 */
class Fw: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Fw(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
    bool jianchashoufa(QString shoufajingling);
    void shezhishoufa(QString shoufajingling);
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 一键刻印/宝石抽奖脚本-多线程类
 * 脚本相关的配置
 */
class Gem: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Gem(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 混沌布莱克脚本-多线程类
 * 脚本相关的配置
 */
class Hdblk: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Hdblk(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 精灵王大乱斗脚本-多线程类
 * 脚本相关的配置
 */
class Jlw: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Repp *script_repp;
    Jlw(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
        script_repp=NULL;
    }

protected:
    void run();
signals:
    void done();
};
/**
 * @brief spt徽章相关脚本-多线程类
 * 脚本相关的配置
 */
class Spt: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Repp *script_repp;
    Spt(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
        script_repp=NULL;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 一键战队贡献脚本-多线程类
 * 脚本相关的配置
 */
class Team: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Team(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void sendMessage(QString msg);
};
/**
 * @brief 一键勇者之塔脚本-多线程类
 * 脚本相关的配置
 */
class Tower: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Tower(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 一键vip礼包脚本-多线程类
 * 脚本相关的配置
 */
class Vip: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Vip(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 一键许愿脚本-多线程类
 * 脚本相关的配置
 */
class Wish: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Wish(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 一键学习力战场脚本-多线程类
 * 脚本相关的配置
 */
class Xxlzc: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Xxlzc(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};


/**
 * @brief 判断进入巅峰-多线程类
 * 用于巅峰脚本判断要进入哪个巅峰以及当前所处的位置
 */
class Pdtop: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    QString mode;
    Pdtop(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 禁用黑屋精灵-多线程类
 * 禁用黑屋精灵以及无黑屋精灵相关的ban操作
 */
class Ban3: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    QString mode;
    Ban3(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};
/**
 * @brief 首发与出战-多线程类
 * 巅峰脚本自动选择首发与自动选择出战精灵
 */
class Explode: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    QString mode;
    Explode(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
    void auto33first();
    void auto33fight();
    void autofirst();
    void autofight();
protected:
    void run();
signals:
    void done();
};

/**
 * @brief 巅峰主脚本-多线程类
 * 脚本相关的配置
 */
class Top: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Repp *script_repp;
    Pdtop *script_pdtop;
    Ban3 *script_ban3;
    Explode *script_explode;
    QString mode;

    bool robot;

    Top(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
        script_repp=NULL;
        script_ban3=NULL;
        script_pdtop=NULL;
        script_explode=NULL;
        robot=false;
    }

    void Robotfight();
protected:
    void run();
signals:
    void done();
};

/**
 * @brief 圣瑞儿子脚本-多线程类
 * 脚本相关的配置
 */
class Searles: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    QString mode;
    Searles(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void sendreset(QString msg);
    void sendlose(QString msg);
    void sendfight(QString msg);
};

/**
 * @brief 六界神王殿脚本-多线程类
 * 脚本相关的配置
 */
class Sixworld: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    int god;
    void god_condition();
    void god_changesp(QString sp);
    void god_method(int method);
    bool jianchashoufa(QString shoufajingling);
    void shezhishoufa(QString shoufajingling);
    Sixworld(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();

};












/**
 * @brief 脚本主窗口类
 * 本类记载了所有的脚本
 */
class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();


    Fw *script_fw;
    Gem *script_gem;
    Hdblk *script_hdblk;
    Jlw *script_jlw;
    Spt *script_spt;
    Team *script_team;
    Tower *script_tower;
    Vip *script_vip;
    Wish *script_wish;
    Xxlzc *script_xxlzc;

    AutoC *script_auto;
    Top *script_top;
    Searles *script_searles;
    Sixworld *script_sixworld;


    QString mode;

private:
    Ui::Form *ui;

public slots:
    void test();
    void test2();

    //单选框槽函数1
    void fw_selected();
    void gem_selected();
    void hdblk_selected();
    void jlw_selected();
    void spt_selected();
    void team_selected();
    void tower_selected();
    void vip_selected();
    void wish_selected();
    void xxlzc_selected();
    //巅峰单选框槽函数
    void top_jj_selected();
    void top_ky_selected();
    void top_33_selected();

    void searles_selected();//选择圣瑞脚本
    void sixworld_selected();//选择六界
    void showMessageBox(QString msg);

    void showreset(QString msg);
    void showlose(QString msg);
    void showfight(QString msg);

};







#endif // FORM_H
