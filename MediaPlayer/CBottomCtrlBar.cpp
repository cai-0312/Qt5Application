#include "CBottomCtrlBar.h"
CBottomCtrlBar::CBottomCtrlBar(QWidget* parent)
	:QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground);
	this->setFixedHeight(80);

	setStyleSheet("background-color:rgb(67,67,67)");
}

CBottomCtrlBar::~CBottomCtrlBar()
{
}