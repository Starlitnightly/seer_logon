/**
 * @file cdkform.h
 * @brief 一键输入cdk窗口头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef CDKFORM_H
#define CDKFORM_H

#include <QWidget>

#include "nono.h"

namespace Ui {
class CdkForm;
}

/**
 * @brief 一键输入cdk窗口类
 * 一键输入cdk窗口这个类相关的函数
 */
class CdkForm : public QWidget
{
    Q_OBJECT

public:
    explicit CdkForm(QWidget *parent = 0);
    ~CdkForm();
public slots:
    void autocdk();
    void clearcdk();

private:
    Ui::CdkForm *ui;
};

#endif // CDKFORM_H
