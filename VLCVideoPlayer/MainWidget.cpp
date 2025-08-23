#include "MainWidget.h"          // 包含 MainWidget 类的头文件
#include <QMessageBox>           // 提示框控件
#include <QFileDialog>           // 文件选择对话框
#include "ui_MainWidget.h"       // Qt Designer 生成的 UI 类
#include <QKeyEvent>
#define NOMINMAX
#include <Windows.h>

BOOL CALLBACK EnumVLC(HWND hwnd, LPARAM lParam)
{
    TCHAR szTitle[1024];
    int nLen = GetWindowText(hwnd, szTitle, 1024);
    if (nLen > 0)
    {
        EnableWindow(hwnd, FALSE);
        KillTimer(NULL, 1);
    }

    return TRUE;
}

void CALLBACK TimeProc(HWND hwnd, UINT msg, UINT_PTR id, DWORD time)
{
    HWND vlcHwnd = FindWindowEx(NULL, NULL, NULL, L"视频播放器");

    if (vlcHwnd)
    {
        EnumChildWindows(vlcHwnd, EnumVLC, NULL);
    }
}

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)            
{
    ui.setupUi(this);            
    this->setWindowTitle(u8"视频播放器");
    m_pVlc.reset(new CVlcKits());

    int nRet = m_pVlc->initVLC();

    switch (nRet)
    {
    case -1:
        //libvlc_new failed
        QMessageBox::information(this, u8"提示", u8"libvlc_new failed");
        exit(EXIT_FAILURE);
    case -2:
        //libvlc_media_player_new failed
        QMessageBox::information(this, u8"提示", u8"libvlc_media_player_new failed");
        exit(EXIT_FAILURE);
    }

    ui.label_time->setText("");  // 初始化时间标签为空

    connect(ui.timesSlider, &QSlider::sliderMoved, this, &MainWidget::onTimeSliderMoved);
    connect(ui.soundSlider, &QSlider::sliderMoved, this, &MainWidget::onSoundSliderMoved);
    connect(m_pVlc.get(), &CVlcKits::sig_TimeText, [=](const QString& value) {
        ui.label_time->setText(value);
        });
    connect(m_pVlc.get(), &CVlcKits::sig_TimeSliderPos, [=](const int& value) {
        ui.timesSlider->setValue(value);
        });
    connect(m_pVlc.get(), &CVlcKits::sig_SoundSliderPos, [=](const int& value) {
        ui.soundSlider->setValue(value);
        });

}

MainWidget::~MainWidget()
{
}

void MainWidget::on_btnOpen_clicked()
{
    // 打开文件对话框，默认路径 D:/video，过滤 mp4 和 flv 文件
    QStringList fileList = QFileDialog::getOpenFileNames(this, u8"请选择视频文件",
        "D:/video",
        u8"视频文件(*.mp4 *.flv);;所有文件(*.*);;");

    if (fileList.isEmpty())      // 如果未选择文件直接返回
        return;

    if (0 != m_pVlc->play(fileList, (void*)(ui.widget->winId())))
    {
        QMessageBox::information(this, u8"提示", u8"播放失败");
        return;
    }

    SetTimer(NULL, 1, 300, TimeProc);
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (this->isFullScreen())
    {
        this->showNormal();
    }
    else
    {
        this->showFullScreen();
    }
}

void MainWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        if (this->isFullScreen())
        {
            this->showNormal();
        }
    }
}

void MainWidget::on_btnPlayer_clicked()
{
    m_pVlc->play();
}

void MainWidget::on_btnPause_clicked()
{
    m_pVlc->pause();
}

void MainWidget::on_btnStop_clicked()
{
    m_pVlc->stop();
}

void MainWidget::onTimeSliderMoved(int value)
{
    libvlc_media_player_set_position(m_pVlc->media_player(), value / 100.0);
}

void MainWidget::onSoundSliderMoved(int value )
{
    libvlc_audio_set_volume(m_pVlc->media_player(), value);
}
