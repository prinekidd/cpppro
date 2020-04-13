#pragma once

#include <QWidget>
#include "ui_MainWnd.h"

class MainWnd : public QWidget
{
	Q_OBJECT

public:
	MainWnd(QWidget *parent = Q_NULLPTR);
	~MainWnd();

private:
	Ui::MainWnd ui;
};
