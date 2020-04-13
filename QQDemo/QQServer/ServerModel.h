#pragma once

#include <iostream>

#ifdef _MSC_VER
#define _WIN32_WINNT 0X0501
#endif
#include <boost\smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost\asio.hpp>
#include <map>
#include <commdef.h>
#define max_len 1024
using namespace std;
typedef boost::asio::io_service io_service_t;
typedef boost::asio::ip::tcp::acceptor acceptor_t;
typedef boost::asio::ip::tcp::endpoint endpoint_t;
typedef boost::asio::ip::tcp::socket socket_t;
typedef boost::asio::ip::tcp tcp_t;
typedef boost::shared_ptr<socket_t> spSock_t;


class CServer
{
public:
	CServer(io_service_t& io)
		: ios(io) //使用传入的io_service
		, acceptor(ios, endpoint_t(tcp_t::v4(), 44444)) //绑定本机IP及6688端口
	{
		accept_async();
	}
	virtual ~CServer() {}
public:
	void accept_async(); //发起一个异步接受连接


	void accept_handler(const boost::system::error_code& ec, spSock_t spSock); //accept完成后的回调

	void send_handler(const boost::system::error_code& ec, spSock_t spSock); //发送数据完成的回调

	void read_handler(const boost::system::error_code& error, spSock_t spSock);


private:
	io_service_t& ios;
	acceptor_t acceptor;
	char data_[max_len];
};
