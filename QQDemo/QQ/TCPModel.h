#pragma once
#include <QTcpSocket>
#include <QHostAddress>
#include "singleton.h"
#include <commdef.h>

class TCPModel
{
public:
    TCPModel();
    ~TCPModel();
public:
    bool ConnectToSrv();
    
    void LoginToSrv(QString acc,QString pwd);
    void LongOut();
    void RegistAcc(QString acc, QString pwd);
    void  SendRequestToServer(CLIENTCOMMAND msg_type, const QJsonObject& jsonobj);
    QTcpSocket* GetQTcpSocket();
private:
    QTcpSocket* m_tcpClient;
    QString m_curAcc;
};


#define NetWork singleton<TCPModel>::instance()