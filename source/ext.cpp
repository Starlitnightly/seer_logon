/**
 * @file ext.cpp
 * @brief 全局变量定义文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "ext.h"

/// 当前登录器版本
QString current_version="6.0.0";
/// 大漠插件相关的对象（唯一）
Dm::Idmsoft dm;
/// 游戏界面窗口句柄
HWND Pid;
/// 游戏界面窗口句柄（备用）
HWND wPid;
/// 检测更新-版本号
QString new_version;
/// 检测更新-更新内容
QString new_content;
/// 检测更新-软件自动销毁
QString new_error;
/// 检测更新-更新地址
QString new_upurl;
/// 检测更新-活动通知开启标志
QString new_time;
/// 检测更新-活动通知内容
QString new_news;
/// 检测更新-活动地址
QString new_guanggao;
/// 当前首发精灵
QString dangqianshoufa;
/// 当前对战精灵
QString dangqianjingling;
/// 当前对战精灵要释放的技能
QString jinglingjineng;
/// 己方精灵
QString jfjl;
/// 对面精灵
QString dmjl;
/// 登录器运行目录
QString allpath;
/// 飞王-全部激活标志
bool fw_allactive;
/// 飞王灵巧激活
bool fw_lqactive;
/// 飞王凌厉激活
bool fw_llactive;
/// 飞王持续激活
bool fw_cxactive;
/// 飞王正确激活
bool fw_trueactive;
/// 飞王战斗目标
QString fw_goal;
/// 好友已按下标志
bool friend_click;
/// 战队贡献面板已开标志
bool panel_open;
/// 许愿面板开启
int panel_wish;
/// 圣瑞战败次数
int searles_lose;
/// 圣瑞挑战次数
int searles_fight;
/// 圣瑞重置次数
int searles_reset;
/// 六界脚本-神王_自爆死
bool explode_death;
