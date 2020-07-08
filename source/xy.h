/**
 * @file xy.h
 * @brief 星夜特色函数头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef XY_H
#define XY_H

#include <QString>
#include <QVariant>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>



#include "ext.h"


QString xy_shibiejifangjingling();//星夜_识别己方精灵
QString xy_shibieduifangjingling();//星夜_识别对面精灵
QString xy_shibiemap();//星夜_识别当前地图

void xy_skill(QString jn,QString jnbmp,QString nextjn);//星夜_释放技能
void xy_autofight();//星夜_自动克制系出战

void hdblk_scriptset();//混沌布莱克脚本配置
void OpenKingSpirit();//打开精灵王装置
void Delay(int time);
double xy_memory(DWORD pid);


#endif // XY_H
