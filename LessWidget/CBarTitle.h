#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "CStretchWindow.h"


class CBarTitle : public QWidget
{
	Q_OBJECT
public:
	CBarTitle(QWidget* p = nullptr);
	~CBarTitle();

private:
	void InitUI();

private:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;

private slots:
	void on_btnClicked();

signals:
	
	void sig_close();


private:
	QLabel* m_pLogo;
	QLabel* m_pTitleTextLabel;

	QPushButton* m_pSetbtn;
	QPushButton* m_pMinbtn;
	QPushButton* m_pFullscreenbtn;
	QPushButton* m_pClosebtn;

};

