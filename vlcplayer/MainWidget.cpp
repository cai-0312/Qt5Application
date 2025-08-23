#include "MainWidget.h"
#include <QMessageBox>
#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    // vlc��ʼ��
    m_pInstance = libvlc_new(0, nullptr);

    if (m_pInstance)
    {
        m_pMediaPlayer = libvlc_media_player_new(m_pInstance);
        if (!m_pMediaPlayer)
        {
            libvlc_release(m_pInstance);
            QMessageBox::information(this, u8"��ʾ", u8"libvlc_media_player_new failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        QMessageBox::information(this, u8"��ʾ", u8"libvlc_new failed");
        exit(EXIT_FAILURE);
    }
}

MainWidget::~MainWidget()
{
    if (m_pInstance)
    {
        libvlc_release(m_pInstance);
        m_pInstance = nullptr;
    }
}

void MainWidget::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, u8"��ѡ����Ƶ�ļ�",
        "D:/testvideo",
        u8"��Ƶ�ļ�(*.mp4 *.flv);;�����ļ�(*.*);;");

    if (fileName.isEmpty())
        return;

    fileName = QDir::toNativeSeparators(fileName);  // ��һ�����Ҫ������m_pMedia�Ƿ񴴽��ɹ�

    //����·��
    m_pMedia = libvlc_media_new_path(m_pInstance, fileName.toStdString().c_str());

    if (m_pMedia)
    {
        //����media
        libvlc_media_parse(m_pMedia);

        //����media
        libvlc_media_player_set_media(m_pMediaPlayer, m_pMedia);

        //���ò��ŵĴ��ھ��
        libvlc_media_player_set_hwnd(m_pMediaPlayer, (void*)(ui.video_widget->winId()));

        //�ͷ�media
        libvlc_media_release(m_pMedia);
        m_pMedia = nullptr;

        //������Ƶ   
        libvlc_media_player_play(m_pMediaPlayer);
    }
    else
    {
        QMessageBox::information(this, u8"��ʾ", u8"libvlc_media_new_path failed");
        exit(EXIT_FAILURE);
    }
}

void MainWidget::on_btnPlay_clicked()
{
    
}

void MainWidget::on_btnPause_clicked()
{
    
}

void MainWidget::on_btnStop_clicked()
{
}
