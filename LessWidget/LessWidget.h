#pragma once

#include <QtWidgets/QWidget>
#include "CBarTitle.h"
#include "CStretchWindow.h"

class LessWidget : public CStretchWindow
{
    Q_OBJECT

public:
    LessWidget(QWidget *parent = nullptr);
    ~LessWidget();

private:

private:
    void InitUI();

private slots:
    void on_closeslot();
    
private:
    CBarTitle* m_pCBarTitle = nullptr;
    
};

