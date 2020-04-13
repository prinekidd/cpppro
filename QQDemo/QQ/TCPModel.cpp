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
	//��Ӽ�ֵ�ԣ�ֵ�������Զ�ʶ��˳�򲻿��Զ���
	root_Obj.insert("account", acc);
	root_Obj.insert("password", pwd);
	root.insert("msg_type", CLIENT_RQ::ClientLogin);
	root.insert("data", root_Obj);
	//����Json�ĵ�
	QJsonDocument root_Doc;
	root_Doc.setObject(root);
	QByteArray root_str = root_Doc.toJson(QJsonDocument::Compact);  //���ո�ʽ
  // QByteArray root_str = root_Doc.toJson(QJsonDocument::Indented);   //��׼JSON��ʽ    QString strJson(root_str);
	QString strJson(root_str);

	m_tcpClient->write(strJson.toStdString().c_str());
}

QTcpSocket* TCPModel::GetQTcpSocket()
{
	return m_tcpClient;
}

TCPModel::TCPModel()
{
	m_tcpClient = new QTcpSocket();  //ʵ����tcpClient
	m_tcpClient->abort();
}