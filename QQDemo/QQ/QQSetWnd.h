#pragma once

#include <QWidget>
#include "ui_QQSetWnd.h"

class QQSetWnd : public QWidget
{
	Q_OBJECT

public:
	QQSetWnd(QWidget *parent = Q_NULLPTR);
	~QQSetWnd();

private:
	Ui::QQSetWnd ui;
};
