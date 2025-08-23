#include "CVlcKits.h"
#include <QDir>

void vlc_callback(const struct libvlc_event_t* p_event, void* p_data)
{
    CVlcKits* pThis = static_cast<CVlcKits*>(p_data);
    if (pThis)
    {
        switch (p_event->type) {
        case libvlc_MediaPlayerPositionChanged:
        {
            float pos = libvlc_media_player_get_position(pThis->media_player());
            pThis->setTimeSliderPos(pos * 100);

            qint64 curSecs = libvlc_media_player_get_time(pThis->media_player()) / 1000;
            int curH = curSecs / 3600;
            int curMinute = (curSecs - curH * 3600) / 60;
            int curSec = curSecs - curH * 3600 - curMinute * 60;

            char buf1[256] = { 0 };
            sprintf(buf1, "%02d:%02d:%02d", curH, curMinute, curSec);
            QString str1(buf1);

            qint64 totalSecs = pThis->getDurations();

            int _hour = totalSecs / 3600;
            int _minute = (totalSecs - _hour * 3600) / 60;
            int _sec = totalSecs - _hour * 3600 - _minute * 60;

            char buf2[256] = { 0 };
            sprintf(buf2, "%02d:%02d:%02d", _hour, _minute, _sec);
            QString str2(buf2);

            QString text = str1 + "/" + str2;

            pThis->setTimeText(text);
        }
        break;
        case libvlc_MediaPlayerAudioVolume:
        {
            int sound = libvlc_audio_get_volume(pThis->media_player());
            pThis->setSoundSliderPos(sound);
        }
        break;
        case libvlc_MediaPlayerMediaChanged:
        {
            pThis->addCurrentIdex();
            int _index = pThis->getCurrentIdex();
            
            int vSize = pThis->getVecDurations().size();
            if (_index > vSize)
            {
                if (_index % vSize == 0)
                {
                    _index = vSize;
                }
                else
                {
                    _index = _index % vSize;
                }
            }

            libvlc_time_t _duration = pThis->getVecDurations()[_index - 1];
            pThis->setCurrentDuration(_duration);

            
        }
        break;
        }
    }

}

int CVlcKits::initVLC()
{
    m_pInstance = libvlc_new(0, nullptr);   // 创建 VLC 实例对象

    if (m_pInstance)             // 如果实例创建成功
    {
        m_pMediaPlayer = libvlc_media_player_new(m_pInstance); // 创建媒体播放器
        if (m_pMediaPlayer)     // 如果播放器创建失败
        {
            m_pEvent_manager = libvlc_media_player_event_manager(m_pMediaPlayer);
            libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerPositionChanged, vlc_callback, this);
            libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerAudioVolume, vlc_callback, this);
            libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerMediaChanged, vlc_callback, this);
        }
        else
        {
            libvlc_release(m_pInstance);   // 释放 VLC 实例
            return -2; //libvlc_media_player_new failed
        }
    }
    else                         // 如果 VLC 实例创建失败
    {
        return -1; //libvlc_new failed
    }
    return 0;
}
CVlcKits::CVlcKits() {

}

CVlcKits::~CVlcKits()
{
    if (m_pMediaPlayer)
    {
        libvlc_media_player_release(m_pMediaPlayer);
        m_pMediaPlayer = nullptr;
    }

    if (m_pInstance)             // 析构时如果 VLC 实例存在
    {
        libvlc_release(m_pInstance); // 释放 VLC 实例
        m_pInstance = nullptr;   // 置空指针，避免悬挂引用
    }
}

void CVlcKits::setSoundSliderPos(int value)
{
    emit sig_SoundSliderPos(value);
}

void CVlcKits::setTimeText(const QString& str)
{
    emit sig_TimeText(str);
}


void CVlcKits::setTimeSliderPos(int value)
{
    emit sig_TimeSliderPos(value);
}

libvlc_media_player_t* CVlcKits::media_player()
{
    return m_pMediaPlayer;
}

libvlc_time_t CVlcKits::getDurations()
{
    return m_CurrentDurtions;
}

void CVlcKits::setCurrentDuration(libvlc_time_t value)
{
    m_CurrentDurtions = value;
}

int CVlcKits::play(QStringList fileList, void* hwnd)
{
   auto m_pMediaPlayerList = libvlc_media_list_player_new(m_pInstance);
   auto m_pMediaList = libvlc_media_list_new(m_pInstance);

    int size = fileList.size();

    for (int i = 0; i < size; i++)
    {
        QString fileName = fileList[i];
        fileName = QDir::toNativeSeparators(fileName);

        libvlc_media_t* _pMedia = libvlc_media_new_path(m_pInstance, fileName.toStdString().c_str());

        if (!_pMedia)
        {
            return -1;
        }

        libvlc_media_list_add_media(m_pMediaList, _pMedia);

        libvlc_media_parse(_pMedia);
        libvlc_time_t _duration = libvlc_media_get_duration(_pMedia);

        if (_duration < -1)
        {
            return -2;
        }
        m_vecDurations.push_back(_duration / 1000);
        libvlc_media_release(_pMedia);
    }
    //设置循环模式 
    libvlc_media_list_player_set_playback_mode(m_pMediaPlayerList, libvlc_playback_mode_loop);

    libvlc_media_list_player_set_media_list(m_pMediaPlayerList, m_pMediaList);
    libvlc_media_list_player_set_media_player(m_pMediaPlayerList, m_pMediaPlayer);
    libvlc_media_player_set_hwnd(m_pMediaPlayer, hwnd);
    libvlc_media_list_player_play(m_pMediaPlayerList);

    return 0;

}

void CVlcKits::play()
{
    // 如果当前是暂停或停止状态
    if (libvlc_media_player_get_state(m_pMediaPlayer) ==
        libvlc_state_t::libvlc_Paused || libvlc_media_player_get_state(m_pMediaPlayer) ==
        libvlc_state_t::libvlc_Stopped)
    {
        libvlc_media_player_play(m_pMediaPlayer); // 播放媒体
    }
}

void CVlcKits::pause()
{
    // 如果当前正在播放
    if (libvlc_media_player_get_state(m_pMediaPlayer) ==
        libvlc_state_t::libvlc_Playing)
    {
        libvlc_media_player_pause(m_pMediaPlayer); // 暂停播放
    }
}

void CVlcKits::stop()
{
    // 如果当前是播放或暂停状态
    if (libvlc_media_player_get_state(m_pMediaPlayer) ==
        libvlc_state_t::libvlc_Playing || libvlc_media_player_get_state(m_pMediaPlayer) ==
        libvlc_state_t::libvlc_Paused)
    {
        libvlc_media_player_stop(m_pMediaPlayer); // 停止播放
    }
}

vector<libvlc_time_t> CVlcKits::getVecDurations()
{
    return m_vecDurations;
}

int CVlcKits::getCurrentIdex()
{
    return m_CurrentIdex;
}

void CVlcKits::addCurrentIdex()
{
    m_CurrentIdex++;
}

