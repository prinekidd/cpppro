#include <iostream>

#ifdef _MSC_VER
#define _WIN32_WINNT 0X0501
#endif
#include <boost\smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost\asio.hpp>
#include <boost/thread.hpp> 
using namespace std;
typedef boost::asio::io_service io_service_t;


#include "MYSQLDB.h"
#include "ServerModel.h"

void main()
{
	cout << "QQ����������" << endl;

	boost::thread t_dbinit(boost::bind(&MYSQLDB::InitDB, MYSQLSERVER));
	t_dbinit.join();

	io_service_t ios;
	CServer srv(ios);

	cout << "QQ��������������" << endl;

	ios.run(); //�����¼�����ѭ��
}