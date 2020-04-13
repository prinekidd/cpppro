#include "TCPModel.h"
#include "common.h"
#include <commdef.h>

TCPModel::~TCPModel()
{
	m_tcpClient->disconnectFromHost();
}

bool TCPModel::ConnectToSrv()
{
	m_tcpClient->connectToHost(QString("127.0.0.1"), 44444);

	if (m_tcpClient->waitForConnected(1000))  
	{
		return true;
	}
	return false;
}

void TCPModel::LoginToSrv(QString acc, QString pwd)
{
	QJsonObject root_Obj;
	QJsonObject root;
	//添加键值对，值的类型自动识别，顺序不可自定义
	root_Obj.insert("account", acc);
	root_Obj.insert("password", pwd);
	root.insert("msg_type", CLIENT_RQ::ClientLogin);
	root.insert("data", root_Obj);
	//创建Json文档
	QJsonDocument root_Doc;
	root_Doc.setObject(root);
	QByteArray root_str = root_Doc.toJson(QJsonDocument::Compact);  //紧凑格式
  // QByteArray root_str = root_Doc.toJson(QJsonDocument::Indented);   //标准JSON格式    QString strJson(root_str);
	QString strJson(root_str);

	m_tcpClient->write(strJson.toStdString().c_str());
}

QTcpSocket* TCPModel::GetQTcpSocket()
{
	return m_tcpClient;
}

TCPModel::TCPModel()
{
	m_tcpClient = new QTcpSocket();  //实例化tcpClient
	m_tcpClient->abort();
}