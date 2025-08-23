#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>

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

	QPushButton* m_pLogoBtn;
	QPushButton* m_pMinimodeBtn;
	QPushButton* m_pSetbtn;
	QPushButton* m_pMinbtn;
	QPushButton* m_pMaxbtn;
	QPushButton* m_pClosebtn;

};

