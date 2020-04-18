#pragma once

#include <QWidget>
#include "ui_QQSetWnd.h"

class QQSetWnd : public QWidget
{
	Q_OBJECT

public:
	QQSetWnd(QWidget *parent = Q_NULLPTR);
	~QQSetWnd();

public slots:
	void on_btn_regist_clicked();
	void on_btn_cancel_clicked();
private:
	Ui::QQSetWnd ui;
};
