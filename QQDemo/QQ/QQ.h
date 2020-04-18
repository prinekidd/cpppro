#pragma once

#include <QtWidgets/QWidget>
#include "ui_QQ.h"
#include <QMouseEvent>
class QQ : public QWidget
{
	Q_OBJECT

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
public:
	QQ(QWidget *parent = Q_NULLPTR);

public slots:
	void on_btn_close_clicked();
	void on_btn_min_clicked();
	void SetCtrlColor(QString color);
	void OnLineHover(QWidget* sender);
	void OnLineLeave(QWidget* sender);
	void OnAccBoxClick();
	void itemClicked(QListWidgetItem* item);

	void on_btn_login_clicked();
	void on_btn_set_clicked();
	void on_btn_regist_clicked();
	void ReadData();
	void TimerTimeOut();
private:
	Ui::QQClass ui;
	QTimer* m_timer;
	QString m_curUserId;
	void Init();
};
