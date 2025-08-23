#include "LessWidget.h"
#include <QMouseEvent>
#include <QVBoxLayout>
#include <qt_windows.h>
#include <windows.h>
#include <windowsx.h>
#include "CStretchWindow.h"
#include <QMessageBox>
#include "CBarTitle.h"

LessWidget::LessWidget(QWidget *parent)
    : CStretchWindow(parent)
{
    InitUI();
}

LessWidget::~LessWidget()
{}

void LessWidget::InitUI()
{
    m_pCBarTitle = new CBarTitle(this);

    QWidget* w = new QWidget(this);
    w->setMinimumSize(800, 600);

    QVBoxLayout* pVlay = new QVBoxLayout(this);
    pVlay->addWidget(m_pCBarTitle);
    pVlay->addWidget(w);

    pVlay->setContentsMargins(0, 0, 0, 0);

    connect(m_pCBarTitle, &CBarTitle::sig_close, this, &LessWidget::on_closeslot);
}

void LessWidget::on_closeslot()
{
    QMessageBox::information(this, "title", u8"收到关闭信号");
    close();
}
