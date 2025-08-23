#pragma once

#include <QWidget>
#include <QPushButton>

#include <QSlider>
#include <QAbstractNativeEventFilter>
#include "CVideoWidgetTopWidget.h"
#include <QAbstractNativeEventFilter>

class VideoWidget : public QWidget, public QAbstractNativeEventFilter
{
	Q_OBJECT

public:
	VideoWidget(QWidget* p = NULL);
	~VideoWidget();

	void showTopWidget(bool show);
	void setPlayStatus(bool play);

protected:
	bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override;
	void resizeEvent(QResizeEvent* event) override;
	/*void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;*/

private slots:
	void onSliderMoved(int value);

signals:
	void sig_OpenFile(const QStringList& fileList);
	void sig_OpenFloder(QString path);
	void sig_OpenPlaylist();
	void sig_Totalms(const qint64& duration);   
	void sig_VideoPositionChanged(const qint64& pos);   
	void sig_SliderMoved(int value);

private:
	QPoint m_dPos;   
	CVideoWidgetTopWidget* m_pTopWidget = nullptr;
	bool m_isPlay = false;
};

