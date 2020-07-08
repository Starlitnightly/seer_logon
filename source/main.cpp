/**
 * @file main.cpp
 * @brief 应用程序入口主文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * license GPL
 */
#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QLibrary>
#include <QDebug>
#include<qmessagebox.h>
#include<QFileInfo>
#include<Qdir>
#include<QFile>


/// 全局静音标志
bool g_bMuted;

/**
 * @brief 加载qss样式类
 * 加载皮肤样式-待用
 */
class CLoadQSS
{
public:
    static void setStyle(const QString &style)
    {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};


/**
 * @brief 主进程入口
 * 主进程
 */
int main(int argc, char *argv[])
{
    //raisePrivilege();
    QApplication a(argc, argv);

    /*
    QFile qss(":style.qss");
    if( qss.open(QFile::ReadOnly)){
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("Open failed");
    }
    */

    MainWindow w;
    w.show();

    return a.exec();
}
