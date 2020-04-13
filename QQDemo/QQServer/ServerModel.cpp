#include "ServerModel.h"
#include "SrvBusiness.h"
#include <boost/format.hpp>
#include <json/json.h>
#include <commdef.h>

	void CServer::accept_async() //����һ���첽��������
	{
		spSock_t spSock(new socket_t(ios));
		acceptor.async_accept(*spSock, boost::bind(&CServer::accept_handler, this, _1, spSock));
	}

	void CServer::accept_handler(const boost::system::error_code& ec, spSock_t spSock) //accept��ɺ�Ļص�
	{
		if (ec) //��������
			return;

		cout << "�пͻ�������, ���� ";
		cout << spSock->remote_endpoint().address() << ": " << spSock->remote_endpoint().port() << endl; //����ͻ���ַ�Ͷ˿ں�
		spSock->async_read_some(boost::asio::buffer(data_, max_len),boost::bind(&CServer::read_handler, this, _1, spSock));
		accept_async(); //�ٴη���һ���첽��������
	}

	void CServer::send_handler(const boost::system::error_code& ec, spSock_t spSock) //����������ɵĻص�
	{
		cout << "���͸��ͻ�����Ϣ���" << endl;
	}

	void CServer::read_handler(const boost::system::error_code& error, spSock_t spSock)
	{
		if (!error)
		{
			std::string ret_str=SRVBUSINESS->OnClientMsgHandle(data_, spSock);
		
			spSock->async_read_some(boost::asio::buffer(data_, max_len),boost::bind(&CServer::read_handler, this, _1, spSock));
		}
	}

