#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>
#include <QMessageBox>

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
}
//补pp脚本
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
//自动确认
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
//飞王脚本
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
//一键刻印/宝石合成脚本
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
//混沌布莱克脚本
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
//精灵王大乱斗脚本
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
//spt徽章脚本
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
//一键战队贡献脚本
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
    void done();
};
//勇者之塔脚本
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
//一键vip礼包脚本
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
//一键许愿脚本
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
//一键学习力战场脚本
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

};





#endif // FORM_H
