/**
 * @file mainwindow.h
 * @brief 游戏主窗口头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <QDesktopWidget>
#include <QScreen>
#include <QtXml>

#include "mediamute.h"
#include "form.h"
#include "dm.h"
#include "ext.h"
#include "speed.h"
#include "nono.h"
#include "changesp.h"
#include "pettip.h"
#include "cdkform.h"
#include "atoken.h"



namespace Ui {
class MainWindow;
}

/**
 * @brief 游戏主窗口类
 * 加载项较多可能会卡一秒
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MediaMute Cmute;
    ~MainWindow();
    void Binddm();
    bool bind_status;
    QNetworkAccessManager *nam;
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    Atoken *ato;
    Form f;
    Speed s;
    Nono *n;
    Changesp *csp;
    CdkForm *cd;





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

    void slot_sb();
    void seer_cal();

    void slot_shiyongshuoming();
    void slot_xiangmuyuanma();
    void slot_mianzexieyi();
    void slot_author();

    void slot_new(QNetworkReply* reply);
signals:
    void sendcap(bool msg);
    void sendtip(QString msg);
    void signal_openskill();



};

void Openbag();
void Searchbag(HWND pid,QString name);
void Wearbag();
#endif // MAINWINDOW_H
