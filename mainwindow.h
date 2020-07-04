#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>

#include "mediamute.h"
#include "form.h"
#include "dm.h"
#include "ext.h"
#include "speed.h"



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
public:


private:
    Ui::MainWindow *ui;
    Form f;
    Speed s;

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
};
#endif // MAINWINDOW_H
