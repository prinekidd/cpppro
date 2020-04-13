#include "QQ.h"
#include <QtWidgets/QApplication>
#include "QQSetWnd.h"
#include "common.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//连接服务端
	NetWork->ConnectToSrv();
	QQ w;
	w.setWindowIcon(QIcon(":QQ/Resources/QQ_Penguin_tencent_128px_500133_easyicon.net.ico"));
	w.show();
	return a.exec();
}
