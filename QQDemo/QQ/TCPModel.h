#pragma once
#include <QTcpSocket>
#include <QHostAddress>
#include "singleton.h"
class TCPModel
{
public:
    TCPModel();
    ~TCPModel();
public:
    bool ConnectToSrv();
    
    void LoginToSrv(QString acc,QString pwd);

    QTcpSocket* GetQTcpSocket();
private:
    QTcpSocket* m_tcpClient;
};


#define NetWork singleton<TCPModel>::instance()