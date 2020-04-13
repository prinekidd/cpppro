#include "QQ.h"
#include <QLine>
#include "QLineEditEx.h"
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include <QDebug>
#include <QTimeLine>
#include "MainWnd.h"
#include "TCPModel.h"
#include "QQSetWnd.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <json/json.h>
#include <commdef.h>

QQ::QQ(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    Init();
}

void QQ::Init()
{
	this->setWindowFlags(Qt::FramelessWindowHint);
	//this->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui.lineEdit, &QLineEditEx::Hovered, this, &QQ::OnLineHover);
    connect(ui.lineEdit, &QLineEditEx::Leaved, this, &QQ::OnLineLeave);
	connect(ui.lineEdit_2, &QLineEditEx::Hovered, this, &QQ::OnLineHover);
	connect(ui.lineEdit_2, &QLineEditEx::Leaved, this, &QQ::OnLineLeave);

    connect(ui.acc_combox_btn, &QPushButton::clicked, this, &QQ::OnAccBoxClick);
    connect(ui.listWidget, &QListWidget::itemClicked, this, &QQ::itemClicked);
    
    connect(NetWork->GetQTcpSocket(), SIGNAL(readyRead()), this, SLOT(ReadData()));

    ui.listWidget->setVisible(false);
    ui.line1->setStyleSheet("Line{}");
    ui.line2->setStyleSheet("Line{}");
	QPalette palette = ui.line1->palette();
	palette.setColor(QPalette::Dark,QColor::fromRgb(216, 216, 216));
    ui.line1->setPalette(palette);
}

static QPoint last(0, 0);        //保存坐标
const int TITLE_HEIGHT = 50;    //这里也可以使用宏定义，保存标题高度，也就是鼠标点击区域的高度
void QQ::mousePressEvent(QMouseEvent* event)
{
    if (event->y() < TITLE_HEIGHT)
    {
        last = event->globalPos();
    }
}
/*
 * 鼠标移动函数
 * 这里实时修改窗口的坐标
 */
void QQ::mouseMoveEvent(QMouseEvent* event)
{
    if (event->y() < TITLE_HEIGHT)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        this->move(this->x() + dx, this->y() + dy);
    }
}
/*
 * 鼠标释放函数
 */
void QQ::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->y() < TITLE_HEIGHT)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        this->move(this->x() + dx, this->y() + dy);
    }
}
void QQ::on_btn_close_clicked()
{
    this->close();
}
void QQ::on_btn_min_clicked()
{
    this->setWindowState(Qt::WindowState::WindowMinimized);
}

void QQ::SetCtrlColor(QString color)
{
    ui.line1->setStyleSheet("QLine:hover{background-color:rgba(230, 230, 230, 150);}");
}

void QQ::OnLineHover(QWidget* sender)
{
    qDebug ()<< "OnLineHover" << endl;
    if (sender->objectName() == "lineEdit")
    {
		QPalette palette = ui.line1->palette();
		palette.setColor(QPalette::Dark, QColor::fromRgb(132, 132, 132));
		ui.line1->setPalette(palette);
   }
   else
   {
		QPalette palette = ui.line2->palette();
		palette.setColor(QPalette::Dark, QColor::fromRgb(132, 132, 132));
		ui.line2->setPalette(palette);
   }

}

void QQ::OnLineLeave(QWidget *sender)
{
    qDebug() << "OnLineLeave" << endl;
	if (sender->objectName() == "lineEdit")
	{
		QPalette palette = ui.line1->palette();
		palette.setColor(QPalette::Dark, QColor::fromRgb(216, 216, 216));
		ui.line1->setPalette(palette);
	}
	else
	{
		QPalette palette = ui.line2->palette();
		palette.setColor(QPalette::Dark, QColor::fromRgb(216, 216, 216));
		ui.line2->setPalette(palette);
	}
}

void QQ::OnAccBoxClick()
{
    if (ui.listWidget->isVisible())
    {
        ui.listWidget->setVisible(false);
    }
    else
    {
        ui.listWidget->setVisible(true);
    }
   
}

void QQ::itemClicked(QListWidgetItem* item)
{
    ui.lineEdit->setText(item->text());
    ui.listWidget->setVisible(false);

}

void QQ::on_btn_login_clicked()
{
    NetWork->LoginToSrv(ui.lineEdit->text(), ui.lineEdit_2->text());
    return;
}

void QQ::on_btn_set_clicked()
{
  
}

void QQ::on_btn_regist_clicked()
{
    QQSetWnd *wd = new QQSetWnd;
    wd->show();
}

void QQ::ReadData()
{
	QByteArray buffer = NetWork->GetQTcpSocket()->readAll();
	if (!buffer.isEmpty())
	{
		Json::CharReaderBuilder crb;
		Json::CharReader* reader(crb.newCharReader());
		Json::Value root;
		JSONCPP_STRING errs;
		int ret = -1;
		std::string msg;
		if (reader->parse(buffer, buffer.toStdString().c_str() + std::strlen(buffer), &root, &errs))
		{
			int msg_type = root["msg_type"].asInt();
			std::string ret_jsonstr;
			int ret = -1;
			std::string msg;
			 ret = root["data"]["code"].asInt();
			msg = root["data"]["msg"].asString();
				switch (msg_type)
				{
					/*用户注册结果*/
				case CLIENTCOMMAND::ClientRegistAccRs:
				{
					if (ret == QQCOMMOMOP::SUCCESS)
					{
						QMessageBox::information(this, QString(QString::fromLocal8Bit("注册结果")), QString(QString::fromLocal8Bit(msg.c_str())));
					}
					else
					{
						QMessageBox::information(this, QString(QString::fromLocal8Bit("注册结果")), QString(QString::fromLocal8Bit(msg.c_str())));
					}
				}
				break;
				/*用户登录结果*/
				case CLIENTCOMMAND::ClientLoginRs:
				{

					if (ret == QQCOMMOMOP::SUCCESS)
					{
						MainWnd* pwnd = new MainWnd;
						this->hide();
						pwnd->show();
					}
					else
					{
						QMessageBox::information(this, QString(QString::fromLocal8Bit("登录结果")), QString(QString::fromLocal8Bit(msg.c_str())));
					}
				}
				break;
				default:
					break;
				}

			return;
		}
		return;
	}
}