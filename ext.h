/**
 * @file ext.h
 * @brief 全局变量声明头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef EXT_H
#define EXT_H

#include "dm.h"
#include "windows.h"

extern QString current_version;

extern QString new_version;
extern QString new_content;
extern QString new_error;
extern QString new_upurl;
extern QString new_time;
extern QString new_news;
extern QString new_guanggao;

extern HWND Pid;
extern HWND wPid;
extern Dm::Idmsoft dm;
extern QString dangqianshoufa;//当前首发精灵
extern QString dangqianjingling;//当前战斗精灵
extern QString jinglingjineng;//要释放的精灵技能
extern QString jfjl;//己方精灵
extern QString dmjl;//对面精灵
extern QString allpath;

extern bool fw_allactive;//飞王全部激活
extern bool fw_lqactive;//飞王灵巧激活
extern bool fw_llactive;//飞王凌厉激活
extern bool fw_cxactive;//飞王持续激活
extern bool fw_trueactive;//飞王正确激活
extern QString fw_goal;//飞王战斗目标

extern bool friend_click;//好友已按下
extern bool panel_open;//面板已开
extern int panel_wish;//许愿面板

extern int searles_lose;//圣瑞战败次数
extern int searles_fight;//圣瑞挑战次数
extern int searles_reset;//圣瑞重置次数

extern bool explode_death;//神王_自爆死


#endif // EXT_H
