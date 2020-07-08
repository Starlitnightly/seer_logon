/**
 * @file speed.h
 * @brief 变速窗口头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef SPEED_H
#define SPEED_H

#include <QWidget>
#include <QLibrary>
#include <QDebug>
#include <qmath.h>

namespace Ui {
class Speed;
}

class Speed : public QWidget
{
    Q_OBJECT

public:
    explicit Speed(QWidget *parent = 0);
    ~Speed();

    float game_speed;

private:
    Ui::Speed *ui;

public slots:
    void Changespeed();
    void sliderspeed();
};

#endif // SPEED_H
