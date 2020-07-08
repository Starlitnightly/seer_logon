/**
 * @file atoken.h
 * @brief 免责协议窗口头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef ATOKEN_H
#define ATOKEN_H

#include <QWidget>
#include "nono.h"
#include <QString>

namespace Ui {
class Atoken;
}

/**
 * @brief 免责协议窗口类
 * 免责协议窗口这个类相关的函数
 */
class Atoken : public QWidget
{
    Q_OBJECT

public:

    explicit Atoken(QWidget *parent = 0);
    ~Atoken();

    QTime *time;
    QTimer *timer;
    void closeEvent(QCloseEvent *event);
    QString uu;
public slots:
    void slot_timer_timeout();
    void slot_agree();

private:
    Ui::Atoken *ui;
};

#endif // ATOKEN_H
