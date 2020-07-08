/**
 * @file mediamute.h
 * @brief 静音功能头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef MEDIAMUTE_H
#define MEDIAMUTE_H

#include "Mmdeviceapi.h"
#include "Audiopolicy.h"

/**
 * @brief 媒体静音类
 * 用于媒体静音
 */
class MediaMute
{
public:
    MediaMute();
    bool SetMute(bool mute);//设置静音
    bool UnMute();//释放

};

#endif // MEDIAMUTE_H
