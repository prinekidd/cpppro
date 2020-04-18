#include "MainWnd.h"
#include "TCPModel.h"
#include "CChatWnd.h"
MainWnd::MainWnd(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);

	ui.listWidget_2->setStyleSheet("QListWidget{color:rgb(173,175,178); background:rgb(25,27,31);border:0px solid gray;}"
		"QListWidget::Item{height:40px;border:1px solid gray;padding-left:15;}"
		"QListWidget::Item:hover{color:rgb(255,255,255);background:transparent;border:0px solid gray;}"
		"QListWidget::Item:selected{color:rgb(255,255,255);border:0px solid gray;}"
		"QListWidget::Item:selected:active{background:#00FFFFFF;color:#FFFFFF;border-width:0;}");

	QListWidgetItem* add_item_1 = new QListWidgetItem(ui.listWidget_2);
	add_item_1->setText("YUNDA");
	connect(ui.listWidget_2, &QListWidget::itemDoubleClicked, this, &MainWnd::on_listWidget_2_itemDoubleClicked);
}

MainWnd::~MainWnd()
{
}

void MainWnd::on_btn_close_clicked()
{
	NetWork->LongOut();
}

void MainWnd::on_listWidget_2_itemDoubleClicked(QListWidgetItem* item)
{
	CChatWnd* dlg = new CChatWnd;
	dlg->setWindowTitle(QString(QString::fromLocal8Bit("与")) + item->text()+ QString(QString::fromLocal8Bit("的会话窗口")));
	dlg->show();
} 