#pragma once

#include <QWidget>
#include "ui_RegistWnd.h"

class RegistWnd : public QWidget
{
	Q_OBJECT

public:
	RegistWnd(QWidget *parent = Q_NULLPTR);
	~RegistWnd();

private:
	Ui::RegistWnd ui;
};
