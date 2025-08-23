#pragma once

#include <QtWidgets/QWidget>
#include "CStretchWindow.h"
#include "CBarTitle.h"
#include "VideoWidget.h"
#include "CBottomCtrlBar.h"
#include "CRightListWidget.h"
#include "CPlayButtonGroupWidget.h"
#include "CVolumeButton.h"
#include "CVolumeSliderDialog.h"

class MainWidget : public CStretchWindow
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    void InitUI();

private slots:
    void on_closeSlot();

private:
    CBarTitle* m_pBarTItle;
    VideoWidget* m_pVideoWidget;
    CRightListWidget* m_pRightListWidget;
    CBottomCtrlBar* m_pBottomCtrlBar;
    

};

