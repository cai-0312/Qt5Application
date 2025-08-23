#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"

#ifdef _WIN32
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif

#include "vlc/vlc.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_btnOpen_clicked();
    void on_btnPlay_clicked();
    void on_btnPause_clicked();
    void on_btnStop_clicked();

private:
    Ui::MainWidgetClass ui;

    libvlc_instance_t* m_pInstance = nullptr;
    libvlc_media_player_t* m_pMediaPlayer = nullptr;
    libvlc_media_t* m_pMedia = nullptr;
};
