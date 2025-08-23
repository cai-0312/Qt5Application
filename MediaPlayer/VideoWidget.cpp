#include "VideoWidget.h"

VideoWidget::VideoWidget(QWidget* parent)
	:QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground);
	this->setMinimumSize(800, 600);
	
}

VideoWidget::~VideoWidget()
{
}
