#pragma once

#include <QtWidgets/QWidget>
#include "CFrameLessWidgetBase.h"
#include "CTitleBar.h"
#include "VideoWidget.h"
#include "CBottomCtrlBar.h"
#include "CRightPlayListWidget.h"
#include "CVlcKits.h"
#include <memory>

using namespace std;


class MainWidget : public CFrameLessWidgetBase
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    void initUI();

private:
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void on_closeSlot();
    void onOpenFile(const QStringList& fileList);
    void onTimeSliderMoved(int value);
    void onPlay();

private:
    CTitleBar *m_pTitleBar;
    VideoWidget *m_pVideoWidget;
    CRightPlayListWidget* m_pRightPlayListWidget;
    CBottomCtrlBar *m_pBottomCtrlBar;

    std::unique_ptr<CVlcKits> m_pVlc;
    bool m_isPlay = false;
};
