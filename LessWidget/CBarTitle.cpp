#include "CBarTitle.h"
#include <QHBoxLayout>
#include <qt_windows.h>
#include <windows.h>
#include <windowsx.h>
#include "LessWidget.h"


CBarTitle::CBarTitle(QWidget* p)
{
	InitUI();
}

CBarTitle::~CBarTitle()
{

}

void CBarTitle::InitUI()
{
	//禁止父窗口影响子窗口样式
	setAttribute(Qt::WA_StyledBackground);

	this->setStyleSheet("background-color:rgb(54, 54, 54)");
	this->setFixedHeight(32 + 5 * 2);

	m_pLogo = new QLabel(this);  //Logo
	m_pLogo->setFixedSize(32, 32);
	m_pLogo->setStyleSheet("QLabel{background-image:url(:/LessWidget/resource/title.png);border:none}");

	m_pTitleTextLabel = new QLabel(this); //Text
	m_pTitleTextLabel->setText(u8"系统");
	m_pTitleTextLabel->setFixedWidth(120);

	m_pSetbtn = new QPushButton(this); //Set
	m_pSetbtn->setFixedSize(32, 32);
	m_pSetbtn->setStyleSheet("QPushButton{background-image:url(:/LessWidget/resource/set.png);border:none}");

	m_pMinbtn = new QPushButton(this); //Min
	m_pMinbtn->setFixedSize(32, 32);
	m_pMinbtn->setStyleSheet("QPushButton{background-image:url(:/LessWidget/resource/min.png);border:none}");

	m_pFullscreenbtn = new QPushButton(this); //Max
	m_pFullscreenbtn->setFixedSize(32, 32);
	m_pFullscreenbtn->setStyleSheet("QPushButton{background-image:url(:/LessWidget/resource/max.png);border:none}");

	m_pClosebtn = new QPushButton(this); //Close
	m_pClosebtn->setFixedSize(32, 32);
	m_pClosebtn->setStyleSheet("QPushButton{background-image:url(:/LessWidget/resource/close.png);border:none}");

	QHBoxLayout* pHlay = new QHBoxLayout(this); //Horizontal
	pHlay->addWidget(m_pLogo);
	pHlay->addWidget(m_pTitleTextLabel);
	pHlay->addStretch();
	pHlay->addWidget(m_pSetbtn);
	pHlay->addWidget(m_pMinbtn);
	pHlay->addWidget(m_pFullscreenbtn);
	pHlay->addWidget(m_pClosebtn);

	pHlay->setContentsMargins(5, 5, 5, 5);

	connect(m_pMinbtn, &QPushButton::clicked, this, &CBarTitle::on_btnClicked);
	connect(m_pFullscreenbtn, &QPushButton::clicked, this, &CBarTitle::on_btnClicked);
	connect(m_pClosebtn, &QPushButton::clicked, this, &CBarTitle::on_btnClicked);
	connect(m_pSetbtn, &QPushButton::clicked, this, &CBarTitle::on_btnClicked);

}

void CBarTitle::mousePressEvent(QMouseEvent* event)
{
	if (ReleaseCapture())
	{
		QWidget* pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
}

void CBarTitle::mouseDoubleClickEvent(QMouseEvent* event)
{
	m_pFullscreenbtn->click();
}

void CBarTitle::on_btnClicked()
{
	QPushButton* pButton = qobject_cast<QPushButton*>(sender());

	QWidget* pWindow = this->window();


	if (pButton == m_pMinbtn)
	{
		pWindow->showMinimized();
	}
	else if (pButton == m_pFullscreenbtn)
	{
		if (pWindow->isMaximized())
		{
			pWindow->showNormal();
		}
		else
		{
			pWindow->showMaximized();
		}
	}
	if (pButton == m_pClosebtn)
	{
		emit sig_close();
	}


}