#include <iostream>

#ifdef _MSC_VER
#define _WIN32_WINNT 0X0501
#endif
#include <boost\smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost\asio.hpp>
#include <boost/thread.hpp> 
#include "SrvBusiness.h"
using namespace std;
typedef boost::asio::io_service io_service_t;


#include "MYSQLDB.h"
#include "ServerModel.h"

void main()
{
	cout << "QQ服务器启动" << endl;

	boost::thread t_dbinit(boost::bind(&MYSQLDB::InitDB, MYSQLSERVER));
	t_dbinit.join();

	io_service_t ios;
	CServer *srv=new CServer(ios);
	SRVBUSINESS->m_pCServer = srv;
	cout << "QQ服务器正常运行" << endl;
	ios.run(); //开启事件处理循环
}