#include "MainWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <Windows.h>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : CStretchWindow(parent)
{
    setAttribute(Qt::WA_StyledBackground);
    
    InitUI();

    
}

MainWidget::~MainWidget()
{}

void MainWidget::InitUI()
{
    setStyleSheet("background-color:rgb(251,252,253)");

    m_pBarTItle = new CBarTitle(this);
    m_pVideoWidget = new VideoWidget(this);
    m_pRightListWidget = new CRightListWidget(this);
    m_pRightListWidget->hide();

    m_pBottomCtrlBar = new CBottomCtrlBar(this);
   

    QVBoxLayout* pMainVlay = new QVBoxLayout(this);
    pMainVlay->addWidget(m_pBarTItle);
    pMainVlay->setSpacing(0);

    QHBoxLayout* pHlay = new QHBoxLayout(this);
    pHlay->addWidget(m_pVideoWidget);
    pHlay->addWidget(m_pRightListWidget);
    pHlay->setContentsMargins(0, 0, 0, 0);


    pMainVlay->addLayout(pHlay);
    pMainVlay->addWidget(m_pBottomCtrlBar);
    pMainVlay->setContentsMargins(0, 0, 0, 0);

    connect(m_pBarTItle, &CBarTitle::sig_close, this, &MainWidget::on_closeSlot);
}

void MainWidget::on_closeSlot()
{
    QMessageBox::StandardButton _exit = QMessageBox::warning(this, u8"提示", u8"确定要退出吗",
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    if (_exit == QMessageBox::Yes)
    {
        close();
    }

}