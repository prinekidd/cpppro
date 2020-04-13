#include "ServerModel.h"
#include "SrvBusiness.h"
#include <boost/format.hpp>
#include <json/json.h>
#include <commdef.h>

	void CServer::accept_async() //发起一个异步接受连接
	{
		spSock_t spSock(new socket_t(ios));
		acceptor.async_accept(*spSock, boost::bind(&CServer::accept_handler, this, _1, spSock));
	}

	void CServer::accept_handler(const boost::system::error_code& ec, spSock_t spSock) //accept完成后的回调
	{
		if (ec) //检测错误码
			return;

		cout << "有客户端连接, 来自 ";
		cout << spSock->remote_endpoint().address() << ": " << spSock->remote_endpoint().port() << endl; //输出客户地址和端口号
		spSock->async_read_some(boost::asio::buffer(data_, max_len),boost::bind(&CServer::read_handler, this, _1, spSock));
		accept_async(); //再次发起一个异步接受连接
	}

	void CServer::send_handler(const boost::system::error_code& ec, spSock_t spSock) //发送数据完成的回调
	{
		cout << "发送给客户端消息完成" << endl;
	}

	void CServer::read_handler(const boost::system::error_code& error, spSock_t spSock)
	{
		if (!error)
		{
			std::string ret_str=SRVBUSINESS->OnClientMsgHandle(data_, spSock);
		
			spSock->async_read_some(boost::asio::buffer(data_, max_len),boost::bind(&CServer::read_handler, this, _1, spSock));
		}
	}

