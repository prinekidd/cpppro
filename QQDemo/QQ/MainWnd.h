#pragma once

#include <QWidget>
#include "ui_MainWnd.h"

class MainWnd : public QWidget
{
	Q_OBJECT

public:
	MainWnd(QWidget *parent = Q_NULLPTR);
	~MainWnd();
public slots:
	void on_btn_close_clicked();
	void MainWnd::on_listWidget_2_itemDoubleClicked(QListWidgetItem* item);
private:
	Ui::MainWnd ui;
};
