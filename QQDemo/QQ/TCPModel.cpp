#include "TCPModel.h"
#include "common.h"
#include <QMessageBox>


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
	QMessageBox::information(NULL, QString(QString::fromLocal8Bit("错误")), QString(QString::fromLocal8Bit("未能连接到服务器")));
	return false;
}

void TCPModel::LoginToSrv(QString acc, QString pwd)
{
	QJsonObject root_Obj;
	root_Obj.insert("account", acc.toInt());
	root_Obj.insert("password", pwd);
	m_curAcc = acc;
	SendRequestToServer(CLIENTCOMMAND::ClientLoginRq, root_Obj);
}

void TCPModel::LongOut()
{
	QJsonObject root_Obj;
	root_Obj.insert("account", m_curAcc.toInt());
	SendRequestToServer(CLIENTCOMMAND::ClientLogOutRq, root_Obj);
}

void TCPModel::RegistAcc(QString acc, QString pwd)
{
	QJsonObject root_Obj;
	root_Obj.insert("account", acc);
	root_Obj.insert("password", pwd);

	SendRequestToServer(CLIENTCOMMAND::ClientRegistAccRq, root_Obj);
}



void TCPModel::SendRequestToServer(CLIENTCOMMAND msg_type, const QJsonObject& jsonobj)
{
	QJsonObject root;
	root.insert("msg_type", msg_type);
	root.insert("data", jsonobj);
	QJsonDocument root_Doc;
	root_Doc.setObject(root);
	QByteArray root_str = root_Doc.toJson(QJsonDocument::Compact); 
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