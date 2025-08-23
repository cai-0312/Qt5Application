#pragma once                         

#include <QtWidgets/QWidget>         
#include "ui_MainWidget.h"
#include <memory>
#include "CVlcKits.h"

using namespace std;

class MainWidget : public QWidget
{
    Q_OBJECT                         

public:
    MainWidget(QWidget* parent = nullptr); 
    ~MainWidget();    
    /*qint64 getDurations();
    void setTimeText(QString str);*/

private slots:                      // 定义槽函数，和界面上的按钮自动绑定
    void on_btnOpen_clicked();      // “打开文件”按钮点击事件
    void on_btnPlayer_clicked();    // “播放”按钮点击事件
    void on_btnPause_clicked();     // “暂停”按钮点击事件
    void on_btnStop_clicked();      // “停止”按钮点击事件

    void onTimeSliderMoved(int value);
    void onSoundSliderMoved(int value);

private:
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::MainWidgetClass ui;         // 界面对象（通过 ui.setupUi(this) 初始化）

    std::unique_ptr<CVlcKits> m_pVlc;
};
