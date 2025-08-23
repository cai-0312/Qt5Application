#pragma once
#include <stdint.h>
#ifdef _WIN32                        // Windows 平台下的兼容性定义
#include <basetsd.h>
typedef SSIZE_T ssize_t;             // 在 Windows 下定义 ssize_t 类型
#endif 

#include "vlc/vlc.h"                 // 引入 libVLC 的头文件（VLC 播放库）
#include <QObject>
#include <vector>

using namespace std;

class CVlcKits : public QObject 
{
	Q_OBJECT
public:
	CVlcKits();
	~CVlcKits();
	int initVLC();

	void setTimeSliderPos(int value);
	void setSoundSliderPos(int value);
	void setTimeText(const QString& str);

	libvlc_media_player_t* media_player();
	libvlc_time_t getDurations();
	void setCurrentDuration(libvlc_time_t value);

	int play(QStringList fileList, void* hwnd);
	void play();
	void pause();
	void stop();

	vector<libvlc_time_t> getVecDurations();
	int getCurrentIdex();
	void addCurrentIdex();

signals:
	void sig_TimeSliderPos(const int& value);
	void sig_SoundSliderPos(const int& value);
	void sig_TimeText(const QString& str);
private:
	libvlc_instance_t* m_pInstance = nullptr;        // VLC 实例指针
	libvlc_media_player_t* m_pMediaPlayer = nullptr; // VLC 媒体播放器指针
	libvlc_media_t* m_pMedia = nullptr;              // VLC 媒体对象指针

	libvlc_media_list_player_t* m_pMediaPlayerList; 
	libvlc_media_list_t* m_pMediaList;              

	libvlc_event_manager_t* m_pEvent_manager = nullptr;

	libvlc_time_t m_CurrentDurtions = 0;
	vector<libvlc_time_t> m_vecDurations;

	int m_CurrentIdex = 0;
};

