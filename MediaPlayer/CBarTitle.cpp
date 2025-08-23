#include "CBarTitle.h"
#include <QHBoxLayout>
#include <QMenu>
#include "qss.h"
#include <QAction>

#pragma comment(lib, "user32.lib")
#include <qt_windows.h>


CBarTitle::CBarTitle(QWidget* p) :
	QWidget(p)
{
	this->setAttribute(Qt::WA_DeleteOnClose);
	setMouseTracking(true);
	InitUI();
}

CBarTitle::~CBarTitle()
{
}


void CBarTitle::InitUI()
{
	setAttribute(Qt::WA_StyledBackground);
	this->setFixedHeight(32 + 5 * 2);
	this->setStyleSheet("background-color:rgb(54,54,54)");

	m_pLogoBtn = new QPushButton(this);
	m_pLogoBtn->setFixedSize(138, 32);
	m_pLogoBtn->setText(u8"视频播放器");
	m_pLogoBtn->setStyleSheet(QString::fromStdString(logo_button_qss));

	QMenu* pMenu = new QMenu(this);
	pMenu->setStyleSheet(QString::fromStdString(menu_qss));

	QAction* pAc1 = new QAction(u8"打开文件", this);
	QAction* pAc2 = new QAction(u8"打开文件夹", this);
	QAction* pAc3 = new QAction(u8"开发说明", this);
	QAction* pAc4 = new QAction(u8"退出", this);

	pMenu->addAction(pAc1);
	pMenu->addAction(pAc2);
	pMenu->addAction(pAc3);
	pMenu->addAction(pAc4);

	m_pLogoBtn->setMenu(pMenu);

	m_pMinimodeBtn = new QPushButton(this);
	m_pMinimodeBtn->setFixedSize(32, 32);
	m_pMinimodeBtn->setStyleSheet(QString::fromStdString(minimode_qss));

	m_pSetbtn = new QPushButton(this);
	m_pSetbtn->setFixedSize(32, 32);
	m_pSetbtn->setStyleSheet(QString::fromStdString(settop_qss));

	m_pMinbtn = new QPushButton(this);
	m_pMinbtn->setFixedSize(32, 32);
	m_pMinbtn->setStyleSheet(QString::fromStdString(min_qss));

	m_pMaxbtn = new QPushButton(this);
	m_pMaxbtn->setFixedSize(32, 32);
	m_pMaxbtn->setStyleSheet(QString::fromStdString(max_qss));

	m_pClosebtn = new QPushButton(this);
	m_pClosebtn->setFixedSize(32, 32);
	m_pClosebtn->setStyleSheet(QString::fromStdString(close_qss));

	QHBoxLayout* pHlay = new QHBoxLayout(this);
	pHlay->addWidget(m_pLogoBtn);

	pHlay->addStretch();
	pHlay->addWidget(m_pMinimodeBtn);
	QSpacerItem* pItem = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem);

	pHlay->addWidget(m_pSetbtn);
	QSpacerItem* pItem1 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem1);

	pHlay->addWidget(m_pMinbtn);
	QSpacerItem* pItem2 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem2);
	pHlay->addWidget(m_pMaxbtn);

	QSpacerItem* pItem3 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pHlay->addSpacerItem(pItem3);   
	pHlay->addWidget(m_pClosebtn);

	pHlay->setContentsMargins(5, 5, 5, 5);

	connect(m_pMinbtn, &QPushButton::clicked, this, &CBarTitle::on_btnClicked);
	connect(m_pMaxbtn, &QPushButton::clicked, this, &CBarTitle::on_btnClicked);
	connect(m_pClosebtn, &QPushButton::clicked, this, &CBarTitle::on_btnClicked);
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
	emit m_pMaxbtn->clicked();
}

void CBarTitle::on_btnClicked()
{
	QPushButton* pButton = qobject_cast<QPushButton*>(sender());

	QWidget* pWindow = this->window();

	if (pButton == m_pMinbtn)
	{
		pWindow->showMinimized();
	}
	else if (pButton == m_pMaxbtn)
	{
		if (pWindow->isMaximized())
		{
			pWindow->showNormal();
			m_pMaxbtn->setStyleSheet("QPushButton{background-image:url(:/titlebar/resources/titleBar/normal.svg);border:none}" \
				"QPushButton:hover{" \
				"background-color:rgb(99, 99, 99);" \
				"background-image:url(:/titlebar/resources/titleBar/normal_hover.svg);border:none;}");
		}
		else
		{
			pWindow->showMaximized();
			m_pMaxbtn->setStyleSheet("QPushButton{background-image:url(:/titlebar/resources/titleBar/max.svg);border:none}" \
				"QPushButton:hover{" \
				"background-color:rgb(99, 99, 99);" \
				"background-image:url(:/titlebar/resources/titleBar/max_hover.svg);border:none;}");
		}
	}
	else if (pButton == m_pClosebtn)
	{
		emit sig_close();
	}
}

