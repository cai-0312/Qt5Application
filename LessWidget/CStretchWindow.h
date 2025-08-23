#pragma once
#include "QWidget"

class CStretchWindow :
    public QWidget
{
    Q_OBJECT
public:
    CStretchWindow(QWidget* p = nullptr);
    ~CStretchWindow() {}

protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

private:

    int m_nBorderWidth = 5;


};

