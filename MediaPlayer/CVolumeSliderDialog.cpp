#include "CVolumeSliderDialog.h"
#include <QVBoxLayout>
#include <QEvent>
#include <windows.h>

CVolumeSliderDialog::CVolumeSliderDialog(QWidget* parent)
	: QDialog(parent)
{
	this->setFixedSize(40, 200);
	QVBoxLayout* pVLay = new QVBoxLayout(this);
	m_pSlider = new QSlider(this);
	m_pSlider->setOrientation(Qt::Vertical);
	pVLay->addWidget(m_pSlider);

	setFixedSize(40, 120);
	setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);   
	setStyleSheet("QDialog{background-color: rgba(54, 54, 54, 0.5);}");  

	connect(m_pSlider, &QSlider::valueChanged, [=](int value) {
		emit sig_SliderValueChanged(value);
		});
}

CVolumeSliderDialog::~CVolumeSliderDialog()
{
}

bool CVolumeSliderDialog::event(QEvent* event)
{
	static bool class_amended = false;

	if (event->type() == QEvent::WinIdChange)
	{
		HWND hwnd = (HWND)winId();

		if (class_amended == false)
		{
			class_amended = true;
			DWORD class_style = ::GetClassLong(hwnd, GCL_STYLE);
			class_style &= ~CS_DROPSHADOW;
			::SetClassLong(hwnd, GCL_STYLE, class_style); 
		}
	}

	return QWidget::event(event);
}
