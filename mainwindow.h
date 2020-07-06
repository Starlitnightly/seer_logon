#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QDesktopWidget>
#include <QScreen>

#include "mediamute.h"
#include "form.h"
#include "dm.h"
#include "ext.h"
#include "speed.h"
#include "nono.h"
#include "changesp.h"



namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MediaMute Cmute;
    ~MainWindow();
    void Binddm();
    bool bind_status;
public:


private:
    Ui::MainWindow *ui;
    Form f;
    Speed s;
    Nono *n;
    Changesp *csp;


public slots:
    //菜单
    void FreshSeer();//刷新游戏
    void Mute();//游戏静音
    void unMute();//解除静音
    void OptimizingMemory();//优化内存
    void ReleaseMemory();//内存释放
    void ClearCache();

    //工具
    void Opence();
    void Openfd();
    void OpenKeyandMouse();
    void OpenMousepoint();

    //功能
    void ChangeSpirit();
    void ChangeBag();
    void Inputcdk();
    void Gemsynthesis();

    void GreenfireTimer();
    void PeakMode();

    //脚本
    void Openscript();

    void ChangeSpeedPrepare();//变速准备
    void ChangeSpeed();//修改速度大小为speed_size
    void script_open();
    void speedopen();

    //一键换装备
    void Changebag_sk();
    void Changebag_fs();
    void Changebag_ld();
    void Changebag_hd();
    void Changebag_dy();
    void Changebag_xa();
    void Changebag_wl();
    void Changebag_ys();
    void Changebag_tz();
    void Changebag_yy();
    void Changebag_tq();
    void Changebag_yh();
    void Changebag(QString name);

    void dianfeng();
    void show_csp();
signals:
    void sendcap(bool msg);
    void sendtip(QString msg);


};

void Openbag();
void Searchbag(HWND pid,QString name);
void Wearbag();
#endif // MAINWINDOW_H
