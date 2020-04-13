#define _CRT_SECURE_NO_WARNINGS
#include "MYSQLDB.h"
#include <iostream>
#include<WinSock.h>
#include "SrvBusiness.h"
MYSQLDB::MYSQLDB()
{
}

MYSQLDB::~MYSQLDB()
{
	mysql_free_result(res);  //�ͷ�һ���������ʹ�õ��ڴ档
	mysql_close(&m_mysql);	 //�ر�һ�����������ӡ�
}

bool MYSQLDB::createDatabase(std::string& dbname)
{
	std::string queryStr = "create database if not exists ";
	queryStr += dbname;
	if (0 == mysql_query(&m_mysql, queryStr.c_str())) {
		queryStr = "use ";
		queryStr += dbname;
		if (0 == mysql_query(&m_mysql, queryStr.c_str())) {
		//	std::cout << "�������ݿ�["<<dbname<<"]�ɹ�" << std::endl;
			  return true;
		}
	}
	std::cout << "�������ݿ�[" << dbname << "]ʧ��" << mysql_error(&m_mysql) <<std::endl;
	return false;
}

bool MYSQLDB::createdbTable(const std::string& query)
{
	if (0 == mysql_query(&m_mysql, query.c_str())) {
		//std::cout << "����["<< query <<"]��ɹ�" << std::endl;
		return true;
	}
	std::cout << "����[" << query << "]��ʧ�ܣ�"<< mysql_error(&m_mysql)<<std::endl;
	return false;
}


//��ѯ����

bool MYSQLDB::SelectDB()
{
	mysql_query(&m_mysql, "set names gbk");
	//����0 ��ѯ�ɹ�������1��ѯʧ��  	
	if (mysql_query(&m_mysql, "select * from qquserdate"))        //ִ��SQL���  
	{		
		printf("Query failed (%s)\n", mysql_error(&m_mysql));
		return false;	
	}	
	else	
	{		
		printf("query success\n");
	}	
	res = mysql_store_result(&m_mysql);	//��ӡ�������� 
	int idx = mysql_affected_rows(&m_mysql);
	return true;
}

bool MYSQLDB::InsertData(std::string table_name, const std::string& data)
{
	std::string under = "insert into "+ table_name+" values (" + data + ");";
	strcpy(query, under.c_str());
	if (mysql_query(&m_mysql, query))        //ִ��SQL���  
	{		
		printf("Query failed (%s)\n", mysql_error(&m_mysql));
		return false;
	}	
	else	
	{		
		printf("���Ӽ�¼[%s]����[%s]���\n", data.c_str(), table_name.c_str());
		return true;	
	}

}

bool MYSQLDB::InitDB()
{
	//��ʼ��mysql 
	mysql_init(&m_mysql);  //����mysql�����ݿ� 
	const char host[] = "localhost";
	const char user[] = "root";	const char psw[] = "123456";
	const char table[] = "qqdata";
	const int port = 3306;	//����false������ʧ�ܣ�����true�����ӳɹ� 
	if (!(mysql_real_connect(&m_mysql, host, user, psw, table, port, NULL, 0)))
		//�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
	{
		printf("Error connecting to database:%s\n", mysql_error(&m_mysql));
		return false;
	}
	else
	{
		printf("���ݿ����ӳɹ�\n");
	}

	std::string database = "qqdata";
	createDatabase(database);
	std::string sql = "CREATE TABLE IF NOT EXISTS `qquserdate`( \
        `login_index`     int,\
		`user_account`     varchar(15),\
		`password`         varchar(10),\
        `ipadress`         varchar(20),\
		`last_login_time`  BIGINT ,\
		PRIMARY KEY(`login_index`)\
		) ENGINE = InnoDB DEFAULT CHARSET = latin1";
	createdbTable(sql);


	sql = "CREATE TABLE IF NOT EXISTS `user_list`( \
		`user_account`     varchar(15),\
		`password`         varchar(10),\
		PRIMARY KEY(`user_account`)\
		) ENGINE = InnoDB DEFAULT CHARSET = latin1";
	createdbTable(sql);

	SelectDB();
	return true;
}


bool MYSQLDB::signInQuery(const std::string& username, const std::string& password, std::string& result)
{
	std::string sql("SELECT username, password FROM user_list WHERE user_account = \"" + username + "\" AND password = \"" +
		password + "\";");
	if (mysql_query(&m_mysql, sql.c_str())) {
		result.clear();
		result += std::string(mysql_error(&m_mysql));
		return false;
	}
	auto res = mysql_store_result(&m_mysql);
	int num_fields = mysql_num_fields(res);
	if (num_fields <= 0) {
		result = std::string("Query error\n");
		return false;
	}

	MYSQL_ROW row = mysql_fetch_row(res);
	if (!row) {
		result = std::string("user_account: " + username + " does not exist!");
		return false;
	}
	auto username_ = std::string(row[0]);
	auto password_ = std::string(row[1]);
	if (username != username_) {
		result = std::string("user_account: " + username + " does not exist!");
		return false;
	}
	if (password_ != password) {
		result = std::string("password error!");
		return false;
	}

	finishQuery();
	result = "login success";
	return true;
}
