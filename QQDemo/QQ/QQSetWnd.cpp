#include "QQSetWnd.h"
#include <QMessageBox>
#include "TCPModel.h"

QQSetWnd::QQSetWnd(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QQSetWnd::~QQSetWnd()
{
}

void QQSetWnd::on_btn_regist_clicked()
{
	QString acc = ui.edit_acc->text();
	QString pwd1 = ui.edit_pw1->text();
	QString pwd2 = ui.edit_pw2->text();
	if (0!= QString::compare(pwd1, pwd2))
	{
		QMessageBox::warning(this, QString("ERROR"), QString("两次输入的密码不一致！"));
		return;
	}

	NetWork->RegistAcc(acc, pwd1);
}

void QQSetWnd::on_btn_cancel_clicked()
{

}
