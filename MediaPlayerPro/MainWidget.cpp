#include "MainWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <Windows.h>
#include <QDebug>

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
    HWND vlcHwnd = FindWindowEx(NULL, NULL, NULL, L"vlcmain");

    if (vlcHwnd)
    {
        EnumChildWindows(vlcHwnd, EnumVLC, NULL);
    }
}

MainWidget::MainWidget(QWidget *parent)
    : CFrameLessWidgetBase(parent)
{
    this->setWindowTitle("vlcmain");
    setMouseTracking(true);

    m_pVlc.reset(new CVlcKits());

    int nRet = m_pVlc->initVLC();

    switch (nRet)
    {
    case -1:
        QMessageBox::information(this, u8"��ʾ", u8"libvlc_new failed");
        exit(EXIT_FAILURE);

    case -2:
        QMessageBox::information(this, u8"��ʾ", u8"libvlc_media_player_new failed");
        exit(EXIT_FAILURE);
    }

    initUI();
}

MainWidget::~MainWidget()
{}

void MainWidget::initUI()
{
    setStyleSheet("background-color:rgb(251,252,253)");

    m_pTitleBar = new CTitleBar(this);
    m_pVideoWidget = new VideoWidget(this);
    m_pRightPlayListWidget = new CRightPlayListWidget(this);
    m_pRightPlayListWidget->hide();

    m_pBottomCtrlBar = new CBottomCtrlBar(this);
    
    QVBoxLayout* pMainVlay = new QVBoxLayout(this);
    pMainVlay->addWidget(m_pTitleBar);
    pMainVlay->setSpacing(0);
    QHBoxLayout* pHlay = new QHBoxLayout;
    pHlay->addWidget(m_pVideoWidget);
    pHlay->addWidget(m_pRightPlayListWidget);
    pHlay->setContentsMargins(0, 0, 0, 0);

    pMainVlay->addLayout(pHlay);
    pMainVlay->addWidget(m_pBottomCtrlBar);
    pMainVlay->setContentsMargins(0, 0, 0, 0);

    connect(m_pTitleBar, &CTitleBar::sig_close, this, &MainWidget::on_closeSlot);
    connect(m_pVideoWidget, &VideoWidget::sig_OpenFile, this, &MainWidget::onOpenFile);
    connect(m_pVideoWidget, &VideoWidget::sig_SliderMoved, this, &MainWidget::onTimeSliderMoved);
    connect(m_pBottomCtrlBar, &CBottomCtrlBar::sig_play, this, &MainWidget::onPlay);
}

void MainWidget::onOpenFile(const QStringList& fileList)
{
    if (fileList.isEmpty())
        return;

    if (0 != m_pVlc->play(fileList, (void*)(m_pVideoWidget->winId())))
    {
        QMessageBox::information(this, u8"提示", u8"����ʧ��");
        return;
    }

    SetTimer(NULL, 1, 300, TimeProc);
    m_pVideoWidget->setPlayStatus(true);
    m_isPlay = true;
}

void MainWidget::onTimeSliderMoved(int value)
{
    m_pVlc->setVideoPostion(value);
}

void MainWidget::onPlay()
{
    m_pVlc->play();
}

void MainWidget::on_closeSlot()
{
    QMessageBox::StandardButton _exit = QMessageBox::warning(this, u8"提示ʾ", u8"确认是否退出",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if (_exit == QMessageBox::Yes)
    {
        close();
    }
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

void MainWidget::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << "mouseMoveEvent";

    
    QPoint p1 = m_pVideoWidget->mapToGlobal(QPoint(0, 0));
    QRect rect = m_pVideoWidget->rect();

    
    QRect rect2(p1.x(), p1.y(), rect.width(), rect.height());

    
    QPoint p2 = QCursor::pos();

    if (m_isPlay)
    {
        if (rect2.contains(p2))
        {
            qDebug() << "in";
            m_pVideoWidget->showTopWidget(true);
        }
        else
        {
            qDebug() << "out";
            m_pVideoWidget->showTopWidget(false);
        }
    }
}