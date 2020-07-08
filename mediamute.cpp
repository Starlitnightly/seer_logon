/**
 * @file mediamute.cpp
 * @brief 静音功能
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "mediamute.h"
#include "mutedsessionevents.h"

extern volatile bool g_bMuted;

static IMMDeviceEnumerator*        m_pEnumerator                = NULL;
static IMMDevice*                        m_pDeviceOut                    = NULL;
static IAudioSessionManager*        m_AudioSessionManager = NULL;
static IAudioSessionControl*        m_AudioSessionControl    = NULL;
static CMutedSessionEvents *        m_pMutedSessionEvents    = NULL;
/**
 * @brief 媒体静音类构造函数
 * @return 无
 */
MediaMute::MediaMute()
{
    CoInitializeEx( NULL , COINIT_MULTITHREADED );

        HRESULT hr;

        //实例化 MMDeviceEnumerator 枚举器
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL,CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),(void**)&m_pEnumerator);


        // 默认设备的IMMDevice接口
        hr = m_pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &m_pDeviceOut);


        // 得到音频会话接口IAudioSessionManager
        hr = m_pDeviceOut->Activate(__uuidof(m_AudioSessionManager), CLSCTX_ALL, NULL, (void**)&m_AudioSessionManager);


        // 设置会话(Session)参数
        hr = m_AudioSessionManager->GetAudioSessionControl(NULL,0,&m_AudioSessionControl);


        // 设置声音改变参数通知
        m_pMutedSessionEvents = new CMutedSessionEvents(m_AudioSessionManager);
        hr = m_AudioSessionControl->RegisterAudioSessionNotification(m_pMutedSessionEvents);


}
/**
 * @brief 解除静音
 * @return 只有true，因为指针释放失败会直接进程结束
 */
bool MediaMute::UnMute()
{
    // ---- 解注册声音改变参数通知
        if (m_AudioSessionControl!=NULL&&m_pMutedSessionEvents!=NULL)
        {
            m_AudioSessionControl->UnregisterAudioSessionNotification(m_pMutedSessionEvents);
        }

        // ---- 释放内存空间
        if (m_AudioSessionControl != NULL)
        {
            m_AudioSessionControl->Release();
            m_AudioSessionControl = NULL;
        }
        if (m_pMutedSessionEvents != NULL)
        {
            m_pMutedSessionEvents->Release();
            m_pMutedSessionEvents = NULL;
        }
        if (m_pDeviceOut != NULL)
        {
            m_pDeviceOut->Release();
            m_pDeviceOut = NULL;
        }
        if(m_AudioSessionManager != NULL)
        {
            m_AudioSessionManager->Release();
            m_AudioSessionManager = NULL;
        }
        if (m_pEnumerator != NULL)
        {
            m_pEnumerator->Release();
            m_pEnumerator = NULL;
        }

        CoUninitialize();

        return true;
}
/**
 * @brief 设置静音状态
 * @param mute true为静音/false为解除静音
 * @return 设置是否成功
 *   @retval true 设置成功
 *   @retval false 设置失败
 */
bool MediaMute::SetMute(bool mute)
{
    HRESULT hr = S_FALSE;

        // 获得音量、静音控制接口
        ISimpleAudioVolume   *pAudioVolume = NULL;
        hr = m_AudioSessionManager->GetSimpleAudioVolume(NULL,0,&pAudioVolume);
        if (FAILED(hr)) return false;

        if(SUCCEEDED(hr))
        {
            pAudioVolume->SetMute(mute, &GUID_NULL);

            // 更改全局静音状态
            g_bMuted = mute;
        }

        if (pAudioVolume != NULL)
        {
            pAudioVolume->Release();
            pAudioVolume = NULL;
        }
        return true;
}
